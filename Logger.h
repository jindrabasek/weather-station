/*
 * Logger.h
 *
 *  Created on: 10. 4. 2016
 *      Author: jindra
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <stddef.h>
#include <stdint.h>
#include <SdFat.h>

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

#ifndef _DO_NOT_LOG_SERIAL_
#define _LOG_SERIAL_
#endif

#ifndef _DO_NOT_LOG_SD_
#define _LOG_SD_
#endif

#define LOG_ERROR(x)    if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.println(x); Logger.flush(); }
#define LOG_ERROR0(x)   if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.print(x); }
#define LOG_ERROR1(x,y) if(LOG_LEVEL>LOGGER_LEVEL_DISABLED) { Logger.print(x); Logger.print(' '); Logger.println(y); Logger.flush(); }
#define LOG_WARN(x)     if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.println(x); Logger.flush(); }
#define LOG_WARN0(x)    if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.print(x); }
#define LOG_WARN1(x,y)  if(LOG_LEVEL>LOGGER_LEVEL_ERROR) { Logger.print(x); Logger.print(' '); Logger.println(y); Logger.flush(); }
#define LOG_INFO(x)     if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.println(x); Logger.flush(); }
#define LOG_INFO0(x)    if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.print(x); }
#define LOG_INFO1(x,y)  if(LOG_LEVEL>LOGGER_LEVEL_WARN) { Logger.print(x); Logger.print(' '); Logger.println(y); Logger.flush(); }

#define LOG_DEBUG(x)      if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.println(x); Logger.flush(); }
#define LOG_DEBUG0(x)     if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.print(x); }
#define LOG_DEBUG1(x,y)   if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.print(x); Logger.print(' '); Logger.println(y); Logger.flush(); }
#define LOG_DEBUG2(x,y,z) if(LOG_LEVEL>LOGGER_LEVEL_INFO) { Logger.print(x); Logger.print(' '); Logger.print(y); Logger.print(' '); Logger.println(z); Logger.flush(); }

#define LOGGER_ERROR LoggerClass::getLoggerForLevel(LOGGER_LEVEL_ERROR)
#define LOGGER_WARN  LoggerClass::getLoggerForLevel(LOGGER_LEVEL_WARN)
#define LOGGER_INFO  LoggerClass::getLoggerForLevel(LOGGER_LEVEL_INFO)
#define LOGGER_DEBUG LoggerClass::getLoggerForLevel(LOGGER_LEVEL_DEBUG)

class LoggerClass : public Print {
private:
    SdFile * sdLoggingFile = NULL;
public:
    LoggerClass() {
    }

    virtual ~LoggerClass() {
    }

    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);
    void flush();

    static Print& getLoggerForLevel(int level);

    void setSdLoggingFile(SdFile* sdLoggingFile) {
        this->sdLoggingFile = sdLoggingFile;
    }
};

class VoidPrintClass : public Print {
public:
    VoidPrintClass() {
    }

    virtual ~VoidPrintClass() {
    }

    virtual size_t write(uint8_t){
        return 1;
    }
    virtual size_t write(const uint8_t *buffer, size_t size){
        return size;
    }
};


extern LoggerClass Logger;
extern VoidPrintClass VoidPrint;

#endif /* LOGGER_H_ */
