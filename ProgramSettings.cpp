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

const float ProgramSettings::DEFAULT_ALTITUDE = 327.1f;

ProgramSettings::ProgramSettings() :
        altitude(DEFAULT_ALTITUDE),
        startupScreen(DEFAULT_STARTUP_SCREEN),
        measureTempFreq(DEFAULT_MEASURE_TEMP_FREQ),
        measurePressureFreq(DEFAULT_MEASURE_PRESSURE_FREQ),
        measureLightFreq(DEFAULT_MEASURE_LIGHT_FREQ),
        displayDrawFreq(DEFAULT_DISPLAY_DRAW_FREQ) {

    memcpy(wifiSsid, "***REMOVED***", 4);
    memcpy(wifiPasswd, "*********", 13);

    loadSettings();
}

void ProgramSettings::loadSettings() {
    if (!OMEEPROM::saved() || OMEEPROM::version() != SETTINGS_VERSION) {
        OMEEPROM::write(ALTITUDE_EPROM_ADDR, altitude);
        OMEEPROM::write(STARTUP_SCREEN_EPROM_ADDR, startupScreen);
        OMEEPROM::write(MEASURE_TEMP_FREQ_EPROM_ADDR, measureTempFreq);
        OMEEPROM::write(MEASURE_PRESSURE_FREQ_EPROM_ADDR, measurePressureFreq);
        OMEEPROM::write(MEASURE_LIGHT_FREQ_EPROM_ADDR, measureLightFreq);
        OMEEPROM::write(DISPLAY_DRAW_FREQ_EPROM_ADDR, displayDrawFreq);

        for (unsigned int i = 0; i < sizeof(wifiPasswd); i++) {
            EEPROM.update(WIFI_PASSWORD_EPROM_ADDR + i, wifiPasswd[i]);
        }
        for (unsigned int i = 0; i < sizeof(wifiSsid); i++) {
            EEPROM.update(WIFI_SSID_EPROM_ADDR + i, wifiSsid[i]);
        }

        OMEEPROM::version(SETTINGS_VERSION);
        OMEEPROM::saved(true);
    }

    OMEEPROM::read(ALTITUDE_EPROM_ADDR, altitude);
    OMEEPROM::read(STARTUP_SCREEN_EPROM_ADDR, startupScreen);
    OMEEPROM::read(MEASURE_TEMP_FREQ_EPROM_ADDR, measureTempFreq);
    OMEEPROM::read(MEASURE_PRESSURE_FREQ_EPROM_ADDR, measurePressureFreq);
    OMEEPROM::read(MEASURE_LIGHT_FREQ_EPROM_ADDR, measureLightFreq);
    OMEEPROM::read(DISPLAY_DRAW_FREQ_EPROM_ADDR, displayDrawFreq);

    for (unsigned int i = 0; i < sizeof(wifiPasswd); i++) {
        wifiPasswd[i] = EEPROM.read(WIFI_PASSWORD_EPROM_ADDR + i);
    }
    for (unsigned int i = 0; i < sizeof(wifiSsid); i++) {
        wifiSsid[i] = EEPROM.read(WIFI_SSID_EPROM_ADDR + i);
    }
}
