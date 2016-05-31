/*
 * temperature.h
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#ifndef TEMPMEASURING_H_
#define TEMPMEASURING_H_

#include <DHT.h>

#include "TempReading.h"

class TempMeasuring {
	DHT dht;
	uint8_t pin;
public:
	void doSetup();
	TempReading measureTemp();
	TempMeasuring(uint8_t pin, uint8_t type);
};

#endif /* TEMPMEASURING_H_ */
