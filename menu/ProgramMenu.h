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


	byte foo = 0;
	byte sel = 0;
	unsigned int bar = 100;
	long baz  = 1;
	float bak = 0.0;


public:
	ProgramMenu(const ProgramMenu& that) = delete;
	void operator=(const ProgramMenu& that) = delete;

	ProgramMenu(LCD & lcd);

	MenuButtonsCache& getButtonsCache() {
		return buttonsCache;
	}

	EnterMenuHandler& getEnterMenuHandler() {
		return enterMenuHandler;
	}

	LcdMenuDraw& getMenuDraw() {
		return menuDraw;
	}

	LcdExitMenu& getMenuExit() {
		return menuExit;
	}
};

#endif /* PROGRAMMENU_H_ */
