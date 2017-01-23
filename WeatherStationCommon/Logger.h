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
#include <WString.h>

#ifndef DO_NOT_LOG_SD
#include <SdFat.h>
#endif

#define S1(x) #x
#define S2(x) S1(x)
#define FILE_LOCATION __FILE__ " : " S2(__LINE__)

// Change _ESPLOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug
// 5: FINEST: errors, warnings, informational, debug and traces

#define LOGGER_LEVEL_DISABLED 0
#define LOGGER_LEVEL_ERROR    1
#define LOGGER_LEVEL_WARN     2
#define LOGGER_LEVEL_INFO     3
#define LOGGER_LEVEL_DEBUG    4
#define LOGGER_LEVEL_FINEST   5

#ifndef LOG_LEVEL
#define LOG_LEVEL LOGGER_LEVEL_INFO
#endif

#ifndef DO_NOT_LOG_SERIAL
#define _LOG_SERIAL_
#endif

#ifndef DO_NOT_LOG_SD
#define _LOG_SD_
#endif

#define LOG_ERROR(x)    if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.log(LOGGER_LEVEL_ERROR,x); }
#define LOG_ERROR0(x)   if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.print(x); }
#define LOG_ERROR1(x,y) if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.log(LOGGER_LEVEL_ERROR,x,y); }
#define LOG_ERROR_TRACE if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.println(F(FILE_LOCATION)); Logger.flush();}
#define LOG_WARN(x)     if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.log(LOGGER_LEVEL_WARN,x); }
#define LOG_WARN0(x)    if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.print(x); }
#define LOG_WARN1(x,y)  if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.log(LOGGER_LEVEL_WARN,x,y); }
#define LOG_WARN2(x,y,z)  if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.log(LOGGER_LEVEL_WARN,x,y,z); }
#define LOG_WARN_TRACE if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.println(F(FILE_LOCATION)); Logger.flush();}
#define LOG_INFO(x)     if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.log(LOGGER_LEVEL_INFO,x); }
#define LOG_INFO0(x)    if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.print(x); }
#define LOG_INFO1(x,y)  if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.log(LOGGER_LEVEL_INFO,x,y); }
#define LOG_INFO2(x,y,z)  if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.log(LOGGER_LEVEL_INFO,x,y,z); }
#define LOG_INFO_TRACE if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.println(F(FILE_LOCATION));}
#define LOG_DEBUG(x)      if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.log(LOGGER_LEVEL_DEBUG,x); }
#define LOG_DEBUG0(x)     if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.print(x); }
#define LOG_DEBUG1(x,y)   if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.log(LOGGER_LEVEL_DEBUG,x,y); }
#define LOG_DEBUG2(x,y,z) if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.log(LOGGER_LEVEL_DEBUG,x,y,z); }
#define LOG_DEBUG_TRACE if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.println(F(FILE_LOCATION)); Logger.flush();}
#define LOG_FINEST(x)      if(LOG_LEVEL>LOGGER_LEVEL_DEBUG) { Logger.log(LOGGER_LEVEL_FINEST,x); }
#define LOG_FINEST0(x)     if(LOG_LEVEL>LOGGER_LEVEL_DEBUG) { Logger.print(x); }
#define LOG_FINEST1(x,y)   if(LOG_LEVEL>LOGGER_LEVEL_DEBUG) { Logger.log(LOGGER_LEVEL_FINEST,x,y); }
#define LOG_FINEST2(x,y,z) if(LOG_LEVEL>LOGGER_LEVEL_DEBUG) { Logger.log(LOGGER_LEVEL_FINEST,x,y,z); }
#define LOG_FINEST_TRACE if(LOG_LEVEL>LOGGER_LEVEL_DEBUG) { Logger.println(F(FILE_LOCATION)); Logger.flush();}

#define LOGGER_ERROR LoggerClass::getLoggerForLevel(LOGGER_LEVEL_ERROR)
#define LOGGER_WARN  LoggerClass::getLoggerForLevel(LOGGER_LEVEL_WARN)
#define LOGGER_INFO  LoggerClass::getLoggerForLevel(LOGGER_LEVEL_INFO)
#define LOGGER_DEBUG LoggerClass::getLoggerForLevel(LOGGER_LEVEL_DEBUG)
#define LOGGER_FINEST LoggerClass::getLoggerForLevel(LOGGER_LEVEL_FINEST)



// Do not define virtual destructor on purpose - class
// and its children is not expected to need destructors,
// it saves a lot of SRAM otherwise occupied by VTABLE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"


class LoggerClass : public Print {
private:
#ifdef _LOG_SD_
    SdFile * sdLoggingFile = NULL;

    static const uint32_t BYTES_TO_DUMP = 1048576;
#endif


public:
    LoggerClass() {
    }

    void printTime();
    void printLevel(uint8_t level);
    void printTimeAndLevel(uint8_t level);

    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);
    virtual void flush();

    static LoggerClass& getLoggerForLevel(uint8_t level);

    template <typename T>
    void log(uint8_t level, T message) {
        printTimeAndLevel(level);
        println(message);
        flush();
    }

    template <typename T, typename U>
    void log(uint8_t level,T message, U message1) {
        printTimeAndLevel(level);
        print(message);
        print(' ');
        println(message1);
        flush();
    }

    template <typename T, typename U, typename V>
    void log(uint8_t level,T message, U message1, V message2) {
        printTimeAndLevel(level);
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
