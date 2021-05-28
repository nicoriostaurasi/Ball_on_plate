/*
 * adxl345.c
 *
 *  Created on: May 27, 2021
 *
 *      Author: Nicolas Rios Taurasi
 */

#include "adxl345.h"


/*Funcion para iniciar el adxl*/
void adxl_init()
{
	adxl_write (0x31, 0x01);  // data_format range= +- 4g
	adxl_write (0x2d, 0x00);  // reset all bits
	adxl_write (0x2d, 0x08);  // power_cntl measure and wake up 8hz
}

/*Funcion para escribir el adxl*/
void adxl_write (uint8_t address, uint8_t value)
{
	uint8_t data[2];
	data[0] = address|0x40;  // multibyte write
	data[1] = value;
	HAL_GPIO_WritePin (SPI1_CS_GPIO_Port,SPI1_CS_Pin  , GPIO_PIN_RESET);  // pull the cs pin low
	HAL_SPI_Transmit (&hspi1, data, 2, 100);  // write data to register
	HAL_GPIO_WritePin (SPI1_CS_GPIO_Port,SPI1_CS_Pin, GPIO_PIN_SET);  // pull the cs pin high
}

/*Funcion para leer el adxl*/
void adxl_read (uint8_t address)
{
	address |= 0x80;  // read operation
	address |= 0x40;  // multibyte read
//	uint8_t rec;
	HAL_GPIO_WritePin (SPI1_CS_GPIO_Port,SPI1_CS_Pin , GPIO_PIN_RESET);  // pull the pin low
	HAL_SPI_Transmit (&hspi1, &address, 1, 100);  // send address
	HAL_SPI_Receive (&hspi1, data_rec, 6, 100);  // receive 6 bytes data
	HAL_GPIO_WritePin (SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);  // pull the pin high
}

/*Aplicacion que lee el acelerometro promedia y calcula los angulos en °*/
void lectura_acelerometro()
{

		adxl_read(0x32);
		x_new=((data_rec[1]<<8)|data_rec[0]);
		y_new=((data_rec[3]<<8)|data_rec[2]);
		z_new=((data_rec[5]<<8)|data_rec[4]);

		promedio_angulos();


		xg=x*0.0078;
		yg=y*0.0078;
		zg=z*0.0078;

		alpha=atan2(xg,zg)*(180/pi);
		beta=atan2(yg,zg)*(180/pi);

		alpha_entero=truncf(alpha);
		beta_entero=truncf(beta);

		alpha_decimal=(uint16_t)(100*fabs(alpha)-100*fabs(alpha_entero));
		beta_decimal=(uint16_t)(100*fabs(beta)-100*fabs(beta_entero));

		itoa(alpha_entero,buff_ae,10);
		itoa(alpha_decimal,buff_ad,10);
		itoa(beta_entero,buff_be,10);
		itoa(beta_decimal,buff_bd,10);


		if(beta_decimal<9)
		{
		 buff_bd[1]=buff_bd[0];
		 buff_bd[0]='0';
		}

		if(alpha_decimal<9)
		{
		 buff_ad[1]=buff_ad[0];
		 buff_ad[0]='0';
		}




}

/*Funcion externa para promediar (filtro de media movil)*/
void promedio_angulos()
{
	static uint8_t i=0;
	static int16_t aux=0;
	aux=0;

	for(i=0;i<CANT_PROMEDIOS-1;i++)
	{
	x_buff[i+1]=x_buff[i];
	}

	for(i=0;i<CANT_PROMEDIOS-1;i++)
	{
	y_buff[i+1]=y_buff[i];
	}

	for(i=0;i<CANT_PROMEDIOS-1;i++)
	{
	z_buff[i+1]=z_buff[i];
	}


	x_buff[0]=x_new;
	y_buff[0]=y_new;
	z_buff[0]=z_new;


	aux=0;

	for(i=0;i<CANT_PROMEDIOS;i++)
	{
	aux=aux+x_buff[i];
	}
	x=aux/CANT_PROMEDIOS;


	aux=0;

	for(i=0;i<CANT_PROMEDIOS;i++)
	{
	aux=aux+y_buff[i];
	}
	y=aux/CANT_PROMEDIOS;

	aux=0;

	for(i=0;i<CANT_PROMEDIOS;i++)
	{
	aux=aux+z_buff[i];
	}
	z=aux/CANT_PROMEDIOS;

}

/*Funcion para imprimir*/
void acelerometro_a_display()
{
	SSD1306_GotoXY (1,0);
	SSD1306_Puts ("x: ", &Font_11x18, 1);
	SSD1306_GotoXY (20,0);
	SSD1306_Puts("            ", &Font_11x18, 1);
	SSD1306_GotoXY (20,0);
	SSD1306_Puts (buff_ae, &Font_11x18, 1);
	SSD1306_Puts (".", &Font_11x18, 1);
	SSD1306_Puts (buff_ad, &Font_11x18, 1);
	SSD1306_Puts ("~", &Font_11x18, 1); //°

	SSD1306_GotoXY (1,30);
	SSD1306_Puts ("y: ", &Font_11x18, 1);
	SSD1306_GotoXY (20,30);
	SSD1306_Puts("            ", &Font_11x18, 1);
	SSD1306_GotoXY (20,30);
	SSD1306_Puts (buff_be, &Font_11x18, 1);
	SSD1306_Puts (".", &Font_11x18, 1);
	SSD1306_Puts (buff_bd, &Font_11x18, 1);
	SSD1306_Puts ("~", &Font_11x18, 1); //°

	SSD1306_UpdateScreen(); //display

}


