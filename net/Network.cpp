/*
 * Network.cpp
 *
 *  Created on: 19. 4. 2016
 *      Author: jindra
 */

#include "Network.h"

#include <HardwareSerial.h>
#include <IPAddress.h>
#include <utility/EspDrv.h>
#include <WiFiEsp.h>
#include <WString.h>

#include "../Logger.h"
#include "../ProgramSettings.h"

void Network::connect(ProgramSettings& settings, bool force) {
    initNetwork(force);

    if (networkInitialized() && (force || !networkConnected())) {

        char wifiPasswd[ProgramSettings::WIFI_PASSWD_ARRAY_LENGTH];
        char wifiSsid[ProgramSettings::WIFI_SSID_ARRAY_LENGTH];
        settings.loadWifiPasswd(wifiPasswd);
        settings.loadWifiSsid(wifiSsid);

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
            } else {
                LOG_INFO(F("WiFi connection failed!"));
            }
            Logger.flush();
        }
    }
}

inline void Network::initNetwork(bool force) {
    if (force || !networkInitialized()) {
        WiFi.init(&Serial1, 4800, 40, 115200);

        espStatus = WiFi.status();
        if (espStatus == WL_NO_SHIELD) {
            LOG_ERROR(F("WiFi shield not present!"));
        }
    }
}
