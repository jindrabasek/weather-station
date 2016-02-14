// Do not remove the include below
#include <Arduino.h>

#include <SoftTimer.h>
#include <PciManager.h>
#include <SoftwareSerial.h>

#include "ProgramState.h"

//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(9600);

	ProgramState::instance();

	Serial.println(F("Init complete"));
}

void loop() {
	SoftTimer::instance().run();
}

// ******* Define PCI interrupt handlers on my own
// to allow multiple handlers to be registered
#ifdef PCINT0_vect
ISR(PCINT0_vect) {
	SoftwareSerial::handle_interrupt();
	PciManager::instance().callListeners(0);
}
#endif

#ifdef PCINT1_vect
ISR(PCINT1_vect) {
	SoftwareSerial::handle_interrupt();
	PciManager::instance().callListeners(1);
}
#endif

#ifdef PCINT2_vect
ISR(PCINT2_vect) {
	SoftwareSerial::handle_interrupt();
	PciManager::instance().callListeners(2);
}
#endif

#ifdef PCINT3_vect
ISR(PCINT3_vect)
{
	SoftwareSerial::handle_interrupt();
	PciManager::instance().callListeners(3);
}
#endif
