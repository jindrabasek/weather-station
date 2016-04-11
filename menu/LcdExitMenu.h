/*
 * LcdExitMenu.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef LCDEXITMENU_H_
#define LCDEXITMENU_H_

#include <LCD.h>
#include <MenuExitHandler.h>
#include <stdbool.h>

#include "../controls/ButtonsBackup.h"
#include "EnterMenuHandler.h"

class LcdExitMenu : public MenuExitHandler {
private:
    LCD & lcd;
    EnterMenuHandler * enterMenuHandler;
    ButtonsBackup & buttonsBackup;
public:
    LcdExitMenu(LCD & lcd, EnterMenuHandler & enterMenuHandler,
                ButtonsBackup & buttonsBackup);
    virtual void exitMenu(bool fullExit);
    virtual void exitMenuPostCallback();
};

#endif /* LCDEXITMENU_H_ */
