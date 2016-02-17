/*
 * LcdExitMenu.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include <ButtonHandler.h>
#include "LcdExitMenu.h"
#include "../ProgramState.h"
#include <PciManager.h>

LcdExitMenu::LcdExitMenu(LCD& lcd, EnterMenuHandler& enterMenuHandler, ButtonsBackup & buttonsBackup) :
	lcd(lcd),
	enterMenuHandler(&enterMenuHandler),
	buttonsBackup(buttonsBackup){
}

void LcdExitMenu::exitMenu(bool fullExit) {
	ProgramState & state = ProgramState::instance();

	PciManager::instance().setEnabled(false);
	if (fullExit) {
		buttonsBackup.restoreHandlers();
		state.getDrawOnDisplayTask().setToDraw(state.getDisplayScreens()[state.getCurrentScreen()], true);
		state.getDrawOnDisplayTask().startAtEarliestOportunity();
		state.getDrawOnDisplayTask().setEnabled(true);
	} else {
		ButtonHandler * voidHandler = &ButtonHandler::voidButtonHandler();
		state.getUpButton().setHandler(voidHandler);
		state.getDownButton().setHandler(voidHandler);
		state.getLeftButton().setHandler(voidHandler);
		state.getRightButton().setHandler(voidHandler);
		state.getEnterButton().setHandler(enterMenuHandler);
		state.getEscButton().setHandler(voidHandler);
		lcd.clear();
		state.getDrawOnDisplayTask().setEnabled(false);
	}
}

void LcdExitMenu::exitMenuPostCallback() {
	PciManager::instance().setEnabled(true);
}
