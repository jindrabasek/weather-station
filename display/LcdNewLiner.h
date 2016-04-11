/*
 * LcdNewLiner.h
 *
 *  Created on: 30. 1. 2016
 *      Author: jindra
 */

#ifndef LCDNEWLINER_H_
#define LCDNEWLINER_H_

#include <LCD.h>
#include <WString.h>

#include "../NewLiner.h"

class LcdNewLiner : public NewLiner {
    LCD & lcd;
public:
    LcdNewLiner(LCD & out) :
            lcd(out) {
    }
    virtual void newLine(int lineNumber) {
        lcd.setCursor(0, lineNumber);
    }
    virtual void clearLine() {
        lcd.print(F("                    "));
    }

    virtual ~LcdNewLiner() {
    }
};

#endif /* LCDNEWLINER_H_ */
