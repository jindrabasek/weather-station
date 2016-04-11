/*
 * LcdExitMenu.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef LCDEXITMENU_H_
#define LCDEXITMENU_H_

#include <MenuExitHandler.h>
#include "EnterMenuHandler.h"
#include <LCD.h>
#include "../controls/ButtonsBackup.h"

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
