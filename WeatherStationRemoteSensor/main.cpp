// Do not remove the include below

#include <ApplicationMonitor.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <Logger.h>
#include <stdbool.h>
#include <stdint.h>
#include <SoftTimer.h>
#include <Task.h>
#include <Wire.h>

#include "ProgramState.h"

Watchdog::CApplicationMonitor ApplicationMonitor;

//The setup function is called once at startup of the sketch
void setup() {
    Serial.begin(115200);

    // Let everything stabilize after powering up
    delay(2000);

    Wire.begin();

    ApplicationMonitor.Dump(Logger);

    ProgramState::instance();

    ApplicationMonitor.EnableWatchdog(Watchdog::CApplicationMonitor::Timeout_8s);

    LOG_INFO(F("Init complete"));
}

void loggingCallback(Task * runningTask) {
    ApplicationMonitor.SetData(reinterpret_cast<uint32_t>(runningTask));
}

void loop() {
    while(true) {
        ApplicationMonitor.IAmAlive();
        SoftTimer.run(loggingCallback);
    }
}
