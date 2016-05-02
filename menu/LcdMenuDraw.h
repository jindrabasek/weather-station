/*
 * LcdMenuDraw.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef LCDMENUDRAW_H_
#define LCDMENUDRAW_H_

#include <LCD.h>
#include <MenuDrawHandler.h>

class LcdMenuDraw : public MenuDrawHandler {
private:
    LCD & lcd;
public:
    LcdMenuDraw(LCD & lcd);
    virtual void draw(char* p_text, uint8_t p_row, uint8_t p_col, uint8_t len);
};

#endif /* LCDMENUDRAW_H_ */
