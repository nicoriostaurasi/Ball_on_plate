/*
 * i2c-lcd.h
 *
 *  Created on: 30 abr. 2021
 *      Author: Nicolas Rios Taurasi
 */


#include "stm32f1xx_hal.h"

void lcd_init (void);   // initializa LCD

void lcd_send_cmd (char cmd);  // envia comando al LCD

void lcd_send_data (char data);  // envia caracter al LCD

void lcd_send_string (char *str);  // envia un string al LCD

void lcd_send_float (float data, int numberofdigits);  // muestra un numero flotante en el LCD
