/*
 * ToDraw.h
 *
 *  Created on: 17. 1. 2016
 *      Author: jindra
 */

#ifndef TODRAW_H_
#define TODRAW_H_

#include <LCD.h>

class ToDraw {
public:
    virtual ~ToDraw() {
    }
    virtual void draw(LCD & display)=0;
};

#endif /* TODRAW_H_ */
