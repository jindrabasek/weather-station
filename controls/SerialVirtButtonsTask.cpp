/*
 * SerialVirtButtonsTask.cpp
 *
 *  Created on: 14. 2. 2016
 *      Author: jindra
 */

#include "SerialVirtButtonsTask.h"
#include "../ProgramState.h"
#include <PciManagerLock.h>

SerialVirtButtonsTask::SerialVirtButtonsTask(unsigned long periodMs) :
        Task(periodMs) {
}

void SerialVirtButtonsTask::run() {
    // check if new serial input is available
    if (Serial.available()) {
        // read one char from input buffer
        char input = Serial.read();
        ProgramState & state = ProgramState::instance();

        {
            PciManagerLock lock;
            switch (input) {
                case UP_CHAR:
                    state.getUpButton().getHandler()->onPressed();
                    break;
                case DOWN_CHAR:
                    state.getDownButton().getHandler()->onPressed();
                    break;
                case LEFT_CHAR:
                    state.getLeftButton().getHandler()->onPressed();
                    break;
                case RIGHT_CHAR:
                    state.getRightButton().getHandler()->onPressed();
                    break;
                case BACKLIGHT_CHAR:
                    state.getBackLightButton().getHandler()->onPressed();
                    break;
                case ENTER_CHAR:
                    state.getEnterButton().getHandler()->onPressed();
                    break;
                case ESC_CHAR:
                    state.getEscButton().getHandler()->onPressed();
                    break;
                default:
                    break;
            }
        }

        Serial.print(F("Key received: "));
        Serial.println(input);
    }
}
