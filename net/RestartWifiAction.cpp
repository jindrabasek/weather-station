/*
 * RestartWifiAction.cpp
 *
 *  Created on: 1. 5. 2016
 *      Author: jindra
 */

#include "RestartWifiAction.h"

#include "../ProgramState.h"

void RestartWifiAction::doAction() {
    WifiWatchdogTask& task = ProgramState::instance().getWifiWatchDogTask();
    task.forceWifiRestart();
    task.startAtEarliestOportunity();
}
