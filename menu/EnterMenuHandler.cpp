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
#include "../display/DrawOnDisplayTask.h"
#include "../ProgramState.h"
#include "MenuScreen.h"
#include "ProgramMenu.h"

extern ProgramState *state;

EnterMenuHandler::EnterMenuHandler(ProgramMenu & menu) :
        menu(menu),
        up(Button::BUTTON_INCREASE, menu.getButtonsCache()),
        down(Button::BUTTON_DECREASE, menu.getButtonsCache()),
        back(Button::BUTTON_BACK, menu.getButtonsCache()),
        enter(Button::BUTTON_SELECT, menu.getButtonsCache()) {
}

void EnterMenuHandler::onPressed() {
    if (!menu.getMenu().isInMenu()) {
        menu.getButtonsBackup().backupHandlers();
        menu.getMenu().setInMenu(true);
    }

    state->getButtons()[WeatherStation::Buttons::UP].setHandler(&up);
    state->getButtons()[WeatherStation::Buttons::DOWN].setHandler(&down);
    //state->getButtons()[WeatherStation::Buttons::LEFT].setHandler(&ButtonHandler::voidButtonHandler);
    //state->getButtons()[WeatherStation::Buttons::RIGHT].setHandler(&ButtonHandler::voidButtonHandler);
    state->getButtons()[WeatherStation::Buttons::ENTER].setHandler(&enter);
    state->getButtons()[WeatherStation::Buttons::ESC].setHandler(&back);

    menu.getButtonsCache().clear();

    menu.getButtonsCache().putPress(Button::BUTTON_NONE);

    state->getDrawOnDisplayTask().setToDraw(&menu.getMenuScreen(), true);
    state->getDrawOnDisplayTask().startAtEarliestOportunity();
    state->getDrawOnDisplayTask().setEnabled(true);
}
