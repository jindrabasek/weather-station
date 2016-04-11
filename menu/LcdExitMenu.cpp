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
        state.getUpButton().setHandler(voidHandler);
        state.getDownButton().setHandler(voidHandler);
        state.getLeftButton().setHandler(voidHandler);
        state.getRightButton().setHandler(voidHandler);
        state.getEnterButton().setHandler(enterMenuHandler);
        state.getEscButton().setHandler(voidHandler);
        lcd.clear();
        state.getDrawOnDisplayTask().setEnabled(false);
    }
}

void LcdExitMenu::exitMenuPostCallback() {
    PciManager::instance().setEnabled(true);
}
