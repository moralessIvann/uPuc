#ifndef _TIMER0_H
#define _TIMER0_H

#include <inttypes.h>

#define FCPU 16000000
#define PS 64
#define TICKS(t) ( ((FCPU/t) / PS) - 1 )

/* Funci�n para inicializar el Timer0 y generar */
/* la temporizaci�n de 1 Sec. */
void Timer0_Ini ( void );

/* Funci�n para verificar bandera del segundo */
uint8_t Timer0_SecFlag ( void );

/* Funci�n que retorna el conteo actual de millis */
uint64_t millis(void);

/* Funci�n para inicializar reloj en base a los parametros */
void Clock_Ini(uint8_t hr, uint8_t min, uint8_t seg);

/* Funci�n para actualizar el reloj */
void Clock_Update(void);
		
/* Funci�n para mostrar el reloj */
void Clock_Display(void);

/* Funci�n para imprimir las hr, min y seg */
void PrintDec2d(uint16_t dato);

#endif /* _TIMER0_H */
