/*
 * Wireless433Mhz.cpp
 *
 *  Created on: 20. 5. 2016
 *      Author: jindra
 */

#include "Wireless433MhzTask.h"

#include <Arduino.h>
#include <digitalWriteFast.h>
#include <HardwareSerial.h>
#include <stdint.h>

#include "../Logger.h"

// http://arduino.cc/forum/index.php/topic,142871.msg1106336.html#msg1106336

// __           ___       ___    ___
//   |         |  |      |  |   |  |
//   |_________|  |______|  |___|  |
//
//   |  Sync      |    1    |  0   |
//   |  4500us    | 2500us  | 1500us

// isrFlags bit numbers
#define F_HAVE_DATA 1                                     // 0=Nothing in read buffer, 1=Data in read buffer
#define F_DATA_RECEIVED 2                                     // 0=Unverified data, 1=Verified (2 consecutive matching reads)
#define F_STATE 7                                         // 0=Sync mode, 1=Data mode

unsigned long Wireless433MhzTask::fall_Time = 0; // Placeholder for microsecond time when last falling edge occured.
unsigned long Wireless433MhzTask::rise_Time = 0; // Placeholder for microsecond time when last rising edge occured.
byte Wireless433MhzTask::bit_Count = 0;        // Bit counter for received bits.
uint64_t Wireless433MhzTask::build_Buffer = 0; // Placeholder last data packet being received.
uint64_t Wireless433MhzTask::build_prev_Buffer = 0; // Placeholder last data packet being received.
volatile uint64_t Wireless433MhzTask::read_Buffer = 0; // Placeholder last full data packet read.
volatile byte Wireless433MhzTask::isrFlags = 0;             // Various flag bits

void Wireless433MhzTask::run() {
    uint64_t myData = 0;

    //dec2binLong(isrFlags);
    //Serial.println();

    if (bitRead(isrFlags,F_DATA_RECEIVED)) {
        // We have at least 2 consecutive matching reads
        myData = read_Buffer; // Read the data spread over 2x 32 variables
        bitClear(isrFlags, F_DATA_RECEIVED); // Flag we have read the data

        if (LOG_LEVEL >= LOGGER_LEVEL_INFO) {
            LOGGER_INFO.printTime();
            dec2binLong(LOGGER_INFO, myData);
            LOGGER_INFO.println();
        }

        Serial.print(" Channel=");
        byte H = ((myData >> 24) & 0x3) + 1;        // Get Channel
        Serial.print(H);

        Serial.print(" Temperature=");
        byte ML = (myData >> 12) & 0xF0; // Get MMMM
        H = (myData >> 12) & 0xF;        // Get LLLL
        ML = ML | H;                      // OR MMMM & LLLL nibbles together
        H = (myData >> 20) & 0xF;        // Get HHHH
        byte HH = 0;
        if (((myData >> 23) & 0x1) == 1) //23 bit
            HH = 0xF;
        int temperature = (H << 8) | (HH << 12) | ML;  // Combine HHHH MMMMLLLL
        Serial.print(temperature / 10.0, 1);
        Serial.println(" *C");
    }
}

void Wireless433MhzTask::PinChangeISR0() { // Pin 2 (Interrupt 0) service routine
    //digitalWrite(13, HIGH);
    unsigned long time = micros();                          // Get current time
    if (!digitalReadFast(3)) {
        // Falling edge
        if (time > (rise_Time + glitch_Length)) {
            // Not a glitch
            time = time - fall_Time; // Subtract last falling edge to get pulse time.
            if (bitRead(isrFlags, F_STATE)) {
                // Looking for Data
                if ((time > bit0_MIN) && (time < bit0_MAX)) {
                    // 0 bit
                    build_Buffer = build_Buffer << 1;
                    bit_Count++;
                } else if ((time > bit1_MIN) && (time < bit1_MAX)) {
                    // 1 bit
                    build_Buffer = build_Buffer << 1;
                    bitSet(build_Buffer, 0);
                    bit_Count++;
                } else if ((time > sync_MIN) && (time < sync_MAX)) {
                    if (bit_Count > 0) {
                        // All bits arrived
                        if (!bitRead(isrFlags, F_HAVE_DATA) && build_Buffer == build_prev_Buffer) {
                            read_Buffer = build_Buffer;
                            bitSet(isrFlags, F_DATA_RECEIVED); // Set data reads match
                            bitSet(isrFlags, F_HAVE_DATA); // Set data reads match
                        }
                        build_prev_Buffer = build_Buffer;

                        bitSet(isrFlags, F_STATE);   // Set looking for new data
                        build_Buffer = 0;
                        bit_Count = 0;
                    } else {
                        // Sync length okay
                        bitSet(isrFlags, F_STATE);              // Set data mode
                    }
                } else {
                    // Not a 0 or 1 bit so restart data build and check if it's a sync?
                    bit_Count = 0;
                    build_Buffer = 0;
                    build_prev_Buffer = 0;
                    bitClear(isrFlags, F_STATE);    // Set looking for Sync mode
                    bitClear(isrFlags, F_HAVE_DATA);
                }
            } else {
                // Looking for sync
                if ((time > sync_MIN) && (time < sync_MAX)) {
                    // Sync length okay
                    bit_Count = 0;
                    build_Buffer = 0;
                    build_prev_Buffer = 0;
                    bitSet(isrFlags, F_STATE);                  // Set data mode
                    bitClear(isrFlags, F_HAVE_DATA);
                }
            }
            fall_Time = micros();                             // Store fall time
        }
    } else {
        // Rising edge
        if (time > (fall_Time + glitch_Length)) {
            // Not a glitch
            rise_Time = time;                                 // Store rise time
        }
    }
    //digitalWrite(13, LOW);
}
