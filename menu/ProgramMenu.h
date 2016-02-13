/*
 * ProgramMenu.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef PROGRAMMENU_H_
#define PROGRAMMENU_H_

#include "MenuButtonsCache.h"
#include "EnterMenuHandler.h"
#include "../controls/ButtonsBackup.h"
#include "MenuScreen.h"
#include <LCD.h>
#include "LcdMenuDraw.h"
#include "LcdExitMenu.h"

class ProgramMenu {
private:
	LCD & lcd;

	ButtonsBackup buttonsBackup;
	MenuButtonsCache buttonsCache;
	MenuScreen menuScreen;
	EnterMenuHandler enterMenuHandler;

	LcdMenuDraw menuDraw;
	LcdExitMenu menuExit;

	OMMenuMgr menu;

public:
	ProgramMenu(const ProgramMenu& that) = delete;
	void operator=(const ProgramMenu& that) = delete;

	ProgramMenu(LCD & lcd) :
		lcd (lcd),
		menuScreen(buttonsCache, menu),
		enterMenuHandler(buttonsCache, menuScreen, buttonsBackup),
		menuDraw(lcd),
		menuExit(lcd, enterMenuHandler, buttonsBackup),
		menu(NULL, menuDraw, menuExit){
	}

	MenuButtonsCache& getButtonsCache() {
		return buttonsCache;
	}

	EnterMenuHandler& getEnterMenuHandler() {
		return enterMenuHandler;
	}
};

#endif /* PROGRAMMENU_H_ */
