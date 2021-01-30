/*
 * Network.cpp
 *
 *  Created on: 19. 4. 2016
 *      Author: jindra
 */

#include "Network.h"

#include <defines.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include <Logger.h>
#include <stdbool.h>
#include <stdint.h>
#include <utility/EspDrv.h>
#include <utility/SerialHolder.h>
#include <WiFiEsp.h>
#include <WString.h>

#include "../ProgramSettings.h"
#include "WifiWatchdogTask.h"
#include "../config.h"

uint8_t Network::espStatus = WL_IDLE_STATUS;
SerialHolderT<HardwareSerial> Network::serial(&Serial2);

void Network::connect(bool force) {
    initNetwork(force);

    if (networkInitialized() && (force || !networkConnected())) {
        char wifiPasswd[] = WIFI_PASSWORD;
        char wifiSsid[] = WIFI_SSID;

        // attempt to connect to WiFi network
        LOG_INFO1(F("Attempting to connect to SSID:"), wifiSsid);

        // Connect to WPA/WPA2 network
        espStatus = WiFi.begin(wifiSsid, wifiPasswd);

        if (LOG_LEVEL >= LOGGER_LEVEL_INFO) {
            if (espStatus == WL_CONNECTED) {
                LOGGER_INFO.print(F("Connected to AP, ip: "));
                IPAddress ip = WiFi.localIP();
                ip.printTo(LOGGER_INFO);
                LOGGER_INFO.println();
                Logger.flush();
            } else {
                LOG_INFO(F("WiFi connection failed!"));
            }
        }
    }
}

void Network::listNetworks() {
    if (LOG_LEVEL >= LOGGER_LEVEL_INFO) {

        char networkSsid[WL_NETWORKS_LIST_MAXNUM][WL_SSID_MAX_LENGTH];
        int32_t networkRssi[WL_NETWORKS_LIST_MAXNUM];
        wl_enc_type networkEncr[WL_NETWORKS_LIST_MAXNUM];

        // scan for nearby networks
        int numSsid = WiFi.scanNetworks(networkSsid, networkRssi, networkEncr);
        if (numSsid == -1) {
            LOG_WARN(F("Couldn't scan networks"));
            return;
        }

        // print the list of networks seen
        LOG_INFO1(F("Number of available networks:"), numSsid);

        // print the network number and name for each network found
        for (int thisNet = 0; thisNet < numSsid; thisNet++) {
            LOGGER_INFO.print(thisNet);
            LOGGER_INFO.print(F(") "));
            LOGGER_INFO.print(networkSsid[thisNet]);
            LOGGER_INFO.print(F("\tSignal: "));
            LOGGER_INFO.print(networkRssi[thisNet]);
            LOGGER_INFO.print(F(" dBm"));
            LOGGER_INFO.print(F("\tEncryption: "));
            switch (networkEncr[thisNet]) {
                case ENC_TYPE_WEP:
                    LOGGER_INFO.print(F("WEP"));
                    break;
                case ENC_TYPE_WPA_PSK:
                    LOGGER_INFO.print(F("WPA_PSK"));
                    break;
                case ENC_TYPE_WPA2_PSK:
                    LOGGER_INFO.print(F("WPA2_PSK"));
                    break;
                case ENC_TYPE_WPA_WPA2_PSK:
                    LOGGER_INFO.print(F("WPA_WPA2_PSK"));
                    break;
                case ENC_TYPE_NONE:
                    LOGGER_INFO.print(F("None"));
                    break;
            }
            LOGGER_INFO.println();
        }
        Logger.flush();
    }
}

void Network::status() {
    if (LOG_LEVEL >= LOGGER_LEVEL_INFO) {

        LOG_INFO(F("---Network status---"));
        switch (espStatus) {
            case WL_NO_SHIELD:
                LOG_INFO(F("Error init ESP!"));
                break;
            case WL_IDLE_STATUS:
            case WL_DISCONNECTED:
                LOG_INFO(F("Not Connected"));
                break;
            case WL_CONNECT_FAILED:
                LOG_INFO(F("Error connecting network"));
                break;
            case WL_CONNECTED:
                LOG_INFO(F("WiFi connected!"));

                IPAddress ip = WiFi.localIP();
                LOGGER_INFO.printTimeAndLevel(LOGGER_LEVEL_INFO);
                LOGGER_INFO.print(F("IP address: "));
                ip.printTo(LOGGER_INFO);
                LOGGER_INFO.println();
                Logger.flush();

                break;
        }
    }
}

inline void Network::initNetwork(bool force) {
    if (force || !networkInitialized()) {
        WiFi.init(&serial, 4800, 42, 40, 115200);
        espStatus = WiFi.status();
        if (espStatus == WL_NO_SHIELD) {
            WifiWatchdogTask::doHardReset();
            LOG_ERROR(F("WiFi shield not present!"));
        } else {
            WifiWatchdogTask::doSoftReset();
        }
    }
}
