/*
 * EnterMenuHandler.cpp
 *
 *  Created on: 8. 2. 2016
 *      Author: jindra
 */

#include "EnterMenuHandler.h"
#include <OMMenuMgr.h>
#include "../ProgramState.h"


EnterMenuHandler::EnterMenuHandler(MenuButtonsCache& buttonsCache, MenuScreen & menuScreen, ButtonsBackup & buttonsBackup) :
	buttonsCache(buttonsCache),
	menuScreen(menuScreen),
	buttonsBackup(buttonsBackup),
	up(Button::BUTTON_INCREASE, buttonsCache),
	down(Button::BUTTON_DECREASE, buttonsCache),
	back(Button::BUTTON_BACK, buttonsCache),
	forward(Button::BUTTON_FORWARD, buttonsCache),
	enter(Button::BUTTON_SELECT, buttonsCache){
}

void EnterMenuHandler::onPressed() {
	ProgramState & state = ProgramState::instance();

	if (!menuScreen.getMenu().isInMenu()){
		buttonsBackup.backupHandlers();
		menuScreen.getMenu().setInMenu(true);
	}

	state.getUpButton().setHandler(&up);
	state.getDownButton().setHandler(&down);
	state.getLeftButton().setHandler(&back);
	state.getRightButton().setHandler(&forward);
	state.getEnterButton().setHandler(&enter);

	buttonsCache.clear();

	buttonsCache.putPress(Button::BUTTON_NONE);

	state.getDrawOnDisplayTask().setToDraw(& menuScreen, true);
	state.getDrawOnDisplayTask().startAtEarliestOportunity();
	state.getDrawOnDisplayTask().setEnabled(true);
}
