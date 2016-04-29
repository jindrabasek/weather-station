/*
 * AirPressureReading.h
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#ifndef AIRPRESSUREREADING_H_
#define AIRPRESSUREREADING_H_

#include <Print.h>
#include <WString.h>

#include "../NewLiner.h"
#include "SensorReading.h"

class AirPressureReading : public SensorReading {
private:
    float pressure;
    float pressureAtSeaLevel;
    float temperature;

//-----------------------------------------------------------------------------

public:
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
    void printValues(Print & out, NewLiner & newLine) const;

    virtual void registerSensorValues(SensorReading ** valueArray);
    virtual void printValue(int valueId, Print & out);

protected:
    const __FlashStringHelper * getErrText() const;
    const __FlashStringHelper * getNotYetMeasuredText() const;
    const __FlashStringHelper * getHeaderText() const;

};

#endif /* AIRPRESSUREREADING_H_ */
