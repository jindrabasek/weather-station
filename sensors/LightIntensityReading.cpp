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

#include "SensorReading.h"
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

void LightIntensityReading::registerSensorValues(SensorReading** valueArray) {
    valueArray[WeatherStation::SensorValueId::LIGHT_INTENSITY] = this;
}

uint8_t LightIntensityReading::printSensorName(Print & out) const
{
    return out.print(F("Light"));
}

uint8_t LightIntensityReading::valuesCount() const {
    return LightSensorIdLocal::LightSensorIdLocalEnumSize;
}

void LightIntensityReading::printValue(uint8_t valueId, bool localId, Print& out,
                                    uint8_t maxLength) const {
    char buffer[maxLength + 1];
    buffer[0] = 0;

    ifIdMatchThenDo(LightSensorIdLocal::L_LIGHT_INTENSITY,
            WeatherStation::SensorValueId::LIGHT_INTENSITY,
            dtostrf(intensity, maxLength, 0, buffer));

    out.print(buffer);
}

uint8_t LightIntensityReading::printValueName(uint8_t valueId, bool localId,
                                           Print& out) const {

    uint8_t length = 0;

    ifIdMatchThenDo(LightSensorIdLocal::L_LIGHT_INTENSITY,
            WeatherStation::SensorValueId::LIGHT_INTENSITY,
            length = out.print(F("Intensity")));
    return length;
}

WeatherStation::SensorValueUnit LightIntensityReading::valueUnit(
        uint8_t valueId, bool localId) const {

    ifIdMatchThenDo(LightSensorIdLocal::L_LIGHT_INTENSITY,
            WeatherStation::SensorValueId::LIGHT_INTENSITY,
            return WeatherStation::SensorValueUnit::LIGHT_INTENSITY_LUX);

    return WeatherStation::SensorValueUnit::N_A;
}
