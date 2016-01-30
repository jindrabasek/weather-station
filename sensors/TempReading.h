/*
 * temperatureMeasurement.h
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#ifndef TEMPREADING_H_
#define TEMPREADING_H_

#include <Arduino.h>
#include "SensorReading.h"

class TempReading : public SensorReading {
private:
	float humidity;
	float temperatureCelsius;
	float heatIndexCelsius;

//-----------------------------------------------------------------------------

public:	
	TempReading(float humidity, float temperatureCelsius,
			float heatIndexCelsius, unsigned long timeStamp);
	TempReading(bool error = false, unsigned long timeStamp = 0);

	float getHeatIndexCelsius() const {
		return heatIndexCelsius;
	}

	float getHumidity() const {
		return humidity;
	}

	float getTemperatureCelsius() const {
		return temperatureCelsius;
	}
	void printValues(Print & out, NewLiner & newLine) const;

protected:
	const __FlashStringHelper * getErrText() const;
	const __FlashStringHelper * getNotYetMeasuredText() const;
	const __FlashStringHelper * getHeaderText() const;
};

#endif /* TEMPREADING_H_ */
