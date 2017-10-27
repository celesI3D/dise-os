/*
 * api.c
 *
 *  Created on: Oct 25, 2017
 *      Author: seb
 */

#include "sapi.h"
#include "api.h"
#include "apiSD.h"

static void FormatInformationArray	(uint16_t valorAdc);

static char InformationArray[100];

uint8_t apiReadTemperatureHumdity(uint16_t * dataTemp, uint16_t * dataHum) {
	uint16_t adcValue1, adcValue2;

	adcValue1 = adcRead(CH1); // temp
	adcValue2 = adcRead(CH2); // hum

	return _API_STATE_OK;
}

uint8_t apiReadWind(uint16_t * dataWind) {
	uint16_t adcValue3 = 0;

	adcValue3 = adcRead(CH3); // viento

	return _API_STATE_OK;
}

uint8_t apiReadSensor(uint16_t * dataTemp, uint16_t * dataHum, uint16_t * dataWind) {

	apiReadTemperatureHumdity(dataTemp, dataHum);

	apiReadWind(dataWind);

	return _API_STATE_OK;
}

static void FormatInformationArray	(uint16_t valorAdc){
	InformationArray[0] = valorAdc/1000 		+ '0';
	InformationArray[1] = (valorAdc%1000)/100 	+ '0';
	InformationArray[2] = (valorAdc%100)/10 	+ '0';
	InformationArray[3] = (valorAdc%10) 		+ '0';
	InformationArray[4] = '\n';
	InformationArray[5] = '\r';
	InformationArray[6] = '\0';
}

uint8_t apiProcessInformation(uint16_t dataTemp, uint16_t dataHum, uint16_t dataWind, uint8_t * destiny) {

	// Formatea el array InformationArray con el valor leido del potenciometro.
	FormatInformationArray(dataTemp);

	return _API_STATE_OK;
}

uint8_t apiWriteSD(uint8_t * filename, uint8_t * stringData) {

	if(apiSD_Init() == _API_STATE_ERROR) {
		// error
	} else {
		if(apiSD_Write(filename) != 0) {
			// error
			gpioWrite( LEDR, ON );
		} else {
			// ok
			gpioWrite( LEDG, ON );
		}
	}

	return _API_STATE_OK;
}
