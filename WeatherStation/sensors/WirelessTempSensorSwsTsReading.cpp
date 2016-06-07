/*
 * WirelessTempSensorSwsTsReading.cpp
 *
 *  Created on: 22. 5. 2016
 *      Author: jindra
 */

#include "WirelessTempSensorSwsTsReading.h"

#include <math.h>
#include <Print.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <SensorIds.h>
#include <WString.h>


#define GLOBAL_SENSOR_ID WeatherStation::SensorValueId::WIRELESS_TEMPERTAURE_SWSTS_CH1 + (channel - 1)

WirelessTempSensorSwsTsReading::WirelessTempSensorSwsTsReading(
        uint8_t channel, float temperature, unsigned long timeStamp) :
        SensorReading(ReadState::READ_OK, timeStamp),
        channel(channel),
        temperature(temperature) {
}

WirelessTempSensorSwsTsReading::WirelessTempSensorSwsTsReading(
        uint8_t channel, bool error, unsigned long timeStamp) :
        SensorReading(error ? ReadState::READ_ERROR : ReadState::NOT_YET_READ,
                timeStamp),
        channel(channel),
        temperature(NAN) {
}

void WirelessTempSensorSwsTsReading::registerSensorValues(
        SensorReading** valueArray) {
    valueArray[GLOBAL_SENSOR_ID] = this;
}

uint8_t WirelessTempSensorSwsTsReading::printSensorName(Print & out) const {
    uint8_t size = out.print(F("433MHz Thermo CH"));
    return size + out.print(channel);
}

uint8_t WirelessTempSensorSwsTsReading::valuesCount() const {
    return WirelessTempSensorSwsTsIdLocal::WirelessTempSensorSwsTsIdLocalEnumSize;
}

void WirelessTempSensorSwsTsReading::printValue(uint8_t valueId, bool localId,
                                                Print& out,
                                                uint8_t maxLength) const {
    char buffer[maxLength + 1];
    buffer[0] = 0;

    ifIdMatchThenDo(
            WirelessTempSensorSwsTsIdLocal::L_WIRELESS_TEMPERTAURE_SWSTS,
            GLOBAL_SENSOR_ID, dtostrf(temperature, maxLength, 1, buffer));

    out.print(buffer);

}

double WirelessTempSensorSwsTsReading::getValue(uint8_t valueId, bool localId) const {

    ifIdMatchThenDo(
            WirelessTempSensorSwsTsIdLocal::L_WIRELESS_TEMPERTAURE_SWSTS,
            GLOBAL_SENSOR_ID, return temperature);

    return 0;
}

uint8_t WirelessTempSensorSwsTsReading::printValueName(uint8_t valueId,
bool localId,
                                                       Print& out) const {

    uint8_t length = 0;

    ifIdMatchThenDo(
            WirelessTempSensorSwsTsIdLocal::L_WIRELESS_TEMPERTAURE_SWSTS,
            GLOBAL_SENSOR_ID,
            length = out.print(F("Temp CH")) ; length += out.print(channel));

    return length;
}

WeatherStation::SensorValueUnit WirelessTempSensorSwsTsReading::valueUnit(
        uint8_t valueId, bool localId) const {

    ifIdMatchThenDo(
            WirelessTempSensorSwsTsIdLocal::L_WIRELESS_TEMPERTAURE_SWSTS,
            GLOBAL_SENSOR_ID,
            return WeatherStation::SensorValueUnit::DEGREE_CELSIUS);

    return WeatherStation::SensorValueUnit::N_A;
}
