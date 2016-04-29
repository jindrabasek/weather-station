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
#include <WString.h>

#include "../ProgramState.h"
#include "Network.h"

NetworkTestTask::NetworkTestTask() :
        Task(0) {
    startAtEarliestOportunity();
}

void NetworkTestTask::run() {
    if (ProgramState::instance().getNetwork().networkConnected()) {
        WiFiEspClient client;
        HttpClient http(client);
        Serial.println(F("Getting page...\n"));
        int err = http.get("arduino.cc", 80, "/asciilogo.txt");
        http.receiveAndPrintResponse(err);
        http.stop();
    } else {
        Serial.println(F("Cannot test network, network not connected."));
    }

    setEnabled(false);
    remove();
}
