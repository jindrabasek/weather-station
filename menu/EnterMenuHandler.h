/*
 * EnterMenuHandler.h
 *
 *  Created on: 8. 2. 2016
 *      Author: jindra
 */

#ifndef ENTERMENUHANDLER_H_
#define ENTERMENUHANDLER_H_

#include "../controls/ButtonsBackup.h"
#include "MenuButtonHandler.h"
#include "MenuButtonsCache.h"
#include "MenuScreen.h"

class ProgramMenu;

class EnterMenuHandler : public ButtonHandler {
private:
    ProgramMenu & menu;

    MenuButtonHandler up;
    MenuButtonHandler down;
    MenuButtonHandler back;
    MenuButtonHandler enter;

public:
    EnterMenuHandler(ProgramMenu & menu);
    virtual void onPressed();
};

#endif /* ENTERMENUHANDLER_H_ */
