/*
 * ButtonsCache.cpp
 *
 *  Created on: 13. 2. 2016
 *      Author: jindra
 */

#include "ButtonsBackup.h"

#include <ButtonHandler.h>
#include <Debouncer.h>
#include <stdint.h>

#include "../ProgramState.h"
#include "Buttons.h"

extern ProgramState *state;

void ButtonsBackup::backupHandlers() {
    for (uint8_t i = 0; i < WeatherStation::Buttons::ButtonsEnumSize; i++) {
        buttonHandlers[i] = state->getButtons()[i].getHandler();
    }
}

void ButtonsBackup::restoreHandlers() {
    for (uint8_t i = 0; i < WeatherStation::Buttons::ButtonsEnumSize; i++) {
        state->getButtons()[i].setHandler(buttonHandlers[i]);
    }
}
