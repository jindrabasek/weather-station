// Do not remove the include below

#include <avr/interrupt.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <PciManager.h>
#include <stdbool.h>
#include <Scheduler.h>
#include <SoftTimer.h>
#include <Wire.h>

#include "Logger.h"
#include "ProgramState.h"
#include "sd/SdCard.h"
#include "time/Clock.h"

//The setup function is called once at startup of the sketch
void setup() {
    Serial.begin(115200);

    // Let everything stabilize after powering up
    delay(2000);

    Scheduler.begin(512);
    Wire.begin();

    Clock::getTime(true);
    SdCard::init();
    ProgramState::instance();

    LOG_INFO(F("Init complete"));
}

void loop() {
    while(true) {
        SoftTimer::instance().run();
    }
}

// ******* Define PCI interrupt handlers on my own
// to allow multiple handlers to be registered
#ifdef PCINT0_vect
ISR(PCINT0_vect) {
    //SoftwareSerial::handle_interrupt();
    PciManager::instance().callListeners(0);
}
#endif

#ifdef PCINT1_vect
ISR(PCINT1_vect) {
    //SoftwareSerial::handle_interrupt();
    PciManager::instance().callListeners(1);
}
#endif

#ifdef PCINT2_vect
ISR(PCINT2_vect) {
    //SoftwareSerial::handle_interrupt();
    PciManager::instance().callListeners(2);
}
#endif

#ifdef PCINT3_vect
ISR(PCINT3_vect)
{
    //SoftwareSerial::handle_interrupt();
    PciManager::instance().callListeners(3);
}
#endif
