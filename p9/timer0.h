#ifndef _TIMER0_H
#define _TIMER0_H

#include <inttypes.h>

#define FCPU 16000000
#define PS 64
#define TICKS(t) ( ((FCPU/t) / PS) - 1 )

/* Función para inicializar el Timer0 y generar */
/* la temporización de 1 Sec. */
void Timer0_Ini ( void );

/* Función para verificar bandera del segundo */
uint8_t Timer0_SecFlag ( void );

/* Función que retorna el conteo actual de millis */
uint64_t millis(void);

/* Función para inicializar reloj en base a los parametros */
void Clock_Ini(uint8_t hr, uint8_t min, uint8_t seg);

/* Función para actualizar el reloj */
void Clock_Update(void);
		
/* Función para mostrar el reloj */
void Clock_Display(void);

/* Función para imprimir las hr, min y seg */
void PrintDec2d(uint16_t dato);

#endif /* _TIMER0_H */
