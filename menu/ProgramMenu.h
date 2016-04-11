/*
 * ProgramMenu.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef PROGRAMMENU_H_
#define PROGRAMMENU_H_

#include "MenuButtonsCache.h"
#include "EnterMenuHandler.h"
#include "../controls/ButtonsBackup.h"
#include "MenuScreen.h"
#include <LCD.h>
#include "LcdMenuDraw.h"
#include "LcdExitMenu.h"
#include "SetTaskFrequencyAction.h"

class ProgramState;
class ProgramSettings;

class ProgramMenu {
private:
    LCD & lcd;

    ButtonsBackup buttonsBackup;
    MenuButtonsCache buttonsCache;
    MenuScreen menuScreen;
    EnterMenuHandler enterMenuHandler;

    LcdMenuDraw menuDraw;
    LcdExitMenu menuExit;

    SetTaskFrequencyAction setTempMeasureFreqAction;
    SetTaskFrequencyAction setPressureMeasureFreqAction;
    SetTaskFrequencyAction setLightMeasureFreqAction;
    SetTaskFrequencyAction setDisplayRedrawFreqAction;

    OMMenuMgr menu;
public:
    ProgramMenu(const ProgramMenu& that) = delete;
    void operator=(const ProgramMenu& that) = delete;

    ProgramMenu(LCD & lcd, ProgramState * state, ProgramSettings & settings);

    MenuButtonsCache& getButtonsCache() {
        return buttonsCache;
    }

    EnterMenuHandler& getEnterMenuHandler() {
        return enterMenuHandler;
    }

    LcdMenuDraw& getMenuDraw() {
        return menuDraw;
    }

    LcdExitMenu& getMenuExit() {
        return menuExit;
    }
};

#endif /* PROGRAMMENU_H_ */
