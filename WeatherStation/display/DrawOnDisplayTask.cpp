/*
 * TempPrintToDisplayTask.cpp
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#include "DrawOnDisplayTask.h"

#include <LCD.h>
#include <stdbool.h>
#include <stdint.h>

#include "Display.h"
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
        for (uint8_t i = 0; i < Display::ROWS; i++) {
            Display::newLine(display, i);
            Display::clearLine(display);
        }
    }

    toDraw->draw(display);
}
