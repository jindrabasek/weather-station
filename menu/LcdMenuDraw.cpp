/*
 * LcdMenuDraw.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "LcdMenuDraw.h"

#include <LCD.h>
#include <stdint.h>

LcdMenuDraw::LcdMenuDraw(LCD & lcd) :
        lcd(lcd) {
}

void LcdMenuDraw::draw(char* p_text, uint8_t p_row, uint8_t p_col, uint8_t len) {
    lcd.setCursor(p_col, p_row);

    for (uint8_t i = 0; i < len; i++) {
        if (p_text[i] < '!' || p_text[i] > '~')
            lcd.write(' ');
        else
            lcd.write(p_text[i]);
    }
}
