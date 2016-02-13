/*
 * MenuScreen.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "MenuScreen.h"
#include <PciManagerLock.h>
#include "../ProgramState.h"

MenuScreen::MenuScreen(MenuButtonsCache& buttonsCache, OMMenuMgr& menu) :
		buttonsCache(buttonsCache), menu(menu) {
}

void MenuScreen::draw(LCD& display) {
	ProgramState & state = ProgramState::instance();

	Button button;
	{
		PciManagerLock lock;
		button = buttonsCache.getPress();
	}

	menu.handleMenu(button);

	{
		PciManagerLock lock;
		bool empty = buttonsCache.isEmpty();
		if (empty) {
			state.getDrawOnDisplayTask().setEnabled(false);
		} else {
			state.getDrawOnDisplayTask().startAtEarliestOportunity();
		}
	}
}
