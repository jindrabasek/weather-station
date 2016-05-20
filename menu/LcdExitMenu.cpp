/*
 * LcdExitMenu.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "LcdExitMenu.h"

#include <Debouncer.h>
#include <PciManager.h>
#include <stdbool.h>
#include <Task.h>

#include "../controls/Buttons.h"
#include "../display/DrawOnDisplayTask.h"
#include "../ProgramState.h"
#include "EnterMenuHandler.h"
#include "ProgramMenu.h"

extern ProgramState *state;

LcdExitMenu::LcdExitMenu(ProgramMenu & menu) :
        menu(menu) {
}

void LcdExitMenu::exitMenu(bool fullExit) {
    PciManager.setEnabled(false);
    if (fullExit) {
        menu.getButtonsBackup().restoreHandlers();
        state->getDrawOnDisplayTask().setToDraw(
                state->getDisplayScreens()[state->getCurrentScreen()], true);
        state->getDrawOnDisplayTask().startAtEarliestOportunity();
        state->getDrawOnDisplayTask().setEnabled(true);
    } else {
        state->getButtons()[WeatherStation::Buttons::UP].setHandler(&ButtonHandler::voidButtonHandler);
        state->getButtons()[WeatherStation::Buttons::DOWN].setHandler(&ButtonHandler::voidButtonHandler);
        //state->getButtons()[WeatherStation::Buttons::LEFT].setHandler(&ButtonHandler::voidButtonHandler);
        //state->getButtons()[WeatherStation::Buttons::RIGHT].setHandler(&ButtonHandler::voidButtonHandler);
        state->getButtons()[WeatherStation::Buttons::ENTER].setHandler(&menu.getEnterMenuHandler());
        state->getButtons()[WeatherStation::Buttons::ESC].setHandler(&ButtonHandler::voidButtonHandler);
        menu.getLcd().clear();
        state->getDrawOnDisplayTask().setEnabled(false);
    }
}

void LcdExitMenu::exitMenuPostCallback() {
    PciManager.setEnabled(true);
}
