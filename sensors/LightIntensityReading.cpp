/*
 * LightIntensityReading.cpp
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#include "LightIntensityReading.h"

#include <Print.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <WString.h>

#include "../NewLiner.h"
#include "../PeripheryReading.h"
#include "Sensors.h"

LightIntensityReading::LightIntensityReading(int16_t intensity,
                                             unsigned long timeStamp) :
        SensorReading(ReadState::READ_OK, timeStamp),
        intensity(intensity) {
}

LightIntensityReading::LightIntensityReading(bool error,
                                             unsigned long timeStamp) :
        SensorReading(error ? ReadState::READ_ERROR : ReadState::NOT_YET_READ, timeStamp),
        intensity(-1) {
}

void LightIntensityReading::printValues(Print & out, NewLiner & newLine) const {
    char buffer[7];
    newLine.newLine(1);
    out.print(F("Intensity:"));
    dtostrf(intensity, 6, 0, buffer);
    out.print(buffer);
    out.print(F(" lux"));
    newLine.newLine(2);
    newLine.clearLine();
    newLine.newLine(3);
    newLine.clearLine();
}

const __FlashStringHelper * LightIntensityReading::getErrText() const {
    return F("light");
}

const __FlashStringHelper * LightIntensityReading::getNotYetMeasuredText() const {
    return F("Light");
}

void LightIntensityReading::registerSensorValues(SensorReading** valueArray) {
    valueArray[WeatherStation::Sensors::LIGHT_INTENSITY] = this;
}

void LightIntensityReading::printValue(uint8_t valueId, Print& out) {
    char buffer[WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH + 1];
    switch (valueId) {
        case WeatherStation::Sensors::LIGHT_INTENSITY:
            dtostrf(intensity, WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH, 0, buffer);
            break;
    }
    out.print(buffer);
}

const __FlashStringHelper * LightIntensityReading::getHeaderText() const {
    return F("Light");
}
