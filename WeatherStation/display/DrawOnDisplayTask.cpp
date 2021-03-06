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
#include <TaskIds.h>

#include "Display.h"
#include "ToDraw.h"

DrawOnDisplayTask::DrawOnDisplayTask(unsigned long periodMs, Display & display,
                                     ToDraw * toDraw) :
        Task(periodMs, true, DrawOnDisplay_Task),
        display(display),
        toDraw(toDraw),
        clear(false) {
}

void DrawOnDisplayTask::run() {
	if (display.isNotInited()) {
		display.doSetup();
	}

    if (clear) {
        clear = false;
        for (uint8_t i = 0; i < Display::ROWS; i++) {
            Display::newLine(display.getLcd(), i);
            Display::clearLine(display.getLcd());
        }
    }

    toDraw->draw(display.getLcd());
}
