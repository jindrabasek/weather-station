/*
 * NextScreenHandler.h
 *
 *  Created on: 16. 1. 2016
 *      Author: jindra
 */

#ifndef SWITCHSCREENHANDLER_H_
#define SWITCHSCREENHANDLER_H_

#include <ButtonHandler.h>
#include "DrawOnDisplayTask.h"

class ProgramState;

class SwitchScreenHandler: public ButtonHandler {
private:
	const int8_t switchFor;
	ProgramState & state;

//-----------------------------------------------------------------------------

public:
	SwitchScreenHandler(int8_t switchFor, ProgramState & state);
	void onPressed();
};

#endif /* SWITCHSCREENHANDLER_H_ */
