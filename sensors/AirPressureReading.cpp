/*
 * AirPressureReading.cpp
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#include "AirPressureReading.h"

#include <math.h>
#include <Print.h>
#include <stdint.h>
#include <stdlib.h>
#include <WString.h>

#include "../NewLiner.h"
#include "../PeripheryReading.h"
#include "Sensors.h"

AirPressureReading::AirPressureReading(float pressure, float pressureAtSeaLevel,
                                       float temperature,
                                       unsigned long timeStamp) :
        SensorReading(ReadState::READ_OK, timeStamp),
        pressure(pressure),
        pressureAtSeaLevel(pressureAtSeaLevel),
        temperature(temperature) {

}

AirPressureReading::AirPressureReading(bool error, unsigned long timeStamp) :
        SensorReading(error ? ReadState::READ_ERROR : ReadState::NOT_YET_READ, timeStamp),
        pressure(0),
        pressureAtSeaLevel(NAN),
        temperature(NAN) {
}

void AirPressureReading::printValues(Print & out, NewLiner & newLine) const {
    char buffer[13];
    newLine.newLine(1);
    out.print(F("Absolute:"));
    dtostrf(pressure, 7, 1, buffer);
    out.print(buffer);
    out.print(F(" hPa"));
    newLine.newLine(2);
    out.print(F("Sea lvl:"));
    dtostrf(pressureAtSeaLevel, 8, 1, buffer);
    out.print(buffer);
    out.print(F(" hPa"));
    newLine.newLine(3);
    out.print(F("Temp:"));
    dtostrf(temperature, 12, 2, buffer);
    out.print(buffer);
    out.print(F(" *C"));
}

const __FlashStringHelper * AirPressureReading::getErrText() const {
    return F("press");
}

const __FlashStringHelper * AirPressureReading::getNotYetMeasuredText() const {
    return F("Press");
}

const __FlashStringHelper * AirPressureReading::getHeaderText() const {
    return F("Barometer");
}

void AirPressureReading::registerSensorValues(SensorReading** valueArray) {
    valueArray[WeatherStation::Sensors::PRESSURE] = this;
    valueArray[WeatherStation::Sensors::PRESSURE_SEAL_LEVEL] = this;
    valueArray[WeatherStation::Sensors::BMP_TEMPERATURE] = this;
}

void AirPressureReading::printValue(uint8_t valueId, Print& out) {
    char buffer[WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH + 1];
    switch (valueId) {
        case WeatherStation::Sensors::PRESSURE:
            dtostrf(pressure, WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH, 1, buffer);
            break;
        case WeatherStation::Sensors::BMP_TEMPERATURE:
            dtostrf(temperature, WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH, 2, buffer);
            break;
        case WeatherStation::Sensors::PRESSURE_SEAL_LEVEL:
            dtostrf(pressureAtSeaLevel, WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH, 1, buffer);
            break;
    }
    out.print(buffer);
}
