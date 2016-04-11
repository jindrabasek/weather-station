/*
 * SensorReading.cpp
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#include "SensorReading.h"

SensorReading::SensorReading(ReadState readState, unsigned long timeStamp) :
        PeripheryReading(readState),
        timeStamp(timeStamp) {
}

void SensorReading::printTo(Print & out, NewLiner & newLine) const {
    if (getReadState() == READ_OK) {
        printValues(out, newLine);
    } else {
        for (uint8_t i = 1; i < 4; i++) {
            newLine.newLine(i);
            newLine.clearLine();
        }
        newLine.newLine(2);
        if (getReadState() == NOT_YET_READ) {
            out.print(getNotYetMeasuredText());
            out.print(F(" not yet read"));

        } else {
            out.print(F("Error reading "));
            out.print(getErrText());
        }

    }
}

