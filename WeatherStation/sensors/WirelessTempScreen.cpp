/*
 * WirelessTempScreen.cpp
 *
 *  Created on: 18. 6. 2016
 *      Author: jindra
 */

#include "WirelessTempScreen.h"

#include <avr/pgmspace.h>
#include <LCD.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <stdbool.h>
#include <stdint.h>
#include <time/Clock.h>
#include <WString.h>

#include "../display/Display.h"
#include "../ProgramState.h"

extern ProgramState *state;

WirelessTempScreen::WirelessTempScreen(uint8_t firstGlobalSensorId, PGM_P screenLabel) :
        firstGlobalSensorId(firstGlobalSensorId), screenLabel(screenLabel) {
}

void WirelessTempScreen::draw(LCD& display) {

    display.setCursor(0, 0);
    display.print((const __FlashStringHelper *) screenLabel);
    char buffer[9];
    Clock::timeToStr(Clock::getTime(true), buffer);
    display.setCursor(12, 0);
    display.print(buffer);

    for (uint8_t i = firstGlobalSensorId; i < firstGlobalSensorId + MAX_CHANNELS; i++) {
        SensorReading* toDraw = state->getSensorValues()[i];
        if (toDraw != NULL) {
            Display::newLine(display, (i - firstGlobalSensorId) + 1);
            uint8_t nameLength = toDraw->printValueName(i, false, display);
            display.print(':');

            if (toDraw->getReadState() == ReadState::READ_OK) {
                WeatherStation::SensorValueUnit valueUnit = toDraw->valueUnit(i,
                        false);
                toDraw->printValue(i, false, display,
                        Display::COLUMNS - nameLength - 2
                                - WeatherStation::SensorValueUnits::sensorUnitNameLength(
                                        valueUnit));
                display.print(' ');
                WeatherStation::SensorValueUnits::printSensorUnit(valueUnit, display);
            } else if (toDraw->getReadState() == ReadState::NOT_YET_READ) {
                display.print(F(" N/A"));
            } else {
                display.print(F(" err"));
            }
        }
    }
}
