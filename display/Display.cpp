/*
 * Display.cpp
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#include "Display.h"

#include <Arduino.h>
#include <LCD.h>

void Display::doSetup() {
    lcd.begin(20, 4);

    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);

    lcd.backlight();
}

Display::Display() :
        // set the LCD address to 0x27 for a 20 chars 4 line display
        // Set the pins on the I2C chip used for LCD connections:
        //  addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
        lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE) {
}
