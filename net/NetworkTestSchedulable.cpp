/*
 * NetworkTestTask.cpp
 *
 *  Created on: 19. 4. 2016
 *      Author: jindra
 */

#include <avr/pgmspace.h>
#include <HardwareSerial.h>
#include <HttpClient.h>
#include <stdbool.h>
#include <Task.h>
#include <WiFiEspClient.h>

#include "../Logger.h"
#include "Network.h"
#include "NetworkTestSchedulable.h"

static const char ARDUINO_URL[] PROGMEM = "arduino.cc";
static const char LOGO_PATH[] PROGMEM = "/asciilogo.txt";

void NetworkTestSchedulable::run(Task * task) {
    if (Network::networkConnected()) {
        WiFiEspClient client;
        HttpClient http(client);
        LOG_INFO(F("Getting page...\n"));
        client.beginPacket();

        char arduinoUrl[sizeof(ARDUINO_URL)];
        strcpy_P(arduinoUrl, ARDUINO_URL);
        char logoPath[sizeof(LOGO_PATH)];
        strcpy_P(logoPath, LOGO_PATH);

        int err = http.get(arduinoUrl, 80, logoPath);
        client.endPacket();
        http.receiveAndPrintResponse(err, Serial, LOGGER_INFO);
        http.stop();
        Logger.flush();
    } else {
        LOG_WARN(F("Cannot test network, network not connected."));
    }

    task->setEnabled(false);
    task->remove();
}
