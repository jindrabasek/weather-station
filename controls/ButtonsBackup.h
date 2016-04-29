/*
 * ButtonsCache.h
 *
 *  Created on: 13. 2. 2016
 *      Author: jindra
 */

#ifndef BUTTONSBACKUP_H_
#define BUTTONSBACKUP_H_

#include <ButtonHandler.h>
#include <stddef.h>

#include "Buttons.h"

class ButtonsBackup {
private:
    ButtonHandler * volatile buttonHandlers[WeatherStation::Buttons::buttonsEnumSize] = {
    NULL };
public:
    ButtonsBackup() {
    }
    void backupHandlers();
    void restoreHandlers();
};

#endif /* BUTTONSBACKUP_H_ */
