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

#include "SensorReading.h"
#include "Sensors.h"

class TempReading : public SensorReading {
private:
    float humidity;
    float humidityAbsolute;
    float temperatureCelsius;
    float heatIndexCelsius;

//-----------------------------------------------------------------------------

public:
    enum TempHumiditySensorIdLocal {
        L_DHT_HUMIDITY,
        L_DHT_TEMPERTAURE_REAL_FEEL,
        L_DHT_TEMPERTAURE,
        L_ABSOLUTE_HUMIDITY,
        TempHumiditySensorIdLocalEnumSize,
    };


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

    void registerSensorValues(SensorReading** valueArray);

    virtual uint8_t printSensorName(Print & out) const;
    virtual uint8_t valuesCount() const;
    virtual void printValue(uint8_t valueId, bool localId, Print & out, uint8_t maxLength) const;
    virtual uint8_t printValueName(uint8_t valueId, bool localId, Print & out) const;
    virtual WeatherStation::SensorValueUnit valueUnit(uint8_t valueId, bool localId) const;
};

#endif /* TEMPREADING_H_ */
