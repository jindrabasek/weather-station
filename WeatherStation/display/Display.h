/*
 * Display.h
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

//#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here:
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.

#include <LiquidCrystal_I2C.h>

class Display {
private:
    LiquidCrystal_I2C lcd;

//-----------------------------------------------------------------------------

public:
    void doSetup();
    Display();

    Display(const Display& that) = delete;
    void operator=(const Display& that) = delete;

    LiquidCrystal_I2C& getLcd() {
        return lcd;
    }

    static const uint16_t ROWS = 4;
    static const uint16_t COLUMNS = 20;

    static void newLine(LCD & lcd, uint8_t lineNumber) {
        lcd.setCursor(0, lineNumber);
    }
    static void clearLine(LCD & lcd) {
        for (uint8_t i = 0; i < COLUMNS; i++) {
            lcd.write(' ');
        }
    }

	bool isNotInited() const {
		return notInited;
	}

private:
    bool notInited = true;
};

#endif /* DISPLAY_H_ */
