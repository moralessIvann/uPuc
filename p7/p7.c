#include <avr/io.h>
//#include <inttypes.h>

// Macros
#define setBitPort(port, bit) asm ("sbi %0, %1"::"I"(_SFR_IO_ADDR(port)),"I" (bit))
#define ClrBitPort(port, bit) asm ("cbi %0, %1"::"I"(_SFR_IO_ADDR(port)),"I" (bit))
#define HIGH 1
#define LOW 0


enum ButtonPressStates{
  eBtnUndefined , //0
  eBtnShortPressed , //1
  eBtnLongPressed  //2
};

// External definitions (ASM)
extern void delay();
void getDelay(uint16_t mseg);


// Local definitions prototypes
void initPorts(void);
uint8_t checkBtn(void);
void updateLeds(void);

// Global variables
uint8_t globalCounter = 0;
uint32_t millis = 0;

int main(void){
	
	initPorts();

	while(1){
		
		switch(checkBtn()){
			
			case eBtnShortPressed: globalCounter++;
			break;
			
			case eBtnLongPressed:  globalCounter--;
			break;
		}
		updateLeds();
		getDelay(5); //
		millis+=5;	
	}
	return 0;
}

void initPorts(void){

	DDRF = 0x40;  //0100 0000
	PORTF = 0x80; //1000 0000
}

uint8_t checkBtn(void){
	
	uint32_t pressedTime = 0;
	uint8_t prevState = HIGH;
	
	if( !(PINF&(1<<PF7)) ){ //no presionado (lee 1 de pullup, not=0)
		if(prevState){
			prevState = LOW;
			pressedTime = millis;	
		}
	}else{ //si presionado (lee 0, not=1)
		if((millis - pressedTime)>100 && prevState == LOW){
			prevState = HIGH;
			if((millis - pressedTime)>999){
				return eBtnLongPressed; //2
			}else{
				return eBtnShortPressed; //1
			}
		}
	}
	return eBtnUndefined; //0
}

void updateLeds(void){
	
	uint8_t ledNum = 0, tmp;
	tmp = globalCounter;
	
	//PORTF &=  ~(1<<PF0) & ~(1<<PF1) & ~(1<<PF2) & ~(1<<PF3);
  	//DDRF &= ~(1<<DDF0) & ~(1<<DDF1) & ~(1<<DDF2) & ~(1<<DDF3);

      if (	(tmp) & (1<<ledNum) ){

            if (ledNum == 0 || ledNum ==1) {					        

                DDRF |= (1<<DDF0) | (1<<DDF1);

                if (ledNum == 0) {
                    setBitPort(PORTF,PF1);					              
                } else {
                  	setBitPort(PORTF,PF0);
                }
		
				
            }
            else if (ledNum == 2 || ledNum == 3) {
			
              DDRF |= (1<<DDF2) | (1<<DDF1);

                if (ledNum == 2) {
                  setBitPort(PORTF,PF2);
                 
                } else {
                  setBitPort(PORTF,PF1);
                }

				
            }
            else if (ledNum == 4 || ledNum == 5) {
			
              
              DDRF |= (1<<DDF0) | (1<<DDF2);
         

                if (ledNum == 4) {
                  setBitPort(PORTF,PF0);
                } else {
                  setBitPort(PORTF,PF2);
                }

			
            }
            else if(ledNum == 6|| ledNum == 7){
		
           
              DDRF |= (1<<DDF3) | (1<<DDF2);
              
                if (ledNum == 6) {
                  setBitPort(PORTF,PF3);
                  
                }
                else{
                  setBitPort(PORTF,PF2);                  
                }
				 
            }
			
			
    }

		
		ledNum = ++ledNum % 8;
}

void getDelay(uint16_t mseg){
	
	uint8_t i=0;
	
	while(i<mseg){
		delay();
		i++;
	}	
}


