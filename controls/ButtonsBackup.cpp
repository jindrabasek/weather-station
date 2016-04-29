/*
 * ButtonsCache.cpp
 *
 *  Created on: 13. 2. 2016
 *      Author: jindra
 */

#include "ButtonsBackup.h"

#include <Debouncer.h>
#include <stddef.h>

#include "../ProgramState.h"

void ButtonsBackup::backupHandlers() {
    ProgramState & state = ProgramState::instance();

    for (unsigned int i = 0; i < WeatherStation::Buttons::buttonsEnumSize; i++) {
        buttonHandlers[i] = state.getButtons()[i].getHandler();
    }
}

void ButtonsBackup::restoreHandlers() {
    ProgramState & state = ProgramState::instance();

    for (unsigned int i = 0; i < WeatherStation::Buttons::buttonsEnumSize; i++) {
        state.getButtons()[i].setHandler(buttonHandlers[i]);
    }
}
