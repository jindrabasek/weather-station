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
#include "MenuButtonsCache.h"
#include "ProgramMenu.h"

MenuScreen::MenuScreen(MenuButtonsCache& buttonsCache, OMMenuMgr& menu) :
        buttonsCache(buttonsCache),
        menu(menu) {
}

void MenuScreen::draw(LCD& display) {
    ProgramState & state = ProgramState::instance();

    Button button;
    {
        PciManagerLock lock;
        button = buttonsCache.getPress();
    }

    menu.handleMenu(button, ProgramState::instance().getMenu().getMenuDraw(),
            ProgramState::instance().getMenu().getMenuExit());

    {
        PciManagerLock lock;
        if (menu.isInMenu()) {
            bool empty = buttonsCache.isEmpty();
            if (empty) {
                state.getDrawOnDisplayTask().setEnabled(false);
            } else {
                state.getDrawOnDisplayTask().startAtEarliestOportunity();
            }
        }
    }
}
