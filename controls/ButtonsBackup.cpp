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

void ButtonsBackup::backupHandlers() {
    ProgramState & state = ProgramState::instance();

    for (uint8_t i = 0; i < WeatherStation::Buttons::buttonsEnumSize; i++) {
        buttonHandlers[i] = state.getButtons()[i].getHandler();
    }
}

void ButtonsBackup::restoreHandlers() {
    ProgramState & state = ProgramState::instance();

    for (uint8_t i = 0; i < WeatherStation::Buttons::buttonsEnumSize; i++) {
        state.getButtons()[i].setHandler(buttonHandlers[i]);
    }
}
