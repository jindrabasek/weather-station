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

// Do not define virtual destructor on purpose - class
// and its children is not expected to need destructors,
// it saves a lot of SRAM otherwise occupied by VTABLE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class LcdNewLiner : public NewLiner {
    LCD & lcd;
public:
    LcdNewLiner(LCD & out) :
            lcd(out) {
    }
    virtual void newLine(uint8_t lineNumber) {
        lcd.setCursor(0, lineNumber);
    }
    virtual void clearLine() {
        lcd.print(F("                    "));
    }
};

#pragma GCC diagnostic pop

#endif /* LCDNEWLINER_H_ */
