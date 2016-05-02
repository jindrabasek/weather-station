/*
 * Logger.cpp
 *
 *  Created on: 10. 4. 2016
 *      Author: jindra
 */

#include "Logger.h"

#include <HardwareSerial.h>
#include <stddef.h>
#include <stdint.h>

size_t LoggerClass::write(uint8_t unsignedChar) {
    size_t r = 0;

#ifdef _LOG_SERIAL_
    r = Serial.write(unsignedChar);
#endif

#ifdef _LOG_SD_
    if (sdLoggingFile != NULL) {
        r = sdLoggingFile->write(unsignedChar);
    }
#endif

    return r;
}

size_t LoggerClass::write(const uint8_t* buffer, size_t size) {
    size_t r = 0;

#ifdef _LOG_SERIAL_
    r = Serial.write(buffer, size);
#endif

#ifdef _LOG_SD_
    if (sdLoggingFile != NULL) {
        r = sdLoggingFile->write(buffer, size);
    }
#endif
    return r;
}

void LoggerClass::flush() {
#ifdef _LOG_SD_
    if (sdLoggingFile != NULL) {
        sdLoggingFile->sync();
    }
#endif
}

Print& LoggerClass::getLoggerForLevel(int level) {
    if (level <= LOG_LEVEL) {
        return Logger;
    }
    return VoidPrint;
}

LoggerClass Logger;
VoidPrintClass VoidPrint;
