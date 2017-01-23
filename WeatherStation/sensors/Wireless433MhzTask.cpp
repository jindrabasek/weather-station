/*
 * Wireless433Mhz.cpp
 *
 *  Created on: 20. 5. 2016
 *      Author: jindra
 */

#include "Wireless433MhzTask.h"

#include <Arduino.h>
#include <digitalWriteFast.h>
#include <Logger.h>
#include <sensors/SensorFlags.h>
#include <stdbool.h>
#include <stdint.h>
#include <SensorIds.h>
#include <time/Clock.h>
#include <Task.h>
#include <WString.h>
#include <TaskIds.h>

#include "../ProgramState.h"
#include "WirelessTempSensorReading.h"

// http://arduino.cc/forum/index.php/topic,142871.msg1106336.html#msg1106336

// __           ___       ___    ___
//   |         |  |      |  |   |  |
//   |_________|  |______|  |___|  |
//
//             |  |
//             |  |
//              500 us
//
//   |  Sync      |    1    |  0   |
//   |  4500us    | 2500us  | 1500us

// isrFlags bit numbers
#define F_DATA_NOT_READ 2

volatile unsigned long Wireless433MhzTask::fall_Time = 0; // Placeholder for microsecond time when last falling edge occured.
volatile unsigned long Wireless433MhzTask::rise_Time = 0; // Placeholder for microsecond time when last rising edge occured.
volatile byte Wireless433MhzTask::bit_Count = 0; // Bit counter for received bits.
volatile uint64_t Wireless433MhzTask::build_Buffer = 0; // Placeholder last data packet being received.
volatile uint64_t Wireless433MhzTask::build_prev_Buffer = 0; // Placeholder before last data packet being received.
volatile uint64_t Wireless433MhzTask::read_Buffer = 0; // Placeholder last full data packet read.
volatile byte Wireless433MhzTask::read_Buffer_length = 0; // Placeholder count of received bits
volatile byte Wireless433MhzTask::isrFlags = 0;             // Various flag bits

extern ProgramState *state;

using namespace WeatherStation;

Wireless433MhzTask::Wireless433MhzTask() :
        Task(0, false, Wireless433Mhz_Task),
        latestReadingIntensityOutdoor(SensorValueId::LIGHT_INTENSITY_OUTDOOR),
        latestReadingTemperatueOutdoor(SensorValueId::DHT_HUMIDITY_OUTDOOR) {
    pinMode(3, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(3), PinChangeISR0, CHANGE);
}

int16_t Wireless433MhzTask::parse12bitNumber(uint64_t& dataReceived,
                                             uint8_t startBit) {
    // OR MMMM & LLLL nibbles together
    byte ML = ((dataReceived >> startBit) & 0xF0)  // Get MMMM
    | ((dataReceived >> startBit) & 0xF);  // Get LLLL

    byte H = (dataReceived >> (startBit + 8)) & 0x7;        // Get HHHH
    int8_t sign = 1;
    if (((dataReceived >> (startBit + 11)) & 0x1) == 1) { //12 bit
        sign = -1;
    }
    return ((H << 8) | ML) * sign; // Combine HHHH MMMMLLLL
}

uint8_t Wireless433MhzTask::parse8bitNumber(uint64_t& dataReceived,
                                            uint8_t startBit) {
    return ((dataReceived >> startBit) & 0xF0)  // Get MMMM
    | ((dataReceived >> startBit) & 0xF);  // Get LLLL
}

