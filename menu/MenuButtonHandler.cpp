/*
 * MenuButtonHandler.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "MenuButtonHandler.h"

#include <OMMenuMgr.h>
#include <stdbool.h>
#include <Task.h>

#include "../ProgramState.h"
#include "MenuButtonsCache.h"

MenuButtonHandler::MenuButtonHandler(Button button,
                                     MenuButtonsCache& buttonsCache) :
        button(button),
        buttonsCache(buttonsCache) {
}

void MenuButtonHandler::onPressed() {
    buttonsCache.putPress(button);
    ProgramState & state = ProgramState::instance();
    state.getDrawOnDisplayTask().startAtEarliestOportunity();
    state.getDrawOnDisplayTask().setEnabled(true);
}
