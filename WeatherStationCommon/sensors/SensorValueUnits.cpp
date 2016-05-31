/*
 * Sensors.cpp
 *
 *  Created on: 16. 5. 2016
 *      Author: jindra
 */

#include <avr/pgmspace.h>
#include <Print.h>
#include <sensors/SensorValueUnits.h>
#include <stdint.h>
#include <WString.h>

static const char N_A_STR[] PROGMEM = "N/A";
static const char DEGREE_CELSIUS_STR[] PROGMEM = "*C";
static const char HECTOPASCAL_STR[] PROGMEM = "hPa";
static const char LIGHT_INTENSITY_LUX_STR[] PROGMEM = "lux";
static const char PERCENT_STR[] PROGMEM = "%";
static const char G_PER_CUBIC_METER_STR[] PROGMEM = "g/m3";

static const char* const UNITS[] PROGMEM = { N_A_STR, DEGREE_CELSIUS_STR,
        HECTOPASCAL_STR, LIGHT_INTENSITY_LUX_STR, PERCENT_STR,
        G_PER_CUBIC_METER_STR };

uint8_t WeatherStation::SensorValueUnits::sensorUnitNameLength(SensorValueUnit unitId) {
    return strlen_P(reinterpret_cast<PGM_P>(pgm_read_word(&(UNITS[unitId]))));
}

void WeatherStation::SensorValueUnits::printSensorUnit(SensorValueUnit unitId,
                                              Print& out) {
    out.print(
            reinterpret_cast<const __FlashStringHelper *>(pgm_read_word(
                    &(UNITS[unitId]))));
}
