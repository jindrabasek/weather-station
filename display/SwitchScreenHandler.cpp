/*
 * NextScreenHandler.cpp
 *
 *  Created on: 16. 1. 2016
 *      Author: jindra
 */

#include "SwitchScreenHandler.h"

#include <stdbool.h>
#include <stdint.h>

#include "../ProgramState.h"
#include "DrawOnDisplayTask.h"

extern ProgramState *state;

SwitchScreenHandler::SwitchScreenHandler(int8_t switchFor) :
        switchFor(switchFor) {
}

void SwitchScreenHandler::onPressed() {
    state->setCurrentScreen(
            (switchFor < 0) ?
                    (state->getCurrentScreen() == 0 ?
                            (ProgramState::COUNT_OF_SCREENS + switchFor) :
                            state->getCurrentScreen() + switchFor) :
                    (state->getCurrentScreen() + switchFor)
                            % ProgramState::COUNT_OF_SCREENS);
    state->getDrawOnDisplayTask().setToDraw(
            state->getDisplayScreens()[state->getCurrentScreen()], true);
    state->getDrawOnDisplayTask().startAtEarliestOportunity();
}
