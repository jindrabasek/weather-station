/*
 * SdCard.cpp
 *
 *  Created on: 2. 5. 2016
 *      Author: jindra
 */

#include "SdCard.h"

#include <avr/pgmspace.h>
#include <FatLib/FatApiConstants.h>
#include <FatLib/FatFile.h>
#include <Logger.h>
#include <SdFat.h>
#include <SdSpiCard/SdInfo.h>
#include <WString.h>

static const char LOG_FILE_NAME[] PROGMEM = "log.txt";

// Error messages stored in flash.
#define error(msg) SdCard::sd.errorHalt(F(msg))

SdFat SdCard::sd;
SdFile SdCard::logFile;

void SdCard::init() {

    // Initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
    // breadboards.  use SPI_FULL_SPEED for better performance.
    if (!sd.begin(CHIP_SELECT, SPI_FULL_SPEED)) {
        sd.initErrorHalt();
    }

    initSdLogger();
}

void SdCard::initSdLogger() {
    char logFileName[sizeof(LOG_FILE_NAME)];
    strcpy_P(logFileName, LOG_FILE_NAME);

    if (!logFile.open(logFileName, O_CREAT | O_RDWR | O_APPEND )) {
        error("file.open");
    }

    LOG_INFO1(F("Log file size is"), logFile.fileSize());

    Logger.setSdLoggingFile(&logFile);
}

