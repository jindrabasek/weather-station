/*
 * LightIntensityReading.h
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#ifndef LIGHTINTENSITYREADING_H_
#define LIGHTINTENSITYREADING_H_

#include <Print.h>
#include <stdbool.h>
#include <stdint.h>
#include <WString.h>

#include "../NewLiner.h"
#include "SensorReading.h"

class LightIntensityReading : public SensorReading {
private:
    int16_t intensity;

//-----------------------------------------------------------------------------

public:
    LightIntensityReading(int16_t intensity, unsigned long timeStamp);
    LightIntensityReading(bool error = false, unsigned long timeStamp = 0);

    int16_t getIntensity() const {
        return intensity;
    }
    void printValues(Print & out, NewLiner & newLine) const;

    virtual void registerSensorValues(SensorReading ** valueArray);
    virtual void printValue(uint8_t valueId, Print & out);

protected:
    const __FlashStringHelper * getErrText() const;
    const __FlashStringHelper * getNotYetMeasuredText() const;
    const __FlashStringHelper * getHeaderText() const;

};

#endif /* LIGHTINTENSITYREADING_H_ */
