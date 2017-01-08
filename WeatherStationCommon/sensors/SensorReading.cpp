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

// by default return double
ValueType SensorReading::getValueType(uint8_t valueId, bool localId) const {
    return ValueType::DOUBLE;
}

double SensorReading::getDoubleValue(uint8_t valueId, bool localId) const {
    return (double) getLongValue(valueId, localId);
}

long SensorReading::getLongValue(uint8_t valueId, bool localId) const {
    return (double) getDoubleValue(valueId, localId);
}
