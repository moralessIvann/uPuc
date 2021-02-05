#include <avr/io.h>
#include "uart.h"
#include "adc.h"
#include "timer.h"

#define ledON PORTF |= (1<<PF7)
#define ledOFF PORTF &= ~(1<<PF7)
#define A4 440
#define A5 880
#define volume 50
#define dischargeTime 5

void LED_ports_init(); //configurar puesrtos de LED
void delay(uint16_t ms);
char timeCntr = 0;	

int main(){
	
	//UART_AutoBaudRate();
	char i;
	UART_Ini(0,9600,8,0,1);
	Timer0_Ini();
	ADC_Ini();
	LED_ports_init();
	
	while(1){
		
		motion_value(); //incio muestreo de lecturas del adc
		
		if( Timer0_SecFlag() ){		//si paso 1 seg...
			timeCntr++;				//inc contador

			while(timeCntr>dischargeTime){ //mientras contador sea mayor a tiempo de descarga...
				if( motion_Detected(motion_value()) ){ //recibe lecturas y verificar si detecta movimiento
					
					ledON; //enciende LED
					Timer2_Gen_Tone(A5,50); //activa bocina
					for(i=0; i<85; i++){ //espera aqui
						delay(10);
						Timer2_Gen_Tone(A4,50); //alternar sonido de bocina
					}		
					break;	
				}
				ledOFF; 
				Timer2_Gen_Tone(0,0); //no ruido	
			}	 
		}	
	}
	return 0;
}

void LED_ports_init(){

	DDRF |= (1<<PF7)|(1<<PF6); //config LED port
	PORTF &= ~(1<<PF6);
}

void delay(uint16_t ms){  //delay de 10ms
    //6x + 5xy + 12
    uint16_t i=0;        //1
    while(ms){            //x+1
        i = 1999;        //x1
        asm("nop");        //x1
        while(i){        //x(y+1)
            i--;        //xy2
            asm("nop");    //xy1
            asm("nop");    //xy1
        }
        ms--;            //x2
	}                   //+10 => (call + ret)
}



