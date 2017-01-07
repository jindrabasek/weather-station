/*
 * AirPressureReading.h
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#ifndef AIRPRESSUREREADING_H_
#define AIRPRESSUREREADING_H_

#include <Print.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <stdbool.h>
#include <stdint.h>


class AirPressureReading : public SensorReading {
private:
    float pressure;
    float pressureAtSeaLevel;
    float temperature;

//-----------------------------------------------------------------------------

public:
    enum AirPressureSensorIdLocal {
        L_PRESSURE,
        L_PRESSURE_SEAL_LEVEL,
        L_BMP_TEMPERATURE,
        AirPressureSensorIdLocalEnumSize,
    };

    AirPressureReading(float preassure, float pressureAtSeaLevel,
                       float temperature, unsigned long timeStamp);
    AirPressureReading(bool error = false, unsigned long timeStamp = 0);

    float getPressureAtSeaLevel() const {
        return pressureAtSeaLevel;
    }

    float getPressure() const {
        return pressure;
    }

    float getTemperature() const {
        return temperature;
    }

    void registerSensorValues(SensorReading** valueArray);

    virtual uint8_t printSensorName(Print & out) const;
    virtual uint8_t valuesCount() const;
    virtual void printValue(uint8_t valueId, bool localId, Print & out, uint8_t maxLength) const;
    virtual double getDoubleValue(uint8_t valueId, bool localId) const;
    virtual uint8_t printValueName(uint8_t valueId, bool localId, Print & out) const;
    virtual WeatherStation::SensorValueUnit valueUnit(uint8_t valueId, bool localId) const;
};

#endif /* AIRPRESSUREREADING_H_ */
