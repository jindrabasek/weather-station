/*
 * NextScreenHandler.cpp
 *
 *  Created on: 16. 1. 2016
 *      Author: jindra
 */

#include "SwitchScreenHandler.h"
#include "ProgramState.h"

SwitchScreenHandler::SwitchScreenHandler(int8_t switchFor, ProgramState & state) :
		switchFor(switchFor), state(state) {
}

void SwitchScreenHandler::onPressed() {

	state.setCurrentScreen(
			(switchFor < 0) ?
					(state.getCurrentScreen() == 0 ?
							(COUNT_OF_SCREENS + switchFor) :
							state.getCurrentScreen() + switchFor) :
					(state.getCurrentScreen() + switchFor) % COUNT_OF_SCREENS);
	state.getDrawOnDisplayTask().setToDraw(
			state.getDisplayScreens()[state.getCurrentScreen()], true);
	state.getDrawOnDisplayTask().startAtEarliestOportunity();
}
