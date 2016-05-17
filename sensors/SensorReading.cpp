/*
 * SensorReading.cpp
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#include "SensorReading.h"

#include "../PeripheryReading.h"

SensorReading::SensorReading(ReadState readState, unsigned long timeStamp) :
        PeripheryReading(readState),
        timeStamp(timeStamp) {
}
