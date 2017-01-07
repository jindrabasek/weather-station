/*
 * LightIntensityReading.cpp
 *
 *  Created on: 18. 1. 2016
 *      Author: jindra
 */

#include "LightIntensityReading.h"

#include <Print.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <SensorIds.h>
#include <WString.h>


LightIntensityReading::LightIntensityReading(WeatherStation::SensorValueId firstGlobalSensorId,
                                             int16_t intensity,
                                             unsigned long timeStamp) :
        SensorReading(ReadState::READ_OK, timeStamp),
        firstGlobalSensorId((uint8_t)firstGlobalSensorId),
        intensity(intensity) {
}

LightIntensityReading::LightIntensityReading(WeatherStation::SensorValueId firstGlobalSensorId,
                                             bool error,
                                             unsigned long timeStamp) :
        SensorReading(error ? ReadState::READ_ERROR : ReadState::NOT_YET_READ, timeStamp),
        firstGlobalSensorId((uint8_t)firstGlobalSensorId),
        intensity(-1) {
}

void LightIntensityReading::registerSensorValues(SensorReading** valueArray) {
    valueArray[firstGlobalSensorId + LightSensorIdLocal::L_LIGHT_INTENSITY] = this;
}

uint8_t LightIntensityReading::printSensorName(Print & out) const
{
    return out.print(F("Light ")) + out.print(firstGlobalSensorId);
}

uint8_t LightIntensityReading::valuesCount() const {
    return LightSensorIdLocal::LightSensorIdLocalEnumSize;
}

void LightIntensityReading::printValue(uint8_t valueId, bool localId, Print& out,
                                    uint8_t maxLength) const {
    char buffer[maxLength + 1];
    buffer[0] = 0;

    ifIdMatchThenDo(LightSensorIdLocal::L_LIGHT_INTENSITY,
            firstGlobalSensorId + LightSensorIdLocal::L_LIGHT_INTENSITY,
            dtostrf(intensity, maxLength, 0, buffer));

    out.print(buffer);
}

ValueType LightIntensityReading::getValueType(uint8_t valueId, bool localId) const {
    ifIdMatchThenDo(LightSensorIdLocal::L_LIGHT_INTENSITY,
                firstGlobalSensorId + LightSensorIdLocal::L_LIGHT_INTENSITY,
                return ValueType::LONG);

    return ValueType::NA;
}

long LightIntensityReading::getLongValue(uint8_t valueId, bool localId) const {

    ifIdMatchThenDo(LightSensorIdLocal::L_LIGHT_INTENSITY,
            firstGlobalSensorId + LightSensorIdLocal::L_LIGHT_INTENSITY,
            return intensity);

    return 0;
}

uint8_t LightIntensityReading::printValueName(uint8_t valueId, bool localId,
                                           Print& out) const {

    uint8_t length = 0;

    ifIdMatchThenDo(LightSensorIdLocal::L_LIGHT_INTENSITY,
            firstGlobalSensorId + LightSensorIdLocal::L_LIGHT_INTENSITY,
            length = out.print(F("Intensity")));
    return length;
}

WeatherStation::SensorValueUnit LightIntensityReading::valueUnit(
        uint8_t valueId, bool localId) const {

    ifIdMatchThenDo(LightSensorIdLocal::L_LIGHT_INTENSITY,
            firstGlobalSensorId + LightSensorIdLocal::L_LIGHT_INTENSITY,
            return WeatherStation::SensorValueUnit::LIGHT_INTENSITY_LUX);

    return WeatherStation::SensorValueUnit::N_A;
}
