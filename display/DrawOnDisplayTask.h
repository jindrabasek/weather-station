/*
 * TempPrintToDisplayTask.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef DRAWONDISPLAYTASK_H_
#define DRAWONDISPLAYTASK_H_

#include <LCD.h>
#include <stdbool.h>
#include <Task.h>

#include "ToDraw.h"

class DrawOnDisplayTask : public Task {
private:
    LCD & display;
    ToDraw * toDraw;
    bool clear;

//-----------------------------------------------------------------------------

public:
    DrawOnDisplayTask(unsigned long periodMs, LCD & display, ToDraw * toDraw);

    DrawOnDisplayTask(const DrawOnDisplayTask& that) = delete;
    void operator=(const DrawOnDisplayTask& that) = delete;

    virtual void run();

    void setToDraw(ToDraw * toDraw, bool clearFirst = false) {
        this->toDraw = toDraw;
        this->clear = clearFirst;
    }
};

#endif /* DRAWONDISPLAYTASK_H_ */
