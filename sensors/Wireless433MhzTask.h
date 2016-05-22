/*
 * Wireless433Mhz.h
 *
 *  Created on: 20. 5. 2016
 *      Author: jindra
 */

#ifndef WIRELESS433MHZTASK_H_
#define WIRELESS433MHZTASK_H_

#include <Arduino.h>
#include <stdbool.h>
#include <Task.h>

class Wireless433MhzTask : public Task {
public:
    Wireless433MhzTask() : Task(1000000) {
        pinMode(3,INPUT);
        //pinMode(13,OUTPUT);
        attachInterrupt(digitalPinToInterrupt(3),PinChangeISR0,CHANGE);
    }

    virtual void run();
private:

    static void PinChangeISR0();

    template<typename T>
    static void dec2binLong(Print& out, T myNum, byte NumberOfBits = sizeof(T) * 8) {
        if (NumberOfBits <= sizeof(T) * 8) {
            myNum = myNum << (sizeof(T) * 8 - NumberOfBits);
            for (int i = 0; i < NumberOfBits; i++) {
                if (bitRead(myNum,(sizeof(T) * 8) - 1) == 1)
                    Serial.print("1");
                else
                    Serial.print("0");
                myNum = myNum << 1;
            }
        }
    }

    // Constants
    static const unsigned long sync_MIN = 4300;                      // Minimum Sync time in micro seconds
    static const unsigned long sync_MAX = 4700;

    static const unsigned long bit1_MIN = 2300;
    static const unsigned long bit1_MAX = 2700;

    static const unsigned long bit0_MIN = 1330;
    static const unsigned long bit0_MAX = 1730;

    static const unsigned long glitch_Length = 300;                  // Anything below this value is a glitch and will be ignored.

    // Interrupt variables
    static unsigned long fall_Time;                              // Placeholder for microsecond time when last falling edge occured.
    static unsigned long rise_Time;                              // Placeholder for microsecond time when last rising edge occured.
    static byte bit_Count;                                       // Bit counter for received bits.
    static uint64_t build_Buffer;                                // Placeholder last data packet being received.
    static uint64_t build_prev_Buffer;                           // Placeholder last data packet being received.
    static volatile uint64_t read_Buffer;                        // Placeholder last full data packet read.
    static volatile byte isrFlags;                               // Various flag bits

};

#endif /* WIRELESS433MHZTASK_H_ */
