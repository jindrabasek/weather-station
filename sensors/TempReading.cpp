/*
 * temperatureMeasurement.cpp
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#include "TempReading.h"

#include <math.h>
#include <Print.h>
#include <stdbool.h>
#include <stdlib.h>
#include <WString.h>

#include "../NewLiner.h"
#include "../PeripheryReading.h"
#include "Sensors.h"

TempReading::TempReading(float humidity, float temperatureCelsius,
                         float heatIndexCelsius, unsigned long timeStamp) :
        SensorReading(ReadState::READ_OK, timeStamp),
        humidity(humidity),
        temperatureCelsius(temperatureCelsius),
        heatIndexCelsius(heatIndexCelsius) {
}

TempReading::TempReading(bool error, unsigned long timeStamp) :
        SensorReading(error ? ReadState::READ_ERROR : ReadState::NOT_YET_READ, timeStamp),
        humidity(NAN),
        temperatureCelsius(NAN),
        heatIndexCelsius(NAN) {
}

void TempReading::printValues(Print & out, NewLiner & newLine) const {
    char buffer[13];
    newLine.newLine(1);
    out.print(F("Humidity:"));
    dtostrf(humidity, 9, 1, buffer);
    out.print(buffer);
    out.print(F(" %"));
    newLine.newLine(2);
    out.print(F("Temp:"));
    dtostrf(temperatureCelsius, 12, 2, buffer);
    out.print(buffer);
    out.print(F(" *C"));
    newLine.newLine(3);
    out.print(F("Real feel:"));
    dtostrf(heatIndexCelsius, 7, 2, buffer);
    out.print(buffer);
    out.print(F(" *C"));
}

const __FlashStringHelper * TempReading::getErrText() const {
    return F("temp");
}

const __FlashStringHelper * TempReading::getNotYetMeasuredText() const {
    return F("Temp");
}

void TempReading::registerSensorValues(SensorReading** valueArray) {
    valueArray[WeatherStation::Sensors::DHT_HUMIDITY] = this;
    valueArray[WeatherStation::Sensors::DHT_TEMPERTAURE] = this;
    valueArray[WeatherStation::Sensors::DHT_TEMPERTAURE_REAL_FEEL] = this;
}

void TempReading::printValue(int valueId, Print& out) {
    char buffer[WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH + 1] = {0};
    switch(valueId) {
        case WeatherStation::Sensors::DHT_HUMIDITY:
            dtostrf(humidity, WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH, 1, buffer);
            break;
        case WeatherStation::Sensors::DHT_TEMPERTAURE:
            dtostrf(temperatureCelsius, WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH, 2, buffer);
            break;
        case WeatherStation::Sensors::DHT_TEMPERTAURE_REAL_FEEL:
            dtostrf(heatIndexCelsius, WeatherStation::Sensors::PRINT_VALUE_STRING_LENGTH, 2, buffer);
            break;
    }
    out.print(buffer);
}

const __FlashStringHelper * TempReading::getHeaderText() const {
    return F("Thermometer");
}
