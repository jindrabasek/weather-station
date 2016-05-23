/*
 * ScreenToDraw.cpp
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#include "SensorReadingScreen.h"

#include <Arduino.h>
#include <LCD.h>
#include <stdbool.h>
#include <stdint.h>
#include <WString.h>

#include "../display/Display.h"
#include "../time/Clock.h"
#include "SensorReading.h"
#include "Sensors.h"

SensorReadingScreen::SensorReadingScreen(SensorReading & toDraw) :
        toDraw(toDraw) {
}

void SensorReadingScreen::draw(LCD & display) {
    display.setCursor(0, 0);
    toDraw.printSensorName(display);
    char buffer[9];
    Clock::timeToStr(Clock::getTime(true), buffer);
    display.setCursor(12, 0);
    display.print(buffer);

    if (toDraw.getReadState() == ReadState::READ_OK) {
        for (uint8_t i = 1; i < min(Display::ROWS, toDraw.valuesCount() + 1); i++) {
            Display::newLine(display, i);
            uint8_t nameLength = toDraw.printValueName(i - 1, true, display);
            display.print(':');
            WeatherStation::SensorValueUnit valueUnit = toDraw.valueUnit(i - 1,
                    true);
            toDraw.printValue(i - 1, true, display,
                    Display::COLUMNS - nameLength - 2
                            - WeatherStation::Sensors::sensorUnitNameLength(
                                    valueUnit));
            display.print(' ');
            WeatherStation::Sensors::printSensorUnit(valueUnit, display);
        }
    } else {
        for (uint8_t i = 1; i < 4; i++) {
            Display::newLine(display, i);
            Display::clearLine(display);
        }
        Display::newLine(display, 2);
        toDraw.printSensorName(display);
        if (toDraw.getReadState() == ReadState::NOT_YET_READ) {
            display.print(F(": N/A"));
        } else {
            display.print(F(": error"));
        }
    }
}

