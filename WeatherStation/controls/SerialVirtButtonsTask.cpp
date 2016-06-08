/*
 * SerialVirtButtonsTask.cpp
 *
 *  Created on: 14. 2. 2016
 *      Author: jindra
 */

#include "SerialVirtButtonsTask.h"

#include <ButtonHandler.h>
#include <Debouncer.h>
#include <HardwareSerial.h>
#include <Logger.h>
#include <PciManagerLock.h>

#include "../ProgramState.h"
#include "Buttons.h"

extern ProgramState *state;

SerialVirtButtonsTask::SerialVirtButtonsTask(unsigned long periodMs) :
        Task(periodMs) {
    pinMode(DO_RESET_PIN, OUTPUT);
}

void SerialVirtButtonsTask::doReset() {
    Serial.println(F("Device will reboot."));
    delay(RESET_DELAY);
    digitalWrite(DO_RESET_PIN, HIGH);
}

void SerialVirtButtonsTask::run() {
    // check if new serial input is available
    if (Serial.available()) {
        // read one char from input buffer
        char input = Serial.read();

        {
            PciManagerLock lock;
            switch (input) {
                case UP_CHAR:
                    state->getButtons()[WeatherStation::Buttons::UP].getHandler()->onPressed();
                    break;
                case DOWN_CHAR:
                    state->getButtons()[WeatherStation::Buttons::DOWN].getHandler()->onPressed();
                    break;
                /*case LEFT_CHAR:
                    state->getButtons()[WeatherStation::Buttons::LEFT].getHandler()->onPressed();
                    break;
                case RIGHT_CHAR:
                    state->getButtons()[WeatherStation::Buttons::RIGHT].getHandler()->onPressed();
                    break;*/
                case BACKLIGHT_CHAR:
                    state->getButtons()[WeatherStation::Buttons::BACKLIGHT].getHandler()->onPressed();
                    break;
                case ENTER_CHAR:
                    state->getButtons()[WeatherStation::Buttons::ENTER].getHandler()->onPressed();
                    break;
                case ESC_CHAR:
                    state->getButtons()[WeatherStation::Buttons::ESC].getHandler()->onPressed();
                    break;
                case RESET_CHAR:
                    doReset();
                    break;
                case LOG_DUMP_CHAR:
                    Logger.dumpLog();
                    break;
                default:
                    break;
            }
        }

        LOG_INFO1(F("Key received: "), input);
    }
}
