/*
 * ToDraw.h
 *
 *  Created on: 17. 1. 2016
 *      Author: jindra
 */

#ifndef TODRAW_H_
#define TODRAW_H_

#include <LCD.h>

// Do not define virtual destructor on purpose - class
// and its children is not expected to need destructors,
// it saves a lot of SRAM otherwise occupied by VTABLE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class ToDraw {
public:
    virtual void draw(LCD & display)=0;
};

#pragma GCC diagnostic pop

#endif /* TODRAW_H_ */
