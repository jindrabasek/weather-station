/*
 * BackLightTask.cpp
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#include "BackLightTask.h"
#include "ProgramState.h"

BackLightTask::BackLightTask(LCD & display, ProgramState & programState) :
		Task(0, false), display(display), programState(programState) {
}

void BackLightTask::run() {
	if (programState.isBackLight()){
		display.backlight();
	} else {
		display.noBacklight();
	}
	setEnabled(false);
}
