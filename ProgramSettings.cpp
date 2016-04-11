/*
 * ProgramSettings.cpp
 *
 *  Created on: 22. 1. 2016
 *      Author: jindra
 */

#include "ProgramSettings.h"

#include <OMEEPROM.h>
#include <stdbool.h>

const float ProgramSettings::DEFAULT_ALTITUDE = 327.1f;

ProgramSettings::ProgramSettings() :
        altitude(DEFAULT_ALTITUDE),
        startupScreen(DEFAULT_STARTUP_SCREEN),
        measureTempFreq(DEFAULT_MEASURE_TEMP_FREQ),
        measurePressureFreq(DEFAULT_MEASURE_PRESSURE_FREQ),
        measureLightFreq(DEFAULT_MEASURE_LIGHT_FREQ),
        displayDrawFreq(DEFAULT_DISPLAY_DRAW_FREQ) {

    loadSettings();
}

void ProgramSettings::loadSettings() {
    if (!OMEEPROM::saved()) {

        OMEEPROM::write(ALTITUDE_EPROM_ADDR, altitude);
        OMEEPROM::write(STARTUP_SCREEN_EPROM_ADDR, startupScreen);
        OMEEPROM::write(MEASURE_TEMP_FREQ_EPROM_ADDR, measureTempFreq);
        OMEEPROM::write(MEASURE_PRESSURE_FREQ_EPROM_ADDR, measurePressureFreq);
        OMEEPROM::write(MEASURE_LIGHT_FREQ_EPROM_ADDR, measureLightFreq);
        OMEEPROM::write(DISPLAY_DRAW_FREQ_EPROM_ADDR, displayDrawFreq);

        OMEEPROM::saved(true);
    } else {
        OMEEPROM::read(ALTITUDE_EPROM_ADDR, altitude);
        OMEEPROM::read(STARTUP_SCREEN_EPROM_ADDR, startupScreen);
        OMEEPROM::read(MEASURE_TEMP_FREQ_EPROM_ADDR, measureTempFreq);
        OMEEPROM::read(MEASURE_PRESSURE_FREQ_EPROM_ADDR, measurePressureFreq);
        OMEEPROM::read(MEASURE_LIGHT_FREQ_EPROM_ADDR, measureLightFreq);
        OMEEPROM::read(DISPLAY_DRAW_FREQ_EPROM_ADDR, displayDrawFreq);
    }
}
