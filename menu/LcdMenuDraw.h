/*
 * LcdMenuDraw.h
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#ifndef LCDMENUDRAW_H_
#define LCDMENUDRAW_H_

#include <MenuDrawHandler.h>
#include <LCD.h>

class LcdMenuDraw : public MenuDrawHandler {
private:
    LCD & lcd;
public:
    LcdMenuDraw(LCD & lcd);
    virtual void draw(char* p_text, int p_row, int p_col, int len);
};

#endif /* LCDMENUDRAW_H_ */
