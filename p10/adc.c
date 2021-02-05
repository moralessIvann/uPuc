#include "adc.h"
#include "uart.h"
#include "timer.h"

void ADC_Ini(void){
    
	ADMUX |= (1<<REFS0)|(1<<ADLAR)|(1<<MUX0); //avcc ref
	ADCSRA |= (1<<ADEN)|(7<<ADPS0);
	ADCSRB = 0x00;
}

uint8_t ADC_Read(uint8_t channel){ 
    
	channel &= 0x07;
	ADMUX |= (ADMUX & 0xF8)|channel; //obtener channel
	ADCSRA |= (1<<ADSC);
	ADCSRB = 0x00;
	while(ADCSRA & (1<<ADSC));
									
	return ADCH;
}

void motion_lectures(){
	
	uint8_t value, i; //i;
	char str[20];
	
	value = ADC_Read(1);

	for(i=0;i<value/5;i++)
		UART_putchar(0,'.');
	itoa(value,str,10);
	UART_puts(0,str);
	UART_puts(0,"\n\r");

}

uint8_t motion_Detected(uint8_t value){ 

	if(value>RANGO)	
		return 1;
	else
		return 0;	
}


uint8_t motion_value(){
	
	uint8_t value;
	
	value = ADC_Read(1);
	
	return value;
}

