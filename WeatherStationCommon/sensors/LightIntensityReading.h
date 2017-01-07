/*
 * LightIntensityReading.h
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#ifndef LIGHTINTENSITYREADING_H_
#define LIGHTINTENSITYREADING_H_

#include <Print.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <stdbool.h>
#include <stdint.h>
#include <SensorIds.h>


class LightIntensityReading : public SensorReading {
private:
    uint8_t firstGlobalSensorId;
    int16_t intensity;

//-----------------------------------------------------------------------------

public:
    enum LightSensorIdLocal {
        L_LIGHT_INTENSITY,
        LightSensorIdLocalEnumSize,
    };


    LightIntensityReading(WeatherStation::SensorValueId firstGlobalSensorId,
                          int16_t intensity, unsigned long timeStamp);
    LightIntensityReading(WeatherStation::SensorValueId firstGlobalSensorId,
                          bool error = false, unsigned long timeStamp = 0);

    int16_t getIntensity() const {
        return intensity;
    }

    void registerSensorValues(SensorReading** valueArray);

    virtual uint8_t printSensorName(Print & out) const;
    virtual uint8_t valuesCount() const;
    virtual void printValue(uint8_t valueId, bool localId, Print & out, uint8_t maxLength) const;
    virtual ValueType getValueType(uint8_t valueId, bool localId) const;
    virtual long getLongValue(uint8_t valueId, bool localId) const;
    virtual uint8_t printValueName(uint8_t valueId, bool localId, Print & out) const;
    virtual WeatherStation::SensorValueUnit valueUnit(uint8_t valueId, bool localId) const;

};

#endif /* LIGHTINTENSITYREADING_H_ */
