/*
 * Network.cpp
 *
 *  Created on: 19. 4. 2016
 *      Author: jindra
 */

#include "Network.h"

#include <HardwareSerial.h>
#include <utility/EspDrv.h>
#include <WiFiEsp.h>
#include <WString.h>

#include "../ProgramSettings.h"

void Network::connect(ProgramSettings& settings) {
    initNetwork();

    if (networkInitialized() && !networkConnected()) {

        char wifiPasswd[ProgramSettings::WIFI_PASSWD_ARRAY_LENGTH];
        char wifiSsid[ProgramSettings::WIFI_SSID_ARRAY_LENGTH];
        settings.loadWifiPasswd(wifiPasswd);
        settings.loadWifiSsid(wifiSsid);

        // attempt to connect to WiFi network
        Serial.print(F("Attempting to connect to SSID: "));
        Serial.println(wifiSsid);

        // Connect to WPA/WPA2 network
        espStatus = WiFi.begin(wifiSsid, wifiPasswd);

        if (espStatus == WL_CONNECTED) {
            Serial.println(F("Connected to AP"));
        } else {
            Serial.println(F("WiFi connection failed!"));
        }
    }
}

inline void Network::initNetwork() {
    if (!networkInitialized()) {
        WiFi.init(&Serial1, 4800, 115200);

        espStatus = WiFi.status();
        if (espStatus == WL_NO_SHIELD) {
            Serial.println(F("WiFi shield not present"));
        }
    }
}
