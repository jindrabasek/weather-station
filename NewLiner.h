/*
 * NewLiner.h
 *
 *  Created on: 30. 1. 2016
 *      Author: jindra
 */

#ifndef NEWLINER_H_
#define NEWLINER_H_

class NewLiner {
public:
    virtual void newLine(uint8_t lineNumber)=0;
    virtual void clearLine() {
    }
    virtual ~NewLiner() {
    }
};
#endif /* NEWLINER_H_ */
