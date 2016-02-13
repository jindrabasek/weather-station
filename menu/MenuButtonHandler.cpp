/*
 * MenuButtonHandler.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "MenuButtonHandler.h"
#include "../ProgramState.h"

MenuButtonHandler::MenuButtonHandler(Button button,
		MenuButtonsCache& buttonsCache) :
		button(button), buttonsCache(buttonsCache) {
}

void MenuButtonHandler::onPressed() {
	buttonsCache.putPress(button);
	ProgramState & state = ProgramState::instance();
	state.getDrawOnDisplayTask().startAtEarliestOportunity();
	state.getDrawOnDisplayTask().setEnabled(true);
}
