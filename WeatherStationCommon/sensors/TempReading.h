/*
 * temperatureMeasurement.h
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#ifndef TEMPREADING_H_
#define TEMPREADING_H_

#include <Print.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <stdbool.h>
#include <stdint.h>
#include <SensorIds.h>


class TempReading : public SensorReading {
private:
    uint8_t firstGlobalSensorId;
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


    TempReading(WeatherStation::SensorValueId firstGlobalSensorId,
                float humidity, float temperatureCelsius,
                unsigned long timeStamp);
    TempReading(WeatherStation::SensorValueId firstGlobalSensorId,
                bool error = false, unsigned long timeStamp = 0);

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
