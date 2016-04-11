/*
 * temperatureMeasurement.cpp
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#include "TempReading.h"

TempReading::TempReading(float humidity, float temperatureCelsius,
                         float heatIndexCelsius, unsigned long timeStamp) :
        SensorReading(READ_OK, timeStamp),
        humidity(humidity),
        temperatureCelsius(temperatureCelsius),
        heatIndexCelsius(heatIndexCelsius) {
}

TempReading::TempReading(bool error, unsigned long timeStamp) :
        SensorReading(error ? READ_ERROR : NOT_YET_READ, timeStamp),
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

const __FlashStringHelper * TempReading::getHeaderText() const {
    return F("Thermometer");
}
