/*
 * NetworkTestTask.cpp
 *
 *  Created on: 19. 4. 2016
 *      Author: jindra
 */

#include "NetworkTestTask.h"

#include <HardwareSerial.h>
#include <HttpClient.h>
#include <stdbool.h>
#include <Task.h>
#include <WiFiEspClient.h>

#include "../Logger.h"
#include "Network.h"

NetworkTestTask::NetworkTestTask() :
        Task(0) {
    startAtEarliestOportunity();
}

void NetworkTestTask::run() {
    if (Network::networkConnected()) {
        WiFiEspClient client;
        HttpClient http(client);
        LOG_INFO(F("Getting page...\n"));
        client.beginPacket();
        int err = http.get("arduino.cc", 80, "/asciilogo.txt");
        client.endPacket();
        http.receiveAndPrintResponse(err, Serial, LOGGER_INFO);
        http.stop();
        Logger.flush();
    } else {
        LOG_WARN(F("Cannot test network, network not connected."));
    }

    setEnabled(false);
    remove();
}
