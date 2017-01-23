/*
 * WifiWatchdogTask.cpp
 *
 *  Created on: 1. 5. 2016
 *      Author: jindra
 */

#include "WifiWatchdogTask.h"

#include <IPAddress.h>
#include <Logger.h>
#include <stdbool.h>
#include <WiFiEsp.h>
#include <TaskIds.h>

#include "../ProgramState.h"
#include "Network.h"

extern ProgramState *state;

volatile uint8_t WifiWatchdogTask::failedConnections = 0;
volatile uint8_t WifiWatchdogTask::flags = 0;

WifiWatchdogTask::WifiWatchdogTask(unsigned long periodMs) :
        Task(periodMs, true, WifiWatchdog_Task) {
}

void WifiWatchdogTask::run() {
    IPAddress ip = WiFi.localIP();
    LOG_INFO(F("Checking WiFi online"));
    // If task is executed manually, restart wifi
    if (isForceRestart() || ip == IPAddress(0, 0, 0, 0) || failedConnections > RESET_AFTER_N_FAILED) {
        clearForceWifiRestart();
        bool result = true;
        if (isDoHardReset()) {
            LOG_INFO(F("Restarting WiFi by HW..."));
            result = WiFi.hardReset();
        } else {
            LOG_INFO(F("Restarting WiFi by SW..."));
        }
        if (result) {
            LOG_INFO(F("Reset done. Connecting..."));
        } else {
            LOG_INFO(F("HW reset not performed, doing SW and connecting..."));
        }
        Network::connect(state->getSettings(), true);
    }
}

void WifiWatchdogTask::aliveOrNot(bool connectionSucceded) {
    if (connectionSucceded) {
        failedConnections = 0;
    } else {
        failedConnections++;
    }
}
