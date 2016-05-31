/*
 * SensorReading.cpp
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#include <sensors/SensorReading.h>

SensorReading::SensorReading(ReadState readState, unsigned long timeStamp) :
        readState(readState),
        timeStamp(timeStamp) {
}
