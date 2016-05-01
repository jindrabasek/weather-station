/*
 * Network.h
 *
 *  Created on: 19. 4. 2016
 *      Author: jindra
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <HardwareSerial.h>
#include <stdbool.h>
#include <stdint.h>
#include <utility/EspDrv.h>
#include <WiFiEsp.h>
#include <WString.h>

#include "../ProgramSettings.h"

class Network {
private:
    uint8_t espStatus = WL_IDLE_STATUS;

public:
    Network() {
    }

    void connect(ProgramSettings& settings, bool force = false);

    bool networkInitialized() {
        return !(espStatus == WL_IDLE_STATUS || espStatus == WL_NO_SHIELD);
    }

    bool networkConnected() {
        return espStatus == WL_CONNECTED;
    }

private:
    void initNetwork(bool force);

};

#endif /* NETWORK_H_ */
