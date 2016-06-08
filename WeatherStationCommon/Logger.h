/*
 * Logger.h
 *
 *  Created on: 10. 4. 2016
 *      Author: jindra
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <Print.h>
#include <stddef.h>
#include <stdint.h>
#include <defines.h>

#ifndef DO_NOT_LOG_SD
#include <SdFat.h>
#endif

// Change _ESPLOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#define LOGGER_LEVEL_DISABLED 0
#define LOGGER_LEVEL_ERROR    1
#define LOGGER_LEVEL_WARN     2
#define LOGGER_LEVEL_INFO     3
#define LOGGER_LEVEL_DEBUG    4

#ifndef LOG_LEVEL
#define LOG_LEVEL LOGGER_LEVEL_INFO
#endif

#ifndef DO_NOT_LOG_SERIAL
#define _LOG_SERIAL_
#endif

#ifndef DO_NOT_LOG_SD
#define _LOG_SD_
#endif

#define LOG_ERROR(x)    if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.log(x); }
#define LOG_ERROR0(x)   if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.print(x); }
#define LOG_ERROR1(x,y) if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.log(x,y); }
#define LOG_WARN(x)     if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.log(x); }
#define LOG_WARN0(x)    if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.print(x); }
#define LOG_WARN1(x,y)  if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.log(x,y); }
#define LOG_WARN2(x,y,z)  if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.log(x,y,z); }
#define LOG_INFO(x)     if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.log(x); }
#define LOG_INFO0(x)    if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.print(x); }
#define LOG_INFO1(x,y)  if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.log(x,y); }
#define LOG_INFO2(x,y,z)  if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.log(x,y,z); }

#define LOG_DEBUG(x)      if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.log(x); }
#define LOG_DEBUG0(x)     if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.print(x); }
#define LOG_DEBUG1(x,y)   if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.log(x,y); }
#define LOG_DEBUG2(x,y,z) if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.log(x,y,z); }

#define LOGGER_ERROR LoggerClass::getLoggerForLevel(LOGGER_LEVEL_ERROR)
#define LOGGER_WARN  LoggerClass::getLoggerForLevel(LOGGER_LEVEL_WARN)
#define LOGGER_INFO  LoggerClass::getLoggerForLevel(LOGGER_LEVEL_INFO)
#define LOGGER_DEBUG LoggerClass::getLoggerForLevel(LOGGER_LEVEL_DEBUG)



// Do not define virtual destructor on purpose - class
// and its children is not expected to need destructors,
// it saves a lot of SRAM otherwise occupied by VTABLE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"


class LoggerClass : public Print {
private:
#ifdef _LOG_SD_
    SdFile * sdLoggingFile = NULL;

    static const uint32_t BYTES_TO_DUMP = 262144;
#endif


public:
    LoggerClass() {
    }

    void printTime();

    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);
    virtual void flush();

    static LoggerClass& getLoggerForLevel(uint8_t level);

    template <typename T>
    void log(T message) {
        printTime();
        println(message);
        flush();
    }

    template <typename T, typename U>
    void log(T message, U message1) {
        printTime();
        print(message);
        print(' ');
        println(message1);
        flush();
    }

    template <typename T, typename U, typename V>
    void log(T message, U message1, V message2) {
        printTime();
        print(message);
        print(' ');
        print(message1);
        print(' ');
        println(message2);
        flush();
    }

#ifdef _LOG_SD_
    void setSdLoggingFile(SdFile* sdLoggingFile) {
        this->sdLoggingFile = sdLoggingFile;
    }

    void dumpLog();
#endif
};

class VoidPrintClass : public LoggerClass {
public:
    VoidPrintClass() {
    }

    virtual size_t write(uint8_t){
        return 1;
    }
    virtual size_t write(const uint8_t *buffer, size_t size){
        return size;
    }

    virtual void flush() {

    }
};


extern LoggerClass Logger;
extern VoidPrintClass VoidPrint;

#pragma GCC diagnostic pop

#endif /* LOGGER_H_ */
