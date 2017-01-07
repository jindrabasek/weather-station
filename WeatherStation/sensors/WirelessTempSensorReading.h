/*
 * WirelessTempSensorSwsTsReading.h
 *
 *  Created on: 22. 5. 2016
 *      Author: jindra
 */

#ifndef WIRELESSTEMPSENSORREADING_H_
#define WIRELESSTEMPSENSORREADING_H_

#include <Print.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <stdint.h>


class WirelessTempSensorReading : public SensorReading {
private:
    uint8_t firstGlobalSensorId;
    float temperature;

//-----------------------------------------------------------------------------

public:
    enum WirelessTempSensorSwsTsIdLocal {
        L_WIRELESS_TEMPERTAURE_SWSTS,
        WirelessTempSensorSwsTsIdLocalEnumSize,
    };

    WirelessTempSensorReading(uint8_t firstGlobalSensorId, float temperature,
                unsigned long timeStamp);
    WirelessTempSensorReading(uint8_t firstGlobalSensorId, bool error = false, unsigned long timeStamp = 0);

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

#endif /* WIRELESSTEMPSENSORREADING_H_ */
