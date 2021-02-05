#ifndef _ADC_H
#define _ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#define RANGO 50 //valor en base a lecturas de ADC al detectar proximidad en la antena

/* Esta funci�n inicializa para 8 bits de resoluci�n y habilita el ADC del microcontrolador de
   forma gen�rica. Encontrar el desplazamiento (offset) de la medici�n y almacenarla. */
void ADC_Ini();

/* Est� funci�n lo que realiza es una lectura del ADC usando el canal correcto y retornando el
   valor de 8 bits acorde a la aplicaci�n (ver Figura 2), compensando el desplazamiento de la medici�n. */
uint8_t ADC_Read(uint8_t channel); // 

/* Esta funci�n utiliza ADC_Read() y en base a las �ltimas muestras determina si ha detectado
   alg�n movimiento. */
uint8_t motion_Detected(uint8_t value);

/* funcion que retorna valor establecido para detectar proximidad mediante la antena*/
uint8_t motion_value();

//void motion_lectures();

#endif





