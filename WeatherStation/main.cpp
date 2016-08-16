// Do not remove the include below

#include <avr/interrupt.h>
#include <ApplicationMonitor.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <Logger.h>
#include <PciManager.h>
#include <stdbool.h>
#include <stdint.h>
#include <Scheduler.h>
#include <SoftTimer.h>
#include <time/Clock.h>
#include <Task.h>
#include <Wire.h>
#include <WString.h>

#include "ProgramState.h"
#include "sd/SdCard.h"

Watchdog::CApplicationMonitor ApplicationMonitor;

//The setup function is called once at startup of the sketch
void setup() {
    Serial.begin(115200);

    // Let everything stabilize after powering up
    delay(2000);

    Scheduler::begin(600);
    Wire.begin();

    Clock::getTime(true);
    SdCard::init();

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

// ******* Define PCI interrupt handlers on my own
// to allow multiple handlers to be registered
#ifdef PCINT0_vect
ISR(PCINT0_vect) {
    //SoftwareSerial::handle_interrupt();
    PciManager.callListeners(0);
}
#endif

#ifdef PCINT1_vect
ISR(PCINT1_vect) {
    //SoftwareSerial::handle_interrupt();
    PciManager.callListeners(1);
}
#endif

#ifdef PCINT2_vect
ISR(PCINT2_vect) {
    //SoftwareSerial::handle_interrupt();
    PciManager.callListeners(2);
}
#endif

#ifdef PCINT3_vect
ISR(PCINT3_vect)
{
    //SoftwareSerial::handle_interrupt();
    PciManager.callListeners(3);
}
#endif
