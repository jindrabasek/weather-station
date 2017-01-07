/*
 * WirelessTempSensorSwsTsReading.cpp
 *
 *  Created on: 22. 5. 2016
 *      Author: jindra
 */

#include "WirelessTempSensorReading.h"

#include <math.h>
#include <Print.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <WString.h>

WirelessTempSensorReading::WirelessTempSensorReading(
        uint8_t firstGlobalSensorId, float temperature, unsigned long timeStamp) :
        SensorReading(ReadState::READ_OK, timeStamp),
        firstGlobalSensorId(firstGlobalSensorId),
        temperature(temperature) {
}

WirelessTempSensorReading::WirelessTempSensorReading(
        uint8_t firstGlobalSensorId, bool error, unsigned long timeStamp) :
        SensorReading(error ? ReadState::READ_ERROR : ReadState::NOT_YET_READ,
                timeStamp),
        firstGlobalSensorId(firstGlobalSensorId),
        temperature(NAN) {
}

void WirelessTempSensorReading::registerSensorValues(
        SensorReading** valueArray) {
    valueArray[firstGlobalSensorId] = this;
}

uint8_t WirelessTempSensorReading::printSensorName(Print & out) const {
    uint8_t size = out.print(F("433MHz Thermo "));
    return size + out.print(firstGlobalSensorId);
}

uint8_t WirelessTempSensorReading::valuesCount() const {
    return WirelessTempSensorSwsTsIdLocal::WirelessTempSensorSwsTsIdLocalEnumSize;
}

void WirelessTempSensorReading::printValue(uint8_t valueId, bool localId,
                                           Print& out,
                                           uint8_t maxLength) const {
    char buffer[maxLength + 1];
    buffer[0] = 0;

    ifIdMatchThenDo(
            WirelessTempSensorSwsTsIdLocal::L_WIRELESS_TEMPERTAURE_SWSTS,
            firstGlobalSensorId, dtostrf(temperature, maxLength, 1, buffer));

    out.print(buffer);

}

double WirelessTempSensorReading::getDoubleValue(uint8_t valueId,
                                                 bool localId) const {

    ifIdMatchThenDo(
            WirelessTempSensorSwsTsIdLocal::L_WIRELESS_TEMPERTAURE_SWSTS,
            firstGlobalSensorId, return temperature);

    return 0;
}

uint8_t WirelessTempSensorReading::printValueName(uint8_t valueId,
                                                  bool localId,
                                                  Print& out) const {

    uint8_t length = 0;

    ifIdMatchThenDo(
            WirelessTempSensorSwsTsIdLocal::L_WIRELESS_TEMPERTAURE_SWSTS,
            firstGlobalSensorId,
            length = out.print(F("W Temp ")) ; length += out.print(firstGlobalSensorId));

    return length;
}

WeatherStation::SensorValueUnit WirelessTempSensorReading::valueUnit(
        uint8_t valueId, bool localId) const {

    ifIdMatchThenDo(
            WirelessTempSensorSwsTsIdLocal::L_WIRELESS_TEMPERTAURE_SWSTS,
            firstGlobalSensorId,
            return WeatherStation::SensorValueUnit::DEGREE_CELSIUS);

    return WeatherStation::SensorValueUnit::N_A;
}
