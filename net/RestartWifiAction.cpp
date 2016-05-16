/*
 * RestartWifiAction.cpp
 *
 *  Created on: 1. 5. 2016
 *      Author: jindra
 */

#include "RestartWifiAction.h"

#include "../ProgramState.h"

void RestartWifiAction::doAction() {
    ProgramState& state = ProgramState::instance();
    state.getWifiWatchDogSchedulable().forceWifiRestart();
    state.getWifiWatchDogTask().startAtEarliestOportunity();
}
