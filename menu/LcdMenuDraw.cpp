/*
 * LcdMenuDraw.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "LcdMenuDraw.h"

LcdMenuDraw::LcdMenuDraw(LCD & lcd) :
		lcd(lcd) {
}

void LcdMenuDraw::draw(char* p_text, int p_row, int p_col, int len) {
	lcd.setCursor(p_col, p_row);

	for (int i = 0; i < len; i++) {
		if (p_text[i] < '!' || p_text[i] > '~')
			lcd.write(' ');
		else
			lcd.write(p_text[i]);
	}
}
