/*
 * WirelessTempSensorSwsTsReading.h
 *
 *  Created on: 22. 5. 2016
 *      Author: jindra
 */

#ifndef WIRELESSTEMPSENSORSWSTSREADING_H_
#define WIRELESSTEMPSENSORSWSTSREADING_H_

#include <Print.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <stdint.h>


class WirelessTempSensorSwsTsReading : public SensorReading {
private:
    uint8_t channel;
    float temperature;

//-----------------------------------------------------------------------------

public:
    enum WirelessTempSensorSwsTsIdLocal {
        L_WIRELESS_TEMPERTAURE_SWSTS,
        WirelessTempSensorSwsTsIdLocalEnumSize,
    };


    WirelessTempSensorSwsTsReading(uint8_t channel, float temperature,
                unsigned long timeStamp);
    WirelessTempSensorSwsTsReading(uint8_t channel, bool error = false, unsigned long timeStamp = 0);

    float getTemperature() const {
        return temperature;
    }

    void registerSensorValues(SensorReading** valueArray);

    virtual uint8_t printSensorName(Print & out) const;
    virtual uint8_t valuesCount() const;
    virtual void printValue(uint8_t valueId, bool localId, Print & out, uint8_t maxLength) const;
    virtual double getValue(uint8_t valueId, bool localId) const;
    virtual uint8_t printValueName(uint8_t valueId, bool localId, Print & out) const;
    virtual WeatherStation::SensorValueUnit valueUnit(uint8_t valueId, bool localId) const;
};

#endif /* WIRELESSTEMPSENSORSWSTSREADING_H_ */
