// Do not remove the include below

#include <avr/interrupt.h>
#include <Arduino.h>
#include <FuncRunnable.h>
#include <HardwareSerial.h>
#include <PciManager.h>
#include <stddef.h>
#include <Scheduler/Semaphore.h>
#include <Scheduler.h>
#include <SoftTimer.h>
#include <Thread.h>
#include <WString.h>

#include "ProgramState.h"

Semaphore mutex;
Thread * mainThread;
Thread * otherThread;

void loop1();
void loop2();
void loop3();
void setup3();

FuncRunnable loop1r(NULL, loop1);
FuncRunnable loop2r(NULL, loop2);
FuncRunnable loop3r(setup3, loop3);

//The setup function is called once at startup of the sketch
void setup() {
    Serial.begin(115200);

    // Let everything stabilize after powering up
    delay(2000);

    Scheduler.begin(512);

    ProgramState::instance();

    Serial.println(F("Init complete"));

    //mainThread = Scheduler.start(&loop1r);
    //otherThread = Scheduler.start(&loop2r);
}

void loop() {
    SoftTimer::instance().run();
}


void loop1() {
    static unsigned int i = 1;
    unsigned long start, stop, ms;

    start = millis();
    mutex.wait();
    {
        stop = millis();
        ms = stop - start;
        Serial.print(stop);
        Serial.print(F(":loop::i="));
        Serial.print(i);
        Serial.print(F(", wait="));
        Serial.println(ms);
        Serial.flush();
        if (i == 31) {
            otherThread->setRunnable(&loop3r);
        }
        if (i == 91) {
            otherThread->setRunnable(&loop2r);
        }

        if (i > 30 && i < 60) {
            otherThread->disable();
        } else if (i > 90 && i < 120) {
            otherThread->disable();
        } else {
            otherThread->enable();
        }
        delay(100);
    }
    mutex.signal();
    delay(random(300));
    i += 1;
}

void loop2() {
    mutex.wait();
    {
        Serial.print(millis());
        Serial.println(F(":loop1::step-1"));
        delay(random(100));

        Serial.print(millis());
        Serial.println(F(":loop1::step-2"));
        delay(random(100));

        Serial.print(millis());
        Serial.println(F(":loop1::step-3"));
        Serial.flush();
        delay(random(100));
    }
    mutex.signal();
}

void setup3() {
    Serial.println(F("Setuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuup"));
}

void loop3() {
    Serial.print(millis());
    Serial.println(F(" Hallllllloooooooooooooooooo"));
    delay(random(100));
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
