/*
 * StackTrace.h
 *
 *  Created on: 23. 1. 2017
 *      Author: jindra
 */

#ifndef LIBRARIES_WEATHERSTATIONCOMMON_STACKTRACE_H_
#define LIBRARIES_WEATHERSTATIONCOMMON_STACKTRACE_H_

#include <stdint.h>

#define PUSH_STACK(x) StackTraceI.push(x,__LINE__)
#define POP_STACK StackTraceI.pop()
#define PRINT_STACK StackTraceI.printToLog()

class StackTrace {
public:
    StackTrace();
    void push(uint8_t id, uint16_t line);
    void pop();
    void printToLog();

private:
    static const uint8_t MAX_DEPTH = 50;

    volatile uint8_t depth = 0;
    volatile uint8_t ids[MAX_DEPTH];
    volatile uint16_t lines[MAX_DEPTH];
};

extern StackTrace StackTraceI;

#endif /* LIBRARIES_WEATHERSTATIONCOMMON_STACKTRACE_H_ */
