/*
 * Sensors.cpp
 *
 *  Created on: 16. 5. 2016
 *      Author: jindra
 */

#include "Sensors.h"

#include <avr/pgmspace.h>
#include <BitBool.h>
#include <Print.h>
#include <stddef.h>
#include <stdint.h>
#include <WString.h>

static const char N_A_STR[] PROGMEM = "N/A";
static const char DEGREE_CELSIUS_STR[] PROGMEM = "*C";
static const char HECTOPASCAL_STR[] PROGMEM = "hPa";
static const char LIGHT_INTENSITY_LUX_STR[] PROGMEM = "lux";
static const char PERCENT_STR[] PROGMEM = "%";
static const char G_PER_CUBIC_METER_STR[] PROGMEM = "g/m3";

BitBool<WeatherStation::SensorValueId::SensorsEnumSize> WeatherStation::Sensors::sensorFlags[WeatherStation::ReadingUploader::ReadingUploaderSize] = {0};

static const char* const UNITS[] PROGMEM = { N_A_STR, DEGREE_CELSIUS_STR,
        HECTOPASCAL_STR, LIGHT_INTENSITY_LUX_STR, PERCENT_STR,
        G_PER_CUBIC_METER_STR };

uint8_t WeatherStation::Sensors::sensorUnitNameLength(SensorValueUnit unitId) {
    return strlen_P(reinterpret_cast<PGM_P>(pgm_read_word(&(UNITS[unitId]))));
}

void WeatherStation::Sensors::printSensorUnit(SensorValueUnit unitId,
                                              Print& out) {
    out.print(
            reinterpret_cast<const __FlashStringHelper *>(pgm_read_word(
                    &(UNITS[unitId]))));
}

void WeatherStation::Sensors::writeFlag(SensorValueId sensorId, bool value,
                                        ReadingUploader uploader) {
    if (uploader >= ReadingUploader::ReadingUploaderSize){
        for (int i = 0; i < ReadingUploader::ReadingUploaderSize; i++) {
            sensorFlags[i][sensorId] = value;
        }
    } else {
        sensorFlags[uploader][sensorId] = value;
    }
}

bool WeatherStation::Sensors::isFlag(SensorValueId sensorId,
                                     ReadingUploader uploader) {
    return sensorFlags[uploader][sensorId];
}
