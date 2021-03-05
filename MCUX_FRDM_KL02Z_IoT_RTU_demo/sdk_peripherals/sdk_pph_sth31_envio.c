/*
 * sdk_pph_sth31_envio.c
 *
 *  Created on: 1/03/2021
 *      Author: hp
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "stdio.h"
#include "sdk_pph_ec25au.h"
#include "sdk_mdlw_leds.h"
#include "sdk_pph_sht3x.h"
#include "sdk_pph_sth31_envio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CLOCK	8000000
#define HABILITAR_SENSOR_SHT3X		1
#define enter  0x1A

/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
void borrarBufferQuectel(void);

/*******************************************************************************
 * Local vars
 ******************************************************************************/
uint8_t sht3x_base_de_tiempo=0;
sht3x_data_t sht3x_datos;
uint8_t sht3x_detectado=0;
uint8_t sht3x_dato_salida=0;


const uint8_t  *topic2[]={
	/*0*/"AT+QMTSUB=0 ,1,\"/1/temperatura\",1",
	/*1*/"AT+QMTPUB=0,0,0,0,\"/1/temperatura\"",
	/*2*/"AT+QMTSUB=0 ,1,\"/1/humedad\",1",
	/*3*/"AT+QMTPUB=0,0,0,0,\"/1/humedad\""
};


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/

status_t enviarMQTT_ValueSHT3x(void) {
	sht3xReadData(&sht3x_datos);

	//printf("%s\r\n", topic2[kAT_QMTSUB_T_L]);
	//waytTimeModem(CLOCK);

	printf("%s\r\n", topic2[kAT_QMTPUB_T_L]);
	waytTimeModem(CLOCK );

	printf("%f\r\n %c",((float)(-45.0 + 175.0 * (sht3x_datos.temperatura / 65535.0))),enter); //imprime temperatura
	//printf("temperatura:       %.2f     ",(float)(-45.0+175.0*(sht3x_datos.temperatura/65535.0)));
	printf(enter);
	waytTimeModem(CLOCK);

	//printf("%s\r\n", topic2[kAT_QMTSUB_H_L]);
	//waytTimeModem(CLOCK );
	printf("\r\n");	//Imprime cambio de linea

	printf("%s\r\n", topic2[kAT_QMTPUB_H_L]);
	waytTimeModem(CLOCK);

	//printf("CRC8_t:         0x%X               ",sht3x_datos.crc_temperatura);    //imprime CRC8 de temperatura
	printf("%f\r\n %c",((float) (100.0 * (sht3x_datos.humedad / 65535.0))), enter); //imprime humedad
	//printf("humedad:         %.2f  %%   ",(float)(100.0*(sht3x_datos.humedad/65535.0)));
	waytTimeModem(CLOCK);
	//printf("CRC8_h:         0x%X             ",sht3x_datos.crc_humedad);    //imprime CRC8 de temperatura

	printf("\r\n");	//Imprime cambio de linea

	//printf("%f\r\n%c",SHT3x_TempC(sht3x_data_L),0x1A);
	//printf("temperatura:       %.2f     ",(float)(-45.0+175.0*(sht3x_datos.temperatura/65535.0)),0x1A);


    //float Hum_L = SHT3x_HumRH(sht3x_data_L);


	//printf("%f\r\n%c", SHT3x_HumRH(sht3x_data_L), 0x1A);
	//printf("humedad:         %.2f  %%   ",(float)(100.0*(sht3x_datos.humedad/65535.0)), 0x1A);


	return(0);

}
