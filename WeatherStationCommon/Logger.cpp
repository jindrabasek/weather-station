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
#if defined (__AVR_ATmega2560__)
#include <ApplicationMonitor.h>
#endif
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


void LoggerClass::printTimeAndLevel(uint8_t level) {

    print('[');
    printTime();
    print(' ');
    printLevel(level);
    print(']');
    print(' ');
}

inline void LoggerClass::printLevel(uint8_t level) {
    if (level == LOGGER_LEVEL_ERROR) {
        print(F("ERROR"));
    } else if (level == LOGGER_LEVEL_WARN) {
        print(F("WARN"));
    } else if (level == LOGGER_LEVEL_INFO) {
        print(F("INFO"));
    } else if (level == LOGGER_LEVEL_DEBUG) {
        print(F("DEBUG"));
    } else if (level == LOGGER_LEVEL_FINEST) {
        print(F("FINEST"));
    } else {
        print(level);
    }
}

#ifdef USE_RTC
inline void LoggerClass::printTime() {
    WireRtcLib::tm& time = Clock::getTime(false);
    if (!time.error) {
        WireRtcLib::formatTime(*this, time);
    } else {
        print('?');
    }
}
#else
inline void LoggerClass::printTime() {
    print(millis());
}
#endif

#ifdef _LOG_SD_
void LoggerClass::dumpLog() {
    Serial.println();
    Serial.println(F("-------- Log dump --------"));
    Serial.println();

    if (sdLoggingFile != NULL && sdLoggingFile->isOpen()) {
        uint32_t currentPosition = sdLoggingFile->curPosition();
        uint32_t fileSize = sdLoggingFile->fileSize();
        sdLoggingFile->seekSet(fileSize > BYTES_TO_DUMP ? fileSize - BYTES_TO_DUMP : 0);
        while (sdLoggingFile->available()) {
            byte data = sdLoggingFile->read();
            Serial.write(data);
#if defined (__AVR_ATmega2560__)
            ApplicationMonitor.IAmAlive();
#endif
        }
        sdLoggingFile->seekSet(currentPosition);
    }

    Serial.println();
    Serial.println(F("-------- End dump --------"));
    Serial.println();
}
#endif

