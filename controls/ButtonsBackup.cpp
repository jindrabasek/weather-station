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

ButtonsBackup::ButtonsBackup() :
        leftButtonPrev(NULL),
        rightButtonPrev(NULL),
        upButtonPrev(NULL),
        downButtonPrev(NULL),
        enterButtonPrev(NULL),
        escButtonPrev(NULL) {

}

void ButtonsBackup::backupHandlers() {
    ProgramState & state = ProgramState::instance();

    upButtonPrev = state.getUpButton().getHandler();
    downButtonPrev = state.getDownButton().getHandler();
    leftButtonPrev = state.getLeftButton().getHandler();
    rightButtonPrev = state.getRightButton().getHandler();
    enterButtonPrev = state.getEnterButton().getHandler();
    escButtonPrev = state.getEscButton().getHandler();
}

void ButtonsBackup::restoreHandlers() {
    ProgramState & state = ProgramState::instance();

    state.getUpButton().setHandler(upButtonPrev);
    state.getDownButton().setHandler(downButtonPrev);
    state.getLeftButton().setHandler(leftButtonPrev);
    state.getRightButton().setHandler(rightButtonPrev);
    state.getEnterButton().setHandler(enterButtonPrev);
    state.getEscButton().setHandler(escButtonPrev);
}
