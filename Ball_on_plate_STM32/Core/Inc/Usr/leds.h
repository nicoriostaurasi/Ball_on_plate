/**
 * @file leds.h
 * @brief En este archivo se encuentran las cabeceras de las funciones de manejo de los leds.
 * @author Tomás Bautista Ordóñez
 * @date 15/04/2021
 */

#ifndef INC_USR_LEDS_H_
#define INC_USR_LEDS_H_

#include "stm32f1xx.h"

///Periodo de toggleo del led
#define LED_COUNT 	COUNT_300ms

/**
 * @brief Inicializa la secuencia del led.
 *
 */
void leds_inicializar(void);

#endif /* INC_USR_LEDS_H_ */
