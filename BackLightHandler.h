/*
 * BackLightHandler.h
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#ifndef BACKLIGHTHANDLER_H_
#define BACKLIGHTHANDLER_H_

#include <ButtonHandler.h>

class ProgramState;

class BackLightHandler : public ButtonHandler {
private:
	ProgramState & state;

//-----------------------------------------------------------------------------

public:
	BackLightHandler(ProgramState & state);
	void onPressed();
};

#endif /* BACKLIGHTHANDLER_H_ */
