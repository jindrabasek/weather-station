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
#include <utility/SerialHolder.h>

class Network {
private:
    static uint8_t espStatus;
    static SerialHolderT<HardwareSerial> serial;

public:
    static void connect(bool force = false);

    static bool networkInitialized() {
        return !(espStatus == WL_IDLE_STATUS || espStatus == WL_NO_SHIELD);
    }

    static bool networkConnected() {
        return espStatus == WL_CONNECTED;
    }

    static void listNetworks();
    static void status();

private:
    static void initNetwork(bool force);

};

#endif /* NETWORK_H_ */
