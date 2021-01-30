/*
 * ProgramMenu.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef PROGRAMMENU_H_
#define PROGRAMMENU_H_

#include <LCD.h>
#include <OMMenuMgr.h>

#include "../controls/ButtonsBackup.h"
#include "../net/RestartWifiAction.h"
#include "EnterMenuHandler.h"
#include "LcdExitMenu.h"
#include "LcdMenuDraw.h"
#include "MenuButtonsCache.h"
#include "MenuScreen.h"
#include "SetLongTaskFrequencyAction.h"
#include "SetTaskFrequencyAction.h"

class ProgramState;

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
#ifdef ENABLE_LIGHT_SENSOR
    SetTaskFrequencyAction setLightMeasureFreqAction;
#endif
    SetTaskFrequencyAction setDisplayRedrawFreqAction;
    SetLongTaskFrequencyAction setTimeSyncFreqAction;
#ifdef ENABLE_SMART_LIVING
    SetTaskFrequencyAction setDataUploadFreqAction;
#endif
    SetTaskFrequencyAction setWifiWatchdogFreqAction;
    RestartWifiAction restartWifiAction;

    OMMenuMgr menu;

    static const unsigned int SEC_IN_MINUTE = 60;
public:
    ProgramMenu(const ProgramMenu& that) = delete;
    void operator=(const ProgramMenu& that) = delete;

    ProgramMenu(LCD & lcd, ProgramState * state);

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

    ButtonsBackup& getButtonsBackup() {
        return buttonsBackup;
    }

    OMMenuMgr& getMenu() {
        return menu;
    }

    MenuScreen& getMenuScreen() {
        return menuScreen;
    }

    LCD& getLcd() {
        return lcd;
    }
};

#endif /* PROGRAMMENU_H_ */
