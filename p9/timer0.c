#include <avr/interrupt.h>
#include <inttypes.h>
#include "timer0.h"
#include "uart.h"

static volatile uint8_t SecFlag;
uint64_t millisFromStart = 0;
uint8_t hr, min, sec;

void Timer0_Ini(void){
    
	TCNT0 = 0; //Inicializar valor para el timer0
    TCCR0A |= (1<<WGM01); // inicializa timer0 en modo CTC
	OCR0A = 249;//TICKS(1000); //resolucion //249
	
	/* Inicializar con fuente de osc. Int. */
    TCCR0B |= (3<<CS00); /* con Prescalador 64 */
    TIMSK0 |= (1<<OCIE0A) ; /* habilita interrupcion del Timer0 */
    sei(); /* habilita interrupciones (global) */
}

uint64_t millis(void){
	
	return millisFromStart;
}

uint8_t Timer0_SecFlag(void){
    
	if(SecFlag){
       SecFlag=0;
       return 1;
    }else{
        return 0;
    }
}

ISR(TIMER0_COMPA_vect){ 

   static uint16_t mSecCnt;
    
    millisFromStart++;
	mSecCnt++; /* Incrementa contador de milisegundos */
    
	if(mSecCnt==1000){
        mSecCnt = 0;
        SecFlag = 1; /* Bandera de Segundos */
    }
}

void UART_AutoBaudRate(void){ 

	DDRE &= ~(1<<DDE0); //porte as input
	PORTE |= (1<<PE0); //pull up on

	TCNT0 = 0; //set Counter0 register to 0
	TCCR0A = 0; //normal mode
	TCCR0B = 0; //timer0 stopped

	while ((PINE & (1<<PE0)));
	TCCR0B = (1<<CS01);  //timer0 starts; 8 prescaler
	while (!(PINE & (1<<PE0)));
	TCCR0B = 0; //timer0 stopped

	UBRR0 = (TCNT0>>1)-1;
}


void Clock_Ini(uint8_t hora, uint8_t minutos, uint8_t segundos){
	
	hr = hora;
	min = minutos;
	sec = segundos;
}

void Clock_Display( void ){
	/* imprimir reloj en formato "hh:mm:ss" */;
	
	PrintDec2d(hr); // solo se esta desplegando hr 
	UART_putchar(0,':');
	PrintDec2d(min); // solo se esta desplegando min 
	UART_putchar(0,':');
	PrintDec2d(sec); // solo se esta desplegando segundos 
	UART_putchar(0,'\r');
}

void Clock_Update(void){
	
	sec++;
	if(sec==60){
		sec=0;
		min++;
		if(min==60){
			min=0;
			hr++;
			if(hr>23){ //|| month==topMonth[month-1]){
				hr=0;// day=1; month++;
			}
		}
	}
}

void PrintDec2d(uint16_t dato){
	UART_putchar(0,dato/10+'0'); // Imprime decenas 
	UART_putchar(0,dato%10+'0');
 } 



