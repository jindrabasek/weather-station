/*
 * EnterMenuHandler.cpp
 *
 *  Created on: 8. 2. 2016
 *      Author: jindra
 */

#include "EnterMenuHandler.h"
#include <OMMenuMgr.h>
#include "../ProgramState.h"

EnterMenuHandler::EnterMenuHandler(MenuButtonsCache& buttonsCache,
                                   MenuScreen & menuScreen,
                                   ButtonsBackup & buttonsBackup) :
        buttonsCache(buttonsCache),
        menuScreen(menuScreen),
        buttonsBackup(buttonsBackup),
        up(Button::BUTTON_INCREASE, buttonsCache),
        down(Button::BUTTON_DECREASE, buttonsCache),
        back(Button::BUTTON_BACK, buttonsCache),
        enter(Button::BUTTON_SELECT, buttonsCache) {
}

void EnterMenuHandler::onPressed() {
    ProgramState & state = ProgramState::instance();

    if (!menuScreen.getMenu().isInMenu()) {
        buttonsBackup.backupHandlers();
        menuScreen.getMenu().setInMenu(true);
    }

    ButtonHandler * voidHandler = &ButtonHandler::voidButtonHandler();
    state.getUpButton().setHandler(&up);
    state.getDownButton().setHandler(&down);
    state.getLeftButton().setHandler(voidHandler);
    state.getRightButton().setHandler(voidHandler);
    state.getEnterButton().setHandler(&enter);
    state.getEscButton().setHandler(&back);

    buttonsCache.clear();

    buttonsCache.putPress(Button::BUTTON_NONE);

    state.getDrawOnDisplayTask().setToDraw(&menuScreen, true);
    state.getDrawOnDisplayTask().startAtEarliestOportunity();
    state.getDrawOnDisplayTask().setEnabled(true);
}
