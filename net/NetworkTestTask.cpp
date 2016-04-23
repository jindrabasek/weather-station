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
        //client.setUseSsl(true);
        HttpClient http(client);

        Serial.println(F("Getting page...\n"));

        int err = http.get("arduino.cc", 80, "/asciilogo.txt");
        //int err = http.get("da.wiktionary.org", 443, "/wiki/car");
        if (err == 0) {
            err = http.responseStatusCode();
            if (err >= 0) {

                // Usually you'd check that the response code is 200 or a
                // similar "success" code (200-299) before carrying on,
                // but we'll print out whatever response we get

                err = http.skipResponseHeaders();
                if (err >= 0) {
                    // Whilst we haven't timed out & haven't reached the end of the body
                    while (http.available()) {
                        char c = http.read();
                        // Print out this character
                        Serial.print(c);
                    }
                    Serial.println(F("Page loaded!\n"));
                } else {
                    Serial.print(F("Failed to skip response headers: "));
                    Serial.println(err);
                }
            } else {
                Serial.print(F("Getting response failed: "));
                Serial.println(err);
            }
        } else {
            Serial.print(F("Connect failed: "));
            Serial.println(err);
        }
        http.stop();
    } else {
        Serial.println(F("Cannot test network, network not connected."));
    }

    setEnabled(false);
    remove();
}
