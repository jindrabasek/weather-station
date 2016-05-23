/*
 * AirPressureReading.cpp
 *
 *  Created on: 15. 1. 2016
 *      Author: jindra
 */

#include "AirPressureReading.h"

#include <math.h>
#include <Print.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <WString.h>

#include "SensorReading.h"
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
        SensorReading(error ? ReadState::READ_ERROR : ReadState::NOT_YET_READ,
                timeStamp),
        pressure(0),
        pressureAtSeaLevel(NAN),
        temperature(NAN) {
}

void AirPressureReading::registerSensorValues(SensorReading** valueArray) {
    valueArray[WeatherStation::SensorValueId::PRESSURE] = this;
    valueArray[WeatherStation::SensorValueId::PRESSURE_SEAL_LEVEL] = this;
    valueArray[WeatherStation::SensorValueId::BMP_TEMPERATURE] = this;
}

uint8_t AirPressureReading::printSensorName(Print & out) const
{
    return out.print(F("Barometer"));
}

uint8_t AirPressureReading::valuesCount() const {
    return AirPressureSensorIdLocal::AirPressureSensorIdLocalEnumSize;
}

void AirPressureReading::printValue(uint8_t valueId, bool localId, Print& out,
                                    uint8_t maxLength) const {
    char buffer[maxLength + 1];
    buffer[0] = 0;

    ifIdMatchThenDo(AirPressureSensorIdLocal::L_PRESSURE,
            WeatherStation::SensorValueId::PRESSURE,
            dtostrf(pressure, maxLength, 1, buffer));

    elseifIdMatchThenDo(AirPressureSensorIdLocal::L_BMP_TEMPERATURE,
            WeatherStation::SensorValueId::BMP_TEMPERATURE,
            dtostrf(temperature, maxLength, 2, buffer));

    elseifIdMatchThenDo(AirPressureSensorIdLocal::L_PRESSURE_SEAL_LEVEL,
            WeatherStation::SensorValueId::PRESSURE_SEAL_LEVEL,
            dtostrf(pressureAtSeaLevel, maxLength, 1, buffer));

    out.print(buffer);

}

uint8_t AirPressureReading::printValueName(uint8_t valueId, bool localId,
                                           Print& out) const {

    uint8_t length = 0;

    ifIdMatchThenDo(AirPressureSensorIdLocal::L_PRESSURE,
            WeatherStation::SensorValueId::PRESSURE,
            length = out.print(F("Absolute")));

    elseifIdMatchThenDo(AirPressureSensorIdLocal::L_BMP_TEMPERATURE,
            WeatherStation::SensorValueId::BMP_TEMPERATURE,
            length = out.print(F("Temp")));

    elseifIdMatchThenDo(AirPressureSensorIdLocal::L_PRESSURE_SEAL_LEVEL,
            WeatherStation::SensorValueId::PRESSURE_SEAL_LEVEL,
            length = out.print(F("Sea lvl")));

    return length;
}

WeatherStation::SensorValueUnit AirPressureReading::valueUnit(
        uint8_t valueId, bool localId) const {

    ifIdMatchThenDo(AirPressureSensorIdLocal::L_PRESSURE,
            WeatherStation::SensorValueId::PRESSURE,
            return WeatherStation::SensorValueUnit::HECTOPASCAL);

    ifIdMatchThenDo(AirPressureSensorIdLocal::L_BMP_TEMPERATURE,
            WeatherStation::SensorValueId::BMP_TEMPERATURE,
            return WeatherStation::SensorValueUnit::DEGREE_CELSIUS);

    ifIdMatchThenDo(AirPressureSensorIdLocal::L_PRESSURE_SEAL_LEVEL,
            WeatherStation::SensorValueId::PRESSURE_SEAL_LEVEL,
            return WeatherStation::SensorValueUnit::HECTOPASCAL);

    return WeatherStation::SensorValueUnit::N_A;
}
