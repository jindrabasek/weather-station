/*
 * WifiWatchdogTask.cpp
 *
 *  Created on: 1. 5. 2016
 *      Author: jindra
 */

#include "WifiWatchdogSchedulable.h"

#include <IPAddress.h>
#include <stdbool.h>
#include <WiFiEsp.h>

#include "../Logger.h"
#include "../ProgramState.h"
#include "Network.h"

void WifiWatchdogSchedulable::run(Task * task) {
    IPAddress ip = WiFi.localIP();
    LOG_INFO(F("Checking WiFi online"));
    // If task is executed manually, restart wifi
    if (forceRestart || ip == IPAddress(0, 0, 0, 0)) {
        forceRestart = false;
        LOG_INFO(F("Restarting WiFi..."));
        bool result = WiFi.hardReset();
        if (result) {
            LOG_INFO(F("Reset done. Connecting..."));
        } else {
            LOG_INFO(F("HW reset not performed, doing SW and connecting..."));
        }
        Network::connect(ProgramState::instance().getSettings(), true);
    }
}
