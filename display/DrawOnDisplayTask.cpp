/*
 * TempPrintToDisplayTask.cpp
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#include "DrawOnDisplayTask.h"

#include <Arduino.h>
#include <LCD.h>
#include <stdbool.h>

#include "LcdNewLiner.h"
#include "ToDraw.h"

DrawOnDisplayTask::DrawOnDisplayTask(unsigned long periodMs, LCD & display,
                                     ToDraw * toDraw) :
        Task(periodMs),
        display(display),
        toDraw(toDraw),
        clear(false) {
}

void DrawOnDisplayTask::run() {
    if (clear) {
        clear = false;
        LcdNewLiner lcdClear(display);
        for (byte i = 0; i < 4; i++) {
            lcdClear.newLine(i);
            lcdClear.clearLine();
        }
    }

    toDraw->draw(display);
}
