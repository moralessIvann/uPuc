#include "timer.h"

static volatile uint8_t SecFlag; 

void Timer0_Ini(void){
    
	TCNT0 = 0; //Inicializar valor para el timer0
    TCCR0A |= (1<<WGM01); // inicializa timer0 en modo CTC
	OCR0A = 249;//TICKS(1000); //resolucion //249
	
	/* Inicializar con fuente de osc. Int. */
    TCCR0B |= (3<<CS00); /* con Prescalador 64 */
    TIMSK0 |= (1<<OCIE0A) ; /* habilita interrupcion del Timer0 */
    sei(); /* habilita interrupciones (global) */
	DDRH |= (1<<PH6); //outuput OC2B
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
    
	mSecCnt++; /* Incrementa contador de milisegundos */
    
	if(mSecCnt==1000){
        mSecCnt = 0;
        SecFlag = 1; /* Bandera de Segundos */
    }
}

void Timer2_Gen_Tone(uint16_t tone, uint8_t volume){
    
	if(TICKS(tone) > 0){
		
		TCCR2A = (1<<COM2B1) | (1<<WGM20); //clear OC2B and set mode PWM phase correct
		TCCR2B = (1<<WGM22) | (1<<CS22) | (1<<CS21) | (1<<CS20); //set mode and PS=1024
		//TCNT2 = 0;
		OCR2A = TICKS(tone);
		OCR2B = (((OCR2A >> 1) * volume)/100);
	}
	else
		TCCR2B = 0; //do nothing
}
