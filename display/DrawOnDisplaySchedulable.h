/*
 * TempPrintToDisplayTask.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef DRAWONDISPLAYSCHEDULABLE_H_
#define DRAWONDISPLAYSCHEDULABLE_H_

#include <LCD.h>
#include <stdbool.h>
#include <Schedulable.h>

#include "ToDraw.h"

class DrawOnDisplaySchedulable : public Schedulable {
private:
    LCD & display;
    ToDraw * toDraw;
    bool clear;

//-----------------------------------------------------------------------------

public:
    DrawOnDisplaySchedulable(LCD & display, ToDraw * toDraw);

    DrawOnDisplaySchedulable(const DrawOnDisplaySchedulable& that) = delete;
    void operator=(const DrawOnDisplaySchedulable& that) = delete;

    virtual void run(Task * task);

    void setToDraw(ToDraw * toDraw, bool clearFirst = false) {
        this->toDraw = toDraw;
        this->clear = clearFirst;
    }
};

#endif /* DRAWONDISPLAYSCHEDULABLE_H_ */
