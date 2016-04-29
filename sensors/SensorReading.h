/*
 * SensorReading.h
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#ifndef SENSORREADING_H_
#define SENSORREADING_H_

#include <Print.h>
#include <WString.h>

#include "../NewLiner.h"
#include "../PeripheryReading.h"

class SensorReading : public PeripheryReading {

private:
    unsigned long timeStamp;

//-----------------------------------------------------------------------------

public:
    SensorReading(ReadState readState, unsigned long timeStamp);
    virtual ~SensorReading() {
    }

    unsigned long getTimeStamp() const {
        return timeStamp;
    }

    virtual const __FlashStringHelper * getHeaderText() const =0;
    void printTo(Print & out, NewLiner & newLine) const;

    virtual void registerSensorValues(SensorReading ** valueArray) =0;
    virtual void printValue(int valueId, Print & out) =0;

protected:
    virtual void printValues(Print & out, NewLiner & newLine) const =0;
    virtual const __FlashStringHelper * getErrText() const =0;
    virtual const __FlashStringHelper * getNotYetMeasuredText() const =0;

};

#endif /* SENSORREADING_H_ */
