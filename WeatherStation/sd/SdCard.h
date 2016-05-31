/*
 * SdCard.h
 *
 *  Created on: 2. 5. 2016
 *      Author: jindra
 */

#ifndef SDCARD_H_
#define SDCARD_H_

#include <pins_arduino.h>
#include <stdint.h>
#include <SdFat.h>

class SdCard {
public:
    SdCard(){

    }

    static void init();

private:
    static const uint8_t CHIP_SELECT = SS;

    static SdFat sd;
    static SdFile logFile;

    static void initSdLogger();
};

#endif /* SDCARD_H_ */
