/*
 * ProgramState.cpp
 *
 *  Created on: 30. 1. 2016
 *      Author: jindra
 */

#include "ProgramState.h"

#include <stddef.h>

ProgramState *state = NULL;

void ProgramState::setStateRef() {
    state = this;
}

ProgramState& ProgramState::instance() {
    static ProgramState state;
    return state;
}
