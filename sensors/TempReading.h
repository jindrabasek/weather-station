/*
 * temperatureMeasurement.h
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#ifndef TEMPREADING_H_
#define TEMPREADING_H_

#include <Print.h>
#include <stdbool.h>
#include <stdint.h>
#include <WString.h>

#include "../NewLiner.h"
#include "SensorReading.h"

class TempReading : public SensorReading {
private:
    float humidity;
    float humidityAbsolute;
    float temperatureCelsius;
    float heatIndexCelsius;

//-----------------------------------------------------------------------------

public:
    TempReading(float humidity, float humidityAbsolute,
                float temperatureCelsius, float heatIndexCelsius,
                unsigned long timeStamp);
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

    float getHumidityAbsolute() const {
        return humidityAbsolute;
    }

    void printValues(Print & out, NewLiner & newLine) const;

    virtual void registerSensorValues(SensorReading ** valueArray);
    virtual void printValue(uint8_t valueId, Print & out);

protected:
    const __FlashStringHelper * getErrText() const;
    const __FlashStringHelper * getNotYetMeasuredText() const;
    const __FlashStringHelper * getHeaderText() const;
};

#endif /* TEMPREADING_H_ */
