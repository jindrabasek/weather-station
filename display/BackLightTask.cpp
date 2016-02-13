/*
 * BackLightTask.cpp
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#include "BackLightTask.h"
#include "../ProgramState.h"

BackLightTask::BackLightTask(LCD & display) :
		Task(0, false), display(display) {
}

void BackLightTask::run() {
	if (ProgramState::instance().isBackLight()){
		display.backlight();
	} else {
		display.noBacklight();
	}
	setEnabled(false);
}
