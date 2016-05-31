/*
 * Logger.cpp
 *
 *  Created on: 10. 4. 2016
 *      Author: jindra
 */

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Logger.h>
#include <Print.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <defines.h>

#ifndef DO_NOT_LOG_SD
#include <FatLib/ArduinoFiles.h>
#include <SdFat.h>
#endif

#ifdef USE_RTC
#include <WireRtcLib.h>
#include <time/Clock.h>
#endif

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

LoggerClass& LoggerClass::getLoggerForLevel(uint8_t level) {
    if (level <= LOG_LEVEL) {
        return Logger;
    }
    return VoidPrint;
}

LoggerClass Logger;
VoidPrintClass VoidPrint;

#ifdef USE_RTC
void LoggerClass::printTime() {
    WireRtcLib::tm& time = Clock::getTime(false);
    print('[');
    if (!time.error) {
        WireRtcLib::formatTime(*this, time);
    } else {
        print('?');
    }
    print(']');
    print(' ');
}
#else
void LoggerClass::printTime() {
    print('[');
    print(millis());
    print(']');
    print(' ');
}
#endif


