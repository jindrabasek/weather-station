/*
 * RestartWifiAction.cpp
 *
 *  Created on: 1. 5. 2016
 *      Author: jindra
 */

#include "RestartWifiAction.h"

#include "../ProgramState.h"

extern ProgramState *state;

void RestartWifiAction::doAction() {
    WifiWatchdogTask::forceWifiRestart();
    state->getWifiWatchDogTask().startAtEarliestOportunity();
}
