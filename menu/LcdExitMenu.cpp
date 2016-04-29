/*
 * LcdExitMenu.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "LcdExitMenu.h"

#include <Debouncer.h>
#include <LCD.h>
#include <PciManager.h>
#include <stdbool.h>
#include <Task.h>

#include "../controls/Buttons.h"
#include "../controls/ButtonsBackup.h"
#include "../display/DrawOnDisplayTask.h"
#include "../ProgramState.h"
#include "EnterMenuHandler.h"

LcdExitMenu::LcdExitMenu(LCD& lcd, EnterMenuHandler& enterMenuHandler,
                         ButtonsBackup & buttonsBackup) :
        lcd(lcd),
        enterMenuHandler(&enterMenuHandler),
        buttonsBackup(buttonsBackup) {
}

void LcdExitMenu::exitMenu(bool fullExit) {
    ProgramState & state = ProgramState::instance();

    PciManager::instance().setEnabled(false);
    if (fullExit) {
        buttonsBackup.restoreHandlers();
        state.getDrawOnDisplayTask().setToDraw(
                state.getDisplayScreens()[state.getCurrentScreen()], true);
        state.getDrawOnDisplayTask().startAtEarliestOportunity();
        state.getDrawOnDisplayTask().setEnabled(true);
    } else {
        ButtonHandler * voidHandler = &ButtonHandler::voidButtonHandler();
        state.getButtons()[WeatherStation::Buttons::UP].setHandler(voidHandler);
        state.getButtons()[WeatherStation::Buttons::DOWN].setHandler(voidHandler);
        state.getButtons()[WeatherStation::Buttons::LEFT].setHandler(voidHandler);
        state.getButtons()[WeatherStation::Buttons::RIGHT].setHandler(voidHandler);
        state.getButtons()[WeatherStation::Buttons::ENTER].setHandler(enterMenuHandler);
        state.getButtons()[WeatherStation::Buttons::ESC].setHandler(voidHandler);
        lcd.clear();
        state.getDrawOnDisplayTask().setEnabled(false);
    }
}

void LcdExitMenu::exitMenuPostCallback() {
    PciManager::instance().setEnabled(true);
}
