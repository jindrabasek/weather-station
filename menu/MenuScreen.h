/*
 * MenuScreen.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef MENUSCREEN_H_
#define MENUSCREEN_H_

#include "../display/ToDraw.h"
#include "MenuButtonsCache.h"
#include <OMMenuMgr.h>

class MenuScreen: public ToDraw {
private:
	MenuButtonsCache & buttonsCache;
	OMMenuMgr & menu;
public:
	MenuScreen(MenuButtonsCache & buttonsCache, OMMenuMgr & menu);
	virtual void draw(LCD & display);

	OMMenuMgr & getMenu() {
		return menu;
	}
};

#endif /* MENUSCREEN_H_ */
