/*
 * MenuButtonHandler.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef MENUBUTTONHANDLER_H_
#define MENUBUTTONHANDLER_H_

#include <ButtonHandler.h>
#include <OMMenuMgr.h>
#include "MenuButtonsCache.h"

class MenuButtonHandler: public ButtonHandler {
private:
	Button button;
	MenuButtonsCache & buttonsCache;
public:
	MenuButtonHandler(Button button, MenuButtonsCache & buttonsCache);
	virtual void onPressed();
};

#endif /* MENUBUTTONHANDLER_H_ */
