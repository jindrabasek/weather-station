/*
 * EnterMenuHandler.h
 *
 *  Created on: 8. 2. 2016
 *      Author: jindra
 */

#ifndef ENTERMENUHANDLER_H_
#define ENTERMENUHANDLER_H_

#include <ButtonHandler.h>
#include "MenuButtonHandler.h"
#include "MenuButtonsCache.h"
#include "MenuScreen.h"
#include "../controls/ButtonsBackup.h"

class EnterMenuHandler: public ButtonHandler {
private:
	MenuButtonsCache & buttonsCache;
	MenuScreen & menuScreen;
	ButtonsBackup & buttonsBackup;

	MenuButtonHandler up;
	MenuButtonHandler down;
	MenuButtonHandler back;
	MenuButtonHandler enter;

public:
	EnterMenuHandler(MenuButtonsCache & buttonsCache, MenuScreen & menuScreen, ButtonsBackup & buttonsBackup);
	virtual void onPressed();
};

#endif /* ENTERMENUHANDLER_H_ */
