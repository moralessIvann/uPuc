/* Morales Rosales Iván A
   1231098
   P5 Interrupciones temporizadas y E/S mapeada a memoria
   uPuC */
   

#include "timer.h"
#define BYTE unsigned char
#define WORD unsigned int

extern void poke(WORD seg, WORD offset, BYTE data);
void UpdateClock( void );
void DisplayClock( void );
void PrintDec2d( BYTE );
void SetClock(BYTE hora, BYTE minutos, BYTE segundos);
void Delay( BYTE );

BYTE seg, min, hr; /* para el manejo de los segundos */

void main(){

	Timer_Ini(); /* inicialzaTimer de 1 segundo */
	SetClock(23,59,50); 
	
	while(1){
		/* Verificación para actualizar el reloj */
		if(TimerSecFlag() ){ /* Ha pasado un segundo? */
			UpdateClock(); /* actualiza y muestra el reloj */
			DisplayClock(); /* desplegar reloj en 0,0 */
			/* indicar en puerto */
			poke(0x0,0x2200,seg); /*0x02200-0x0FFFF*/
		}
		/* otras cosas por hacer */
		Delay(2000);
		/* putchar('.'); /* Imprime */
	}
}

void UpdateClock( void ){
	/*seg=(++seg%60);*/
	/*falta minutos , horas etc. etc. */
	seg++;
	if(seg == 60){
		seg = 0;
		min++;
		if(min == 60){
			min = 0;
			hr++;
			if(hr>23){
				hr = 0;
			}
		}
	}
}

void DisplayClock( void ){
	/* imprimir reloj en formato "hh:mm:ss" */;
	PrintDec2d(hr);
	putchar(':');
	PrintDec2d(min);
	putchar(':');
	PrintDec2d(seg); 
	putchar('\r');
}

void SetClock(BYTE hora, BYTE minutos, BYTE segundos){
	/* inicializar clock*/
	hr = hora;
	min = minutos;
	seg = segundos;
}

void Delay( BYTE i){
	while(--i);
}

void PrintDec2d( BYTE dato){
	putchar( dato/10 +'0'); /* Imprime decenas */
	putchar( dato%10 +'0'); /* Imprime unidades */
}

