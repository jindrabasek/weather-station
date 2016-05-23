/*
 * Wireless433Mhz.h
 *
 *  Created on: 20. 5. 2016
 *      Author: jindra
 */

#ifndef WIRELESS433MHZTASK_H_
#define WIRELESS433MHZTASK_H_

#include <Arduino.h>
#include <HardwareSerial.h>
#include <pins_arduino.h>
#include <stdbool.h>
#include <stdint.h>
#include <Task.h>

#include "WirelessTempSensorSwsTsReading.h"

class Wireless433MhzTask : public Task {
public:
    Wireless433MhzTask() :
            Task(0, false) {
        pinMode(3, INPUT);
        attachInterrupt(digitalPinToInterrupt(3), PinChangeISR0, CHANGE);
    }

    virtual void run();

    WirelessTempSensorSwsTsReading& getLatestReading(uint8_t channel) {
        return latestReadings[channel - 1];
    }

private:

    static void PinChangeISR0();

    template<typename T>
    static void dec2binLong(Print& out, T myNum,
                            byte NumberOfBits = sizeof(T) * 8) {
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

    static const uint8_t MAX_CHANNELS_SENCOR = 3;

    // Constants
    static const unsigned long sync_MIN = 4300; // Minimum Sync time in micro seconds
    static const unsigned long sync_MAX = 4700;

    // Constants
    static const unsigned long sync_FALL_MIN = 4020; // Minimum Sync time in micro seconds
    static const unsigned long sync_FALL_MAX = 4110;

    static const unsigned long bit1_MIN = 2300;
    static const unsigned long bit1_MAX = 2700;

    static const unsigned long bit0_MIN = 1330;
    static const unsigned long bit0_MAX = 1730;

    static const unsigned long glitch_Length = 300; // Anything below this value is a glitch and will be ignored.

    // Interrupt variables
    static volatile unsigned long fall_Time; // Placeholder for microsecond time when last falling edge occured.
    static volatile unsigned long rise_Time; // Placeholder for microsecond time when last rising edge occured.
    static volatile byte bit_Count;            // Bit counter for received bits.
    static volatile uint64_t build_Buffer; // Placeholder last data packet being received.
    static volatile uint64_t build_prev_Buffer; // Placeholder last data packet being received.
    static volatile uint64_t read_Buffer; // Placeholder last full data packet read.
    static volatile byte read_Buffer_length;
    static volatile byte isrFlags;                          // Various flag bits

    WirelessTempSensorSwsTsReading latestReadings[MAX_CHANNELS_SENCOR] = { {1}, {2}, {3} };
};

#endif /* WIRELESS433MHZTASK_H_ */
