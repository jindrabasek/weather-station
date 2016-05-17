/*
 * SensorReading.h
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#ifndef SENSORREADING_H_
#define SENSORREADING_H_

#include <Print.h>
#include <stdint.h>
#include <WString.h>

#include "../PeripheryReading.h"
#include "Sensors.h"

#define ifIdMatchThenDo(lcId,gbId,doWork)  \
{                                                   \
    if ((localId && valueId == lcId) || \
            (!localId && valueId == gbId)) {\
        doWork; \
    } \
}

#define elseifIdMatchThenDo(lcId,gbId,doWork)  \
{                                                   \
    if ((localId && valueId == lcId) || \
            (!localId && valueId == gbId)) {\
        doWork; \
    } \
}

// Do not define virtual destructor on purpose - class
// and its children is not expected to need destructors,
// it saves a lot of SRAM otherwise occupied by VTABLE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class SensorReading : public PeripheryReading {

private:
    unsigned long timeStamp;

//-----------------------------------------------------------------------------

public:
    SensorReading(ReadState readState, unsigned long timeStamp);

    unsigned long getTimeStamp() const {
        return timeStamp;
    }

    virtual const __FlashStringHelper * getSensorName() const =0;
    virtual uint8_t valuesCount() const =0;
    virtual void printValue(uint8_t valueId, bool localId, Print & out, uint8_t maxLength) const =0;
    virtual uint8_t printValueName(uint8_t valueId, bool localId, Print & out) const =0;
    virtual WeatherStation::SensorValueUnit valueUnit(uint8_t valueId, bool localId) const =0;

};

#pragma GCC diagnostic pop

#endif /* SENSORREADING_H_ */
