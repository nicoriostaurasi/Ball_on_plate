/*
 * adxl345.h
 *
 *  Created on: May 27, 2021
 *
 *      Author: Nicolas Rios Taurasi
 */

#include "main.h"
//#include "i2c-lcd.h"
#include "ssd1306.h"
#include "math.h"
#include "string.h"
#define pi 3.14159265359
#define LEN_BUFFER_D 2
#define LEN_BUFFER_E 4
#define CANT_PROMEDIOS 100
SPI_HandleTypeDef hspi1;

uint8_t data_rec[10]; //buffer de conversion
int16_t x,y,z;		  //variables en donde se almacena
int16_t x_new,y_new,z_new;
int16_t x_buff[CANT_PROMEDIOS];
int16_t y_buff[CANT_PROMEDIOS];
int16_t z_buff[CANT_PROMEDIOS];

float xg,yg,zg;		  //floats de aceleracion
float alpha;
float beta;
int16_t alpha_entero;
int16_t beta_entero;
int16_t alpha_decimal;
int16_t beta_decimal;

char buff_ae[LEN_BUFFER_E];
char buff_ad[LEN_BUFFER_D];
char buff_be[LEN_BUFFER_E];
char buff_bd[LEN_BUFFER_D];


void adxl_init(void);
void adxl_read (uint8_t);
void adxl_write (uint8_t,uint8_t);
void lectura_acelerometro(void);
void acelerometro_a_display(void);
void promedio_angulos(void);
