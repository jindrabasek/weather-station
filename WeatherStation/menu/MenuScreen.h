/*
 * MenuScreen.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef MENUSCREEN_H_
#define MENUSCREEN_H_

#include <LCD.h>
#include <OMMenuMgr.h>

#include "../display/ToDraw.h"
#include "MenuButtonsCache.h"

class ProgramMenu;

class MenuScreen : public ToDraw {
private:
    ProgramMenu & menu;
public:
    MenuScreen(ProgramMenu & menu);
    virtual void draw(LCD & display);
};

#endif /* MENUSCREEN_H_ */
