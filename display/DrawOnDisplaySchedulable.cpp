/*
 * TempPrintToDisplayTask.cpp
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#include "DrawOnDisplaySchedulable.h"

#include <LCD.h>
#include <stdbool.h>
#include <stdint.h>

#include "LcdNewLiner.h"
#include "ToDraw.h"

DrawOnDisplaySchedulable::DrawOnDisplaySchedulable(LCD & display,
                                     ToDraw * toDraw) :
        display(display),
        toDraw(toDraw),
        clear(false) {
}

void DrawOnDisplaySchedulable::run(Task * task) {
    if (clear) {
        clear = false;
        LcdNewLiner lcdClear(display);
        for (uint8_t i = 0; i < 4; i++) {
            lcdClear.newLine(i);
            lcdClear.clearLine();
        }
    }

    toDraw->draw(display);
}
