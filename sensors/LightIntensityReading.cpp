/*
 * LightIntensityReading.cpp
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#include "LightIntensityReading.h"

LightIntensityReading::LightIntensityReading(int16_t intensity, unsigned long timeStamp) :
		SensorReading(READ_OK, timeStamp), intensity(intensity) {
}

LightIntensityReading::LightIntensityReading(bool error, unsigned long timeStamp) :
		SensorReading(error ? READ_ERROR : NOT_YET_READ, timeStamp), intensity(-1) {
}

void LightIntensityReading::printValues(Print & out, NewLiner & newLine) const {
	char buffer[7];
	newLine.newLine(1);
	out.print(F("Intensity:"));
	dtostrf(intensity, 6, 0, buffer);
	out.print(buffer);
	out.print(F(" lux"));
	newLine.newLine(2);
	newLine.clearLine();
	newLine.newLine(3);
	newLine.clearLine();
}

const __FlashStringHelper * LightIntensityReading::getErrText() const {
	return F("light");
}

const __FlashStringHelper * LightIntensityReading::getNotYetMeasuredText() const {
	return F("Light");
}

const __FlashStringHelper * LightIntensityReading::getHeaderText() const {
	return F("Light");
}
