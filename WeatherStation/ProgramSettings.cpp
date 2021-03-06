/*
 * ProgramSettings.cpp
 *
 *  Created on: 22. 1. 2016
 *      Author: jindra
 */

#include "ProgramSettings.h"

#include <EEPROM.h>
#include <OMEEPROM.h>
#include <stdbool.h>
#include <string.h>

#include "config.h"

const float ProgramSettings::DEFAULT_ALTITUDE = 327.1f;

ProgramSettings::ProgramSettings() {
    loadSettings();
}

void ProgramSettings::loadSettings() {
    if (!OMEEPROM::saved() || OMEEPROM::version() != SETTINGS_VERSION) {
        OMEEPROM::writeConst(ALTITUDE_EPROM_ADDR, DEFAULT_ALTITUDE);
        OMEEPROM::writeConst(STARTUP_SCREEN_EPROM_ADDR, DEFAULT_STARTUP_SCREEN);
        OMEEPROM::writeConst(MEASURE_TEMP_FREQ_EPROM_ADDR,
                DEFAULT_MEASURE_TEMP_FREQ);
        OMEEPROM::writeConst(MEASURE_PRESSURE_FREQ_EPROM_ADDR,
                DEFAULT_MEASURE_PRESSURE_FREQ);
        OMEEPROM::writeConst(MEASURE_LIGHT_FREQ_EPROM_ADDR,
                DEFAULT_MEASURE_LIGHT_FREQ);
        OMEEPROM::writeConst(DISPLAY_DRAW_FREQ_EPROM_ADDR,
                DEFAULT_DISPLAY_DRAW_FREQ);

        OMEEPROM::writeConst(TIME_ZONE_EPROM_ADDR, DEFAULT_TIME_ZONE);
        OMEEPROM::writeConst(SYNC_TIME_FREQ_EPROM_ADDR, DEFAULT_SYNC_TIME_FREQ);
        OMEEPROM::writeConst(DATA_UPLOAD_MIN_EPROM_ADDR,
                DEFAULT_DATA_UPLOAD_MIN_FREQ);
        OMEEPROM::writeConst(WIFI_WATCHDOG_MIN_EPROM_ADDR,
                DEFAULT_WIFI_WATCHDOG_MIN_FREQ);

        OMEEPROM::version(SETTINGS_VERSION);
        OMEEPROM::saved(true);
    }
}
