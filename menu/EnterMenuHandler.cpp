/*
 * EnterMenuHandler.cpp
 *
 *  Created on: 8. 2. 2016
 *      Author: jindra
 */

#include "EnterMenuHandler.h"

#include <Debouncer.h>
#include <OMMenuMgr.h>
#include <stdbool.h>
#include <Task.h>

#include "../controls/Buttons.h"
#include "../controls/ButtonsBackup.h"
#include "../display/DrawOnDisplayTask.h"
#include "../ProgramState.h"
#include "MenuButtonsCache.h"
#include "MenuScreen.h"

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

    state.getButtons()[WeatherStation::Buttons::UP].setHandler(&up);
    state.getButtons()[WeatherStation::Buttons::DOWN].setHandler(&down);
    state.getButtons()[WeatherStation::Buttons::LEFT].setHandler(&ButtonHandler::voidButtonHandler);
    state.getButtons()[WeatherStation::Buttons::RIGHT].setHandler(&ButtonHandler::voidButtonHandler);
    state.getButtons()[WeatherStation::Buttons::ENTER].setHandler(&enter);
    state.getButtons()[WeatherStation::Buttons::ESC].setHandler(&back);

    buttonsCache.clear();

    buttonsCache.putPress(Button::BUTTON_NONE);

    state.getDrawOnDisplayTask().setToDraw(&menuScreen, true);
    state.getDrawOnDisplayTask().startAtEarliestOportunity();
    state.getDrawOnDisplayTask().setEnabled(true);
}
