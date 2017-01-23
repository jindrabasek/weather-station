/*
 * StackTrace.cpp
 *
 *  Created on: 23. 1. 2017
 *      Author: jindra
 */

#include <Logger.h>
#include <stdint.h>
#include <StackTrace.h>
#include <WString.h>

StackTrace::StackTrace() {}

void StackTrace::push(uint8_t id, uint16_t line) {
    if (depth < MAX_DEPTH) {
        ids[depth] = id;
        lines[depth] = line;
        depth++;
    }
}

void StackTrace::pop() {
    if (depth > 0) {
        depth--;
    }
}

void StackTrace::printToLog() {
    Logger.println(F("--- Stack Trace ---"));
    for (int i = 0; i < depth; i++) {
        Logger.print(F("Call: "));
        Logger.print(i);
        Logger.print(F(", ID: "));
        Logger.print(ids[i]);
        Logger.print(F(", Line: "));
        Logger.println(lines[i]);
    }
    Logger.println(F("--- End Stack Trace ---"));
    Logger.flush();
}
