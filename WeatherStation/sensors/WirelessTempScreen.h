/*
 * WirelessTempScreen.h
 *
 *  Created on: 18. 6. 2016
 *      Author: jindra
 */

#ifndef WIRELESSTEMPSCREEN_H_
#define WIRELESSTEMPSCREEN_H_

#include <avr/pgmspace.h>
#include <LCD.h>
#include <stdint.h>

#include "../display/ToDraw.h"

class WirelessTempScreen : public ToDraw {
private:
    uint8_t firstGlobalSensorId;
    PGM_P screenLabel;
    static const uint8_t MAX_CHANNELS = 3;

public:
    WirelessTempScreen(uint8_t firstGlobalSensorId, PGM_P screenLabel);
    virtual void draw(LCD & display);
};

#endif /* WIRELESSTEMPSCREEN_H_ */
