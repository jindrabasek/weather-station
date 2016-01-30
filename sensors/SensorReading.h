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
#include "../PeripheryReading.h"
#include "../NewLiner.h"

class SensorReading: public PeripheryReading {

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

protected:
	virtual void printValues(Print & out, NewLiner & newLine) const =0;
	virtual const __FlashStringHelper * getErrText() const =0;
	virtual const __FlashStringHelper * getNotYetMeasuredText() const =0;

};

#endif /* SENSORREADING_H_ */
