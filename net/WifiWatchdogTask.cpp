/*
 * WifiWatchdogTask.cpp
 *
 *  Created on: 1. 5. 2016
 *      Author: jindra
 */

#include "WifiWatchdogTask.h"

#include <HardwareSerial.h>
#include <IPAddress.h>
#include <WiFiEsp.h>
#include <WString.h>

#include "../Logger.h"
#include "../ProgramState.h"

WifiWatchdogTask::WifiWatchdogTask(unsigned long periodMs) : Task(periodMs) {
}

void WifiWatchdogTask::run() {
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
        ProgramState & state = ProgramState::instance();
        state.getNetwork().connect(state.getSettings(), true);
    }
}