void Wireless433MhzTask::run() {
    // We have at least 2 consecutive matching reads

    uint64_t dataReceived = read_Buffer;
    byte dataLength = read_Buffer_length;
    bitClear(isrFlags, F_DATA_NOT_READ);

    byte dataType = ((dataReceived >> (dataLength - 4)) & 0x3); // Get data type

    if (LOG_LEVEL >= LOGGER_LEVEL_INFO) {
        LOGGER_INFO.printTime();
        dec2binLong(LOGGER_INFO, dataReceived);
        LOGGER_INFO.print(F(", Length = "));
        LOGGER_INFO.print(dataLength);
        LOGGER_INFO.print(F(" - Data Type = "));
        LOGGER_INFO.print(dataType);
    }

    if (dataType == 2 && dataLength == 40) {
        float humidity = parse12bitNumber(dataReceived, 0) / 10.0;
        float temperature = parse12bitNumber(dataReceived, 12) / 10.0;
        int16_t lightIntensity = parse12bitNumber(dataReceived, 24);

        if (LOG_LEVEL >= LOGGER_LEVEL_INFO) {
            LOGGER_INFO.print(F("; Light intensity = "));
            LOGGER_INFO.print(lightIntensity);
            LOGGER_INFO.print(F(" Lux; Temperature = "));
            LOGGER_INFO.print(temperature, 1);
            LOGGER_INFO.print(F(" *C; Humidity = "));
            LOGGER_INFO.print(humidity, 1);
            LOGGER_INFO.println(F(" %"));
        }

        latestReadingTemperatueOutdoor = TempReading(
                SensorValueId::DHT_HUMIDITY_OUTDOOR, humidity, temperature,
                Clock::getTime(true).timeStamp);

        latestReadingIntensityOutdoor = LightIntensityReading(
                SensorValueId::LIGHT_INTENSITY_OUTDOOR, lightIntensity,
                Clock::getTime(true).timeStamp);

        SensorFlags::writeFlag(SensorValueId::DHT_HUMIDITY_OUTDOOR, false);
        SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE_REAL_FEEL_OUTDOOR,
                false);
        SensorFlags::writeFlag(SensorValueId::DHT_TEMPERTAURE_OUTDOOR, false);
        SensorFlags::writeFlag(SensorValueId::ABSOLUTE_HUMIDITY_OUTDOOR, false);

        SensorFlags::writeFlag(SensorValueId::LIGHT_INTENSITY_OUTDOOR, false);

    } else if (dataType == 3 && dataLength == 36) {
        byte channel = ((dataReceived >> 24) & 0x3) + 1;      // Get Channel

        float temperature = parse12bitNumber(dataReceived, 12) / 10.0; // Combine HHHH MMMMLLLL

        if (LOG_LEVEL >= LOGGER_LEVEL_INFO) {
            LOGGER_INFO.print(F("; Channel = "));
            LOGGER_INFO.print(channel);
            LOGGER_INFO.print(F("; Temperature = "));
            LOGGER_INFO.print(temperature, 1);
            LOGGER_INFO.println(F(" *C"));
        }

        latestReadingsSencor[channel - 1] = WirelessTempSensorReading(
                WeatherStation::SensorValueId::WIRELESS_TEMPERTAURE_SWSTS_CH1
                        + (channel - 1), temperature,
                Clock::getTime(true).timeStamp);

        // indicate sensor reading was refreshed
        SensorFlags::writeFlag(
                (SensorValueId) (SensorValueId::WIRELESS_TEMPERTAURE_SWSTS_CH1
                        + (channel - 1)), false);
    } else {
        if (LOG_LEVEL >= LOGGER_LEVEL_INFO) {
            LOGGER_INFO.println();
        }
    }

    setEnabled(false);
}

void Wireless433MhzTask::PinChangeISR0() { // Pin 2 (Interrupt 0) service routine
    digitalWriteFast(LED_BUILTIN, HIGH);
    unsigned long timeT = micros();                          // Get current time
    if (!digitalReadFast(3)) {
        // Falling edge
        if (timeT >= (rise_Time + glitch_Length)
                || (timeT <= rise_Time
                        && ((4294967294L - rise_Time) + timeT) > glitch_Length)) {
            // Not a glitch
            unsigned long pulseWidth;
            if (timeT < fall_Time) {
                pulseWidth = (4294967294L - fall_Time) + timeT;
            } else {
                pulseWidth = timeT - fall_Time; // Subtract last falling edge to get pulse time.
            }
            // Looking for Data
            if ((pulseWidth >= bit0_MIN) && (pulseWidth <= bit0_MAX)) {
                // 0 bit
                build_Buffer = build_Buffer << 1;
                bit_Count++;
            } else if ((pulseWidth >= bit1_MIN) && (pulseWidth <= bit1_MAX)) {
                // 1 bit
                build_Buffer = build_Buffer << 1;
                bitSet(build_Buffer, 0);
                bit_Count++;
            } else if ((pulseWidth >= sync_MIN) && (pulseWidth <= sync_MAX)) {
                if (bit_Count > 0 && build_Buffer > 0) {
                    // All bits arrived
                    if (!bitRead(isrFlags, F_DATA_NOT_READ)
                            && build_Buffer == build_prev_Buffer) {
                        read_Buffer = build_Buffer;
                        read_Buffer_length = bit_Count;
                        bitSet(isrFlags, F_DATA_NOT_READ); // Set data reads match
                        state->getWireless433MhzTask().setEnabled(true);
                        state->getWireless433MhzTask().startAtEarliestOportunity();
                    }
                    build_prev_Buffer = build_Buffer;
                } else {
                    // Sync length okay
                    build_prev_Buffer = 0;
                }
                bit_Count = 0;
                build_Buffer = 0;
            } else {
                // Not a 0 or 1 bit so restart data build and check if it's a sync?
                bit_Count = 0;
                build_Buffer = 0;
                build_prev_Buffer = 0;
            }
            fall_Time = timeT;                             // Store fall time
            digitalWriteFast(LED_BUILTIN, LOW);
        }
    } else {
        // Rising edge
        if (rise_Time == 0 || timeT >= (fall_Time + glitch_Length)
                || (timeT <= fall_Time
                        && ((4294967294L - fall_Time) + timeT) > glitch_Length)) {
            // Not a glitch
            rise_Time = timeT;                                // Store rise time
            digitalWriteFast(LED_BUILTIN, LOW);
        }
    }

}
