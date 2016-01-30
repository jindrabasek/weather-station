/*
 * SensorReading.h
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#ifndef SENSORREADING_H_
#define SENSORREADING_H_

#include <Arduino.h>
#include <LCD.h>
#include "defines.h"
#include "PeripheryReading.h"

class SensorReading: public PeripheryReading {
public:


#ifdef PRINT_TO_STREAM_SUPPORT
	class StreamNewLiner: public NewLiner {
		Stream & stream;
	public:
		StreamNewLiner(Stream & out) :
		stream(out) {
		}
		virtual void newLine(int lineNumber) {
			stream.println();
		}
	};
#endif


//-----------------------------------------------------------------------------

private:
	unsigned long timeStamp;

//-----------------------------------------------------------------------------

public:
	SensorReading(ReadState readState, unsigned long timeStamp);
	virtual ~SensorReading() {
	}

#ifdef PRINT_TO_STREAM_SUPPORT
	void printToStream(Stream & out) const;
#endif

	void printToDisplay(LCD & out) const;

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
