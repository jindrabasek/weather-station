/*
 * BackLightHandler.cpp
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#include "BackLightHandler.h"

#include <stdbool.h>
#include <Task.h>

#include "../ProgramState.h"

extern ProgramState *state;

void BackLightHandler::onPressed() {
    state->setBackLight(!state->isBackLight());
    state->getBackLightTask().startAtEarliestOportunity();
    state->getBackLightTask().setEnabled(true);
}
