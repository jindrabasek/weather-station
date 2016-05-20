/*
 * MenuScreen.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "MenuScreen.h"

#include <LCD.h>
#include <OMMenuMgr.h>
#include <PciManagerLock.h>
#include <stdbool.h>
#include <Task.h>

#include "../ProgramState.h"
#include "LcdExitMenu.h"
#include "LcdMenuDraw.h"
#include "ProgramMenu.h"

extern ProgramState *state;

MenuScreen::MenuScreen(ProgramMenu & menu) :
        menu(menu) {
}

void MenuScreen::draw(LCD& display) {
    Button button;
    {
        PciManagerLock lock;
        button = menu.getButtonsCache().getPress();
    }

    menu.getMenu().handleMenu(button, state->getMenu().getMenuDraw(),
            state->getMenu().getMenuExit());

    {
        PciManagerLock lock;
        if (menu.getMenu().isInMenu()) {
            bool empty = menu.getButtonsCache().isEmpty();
            if (empty) {
                state->getDrawOnDisplayTask().setEnabled(false);
            } else {
                state->getDrawOnDisplayTask().startAtEarliestOportunity();
            }
        }
    }
}
