/*
 * NewLiner.h
 *
 *  Created on: 30. 1. 2016
 *      Author: jindra
 */

#ifndef NEWLINER_H_
#define NEWLINER_H_

// Do not define virtual destructor on purpose - class
// and its children is not expected to need destructors,
// it saves a lot of SRAM otherwise occupied by VTABLE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class NewLiner {
public:
    virtual void newLine(uint8_t lineNumber)=0;
    virtual void clearLine() {
    }
};

#pragma GCC diagnostic pop

#endif /* NEWLINER_H_ */
