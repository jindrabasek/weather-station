/*
 * Wireless433Mhz.h
 *
 *  Created on: 20. 5. 2016
 *      Author: jindra
 */

#ifdef ENABLE_W433_SENSORS

#ifndef WIRELESS433MHZTASK_H_
#define WIRELESS433MHZTASK_H_

#include <Arduino.h>
#include <pins_arduino.h>
#include <Print.h>
#include <sensors/LightIntensityReading.h>
#include <sensors/TempReading.h>
#include <stdbool.h>
#include <stdint.h>
#include <Task.h>
#include <SensorIds.h>

#include "WirelessTempSensorReading.h"

class Wireless433MhzTask : public Task {
public:
    Wireless433MhzTask();

    virtual void run();

    WirelessTempSensorReading& getLatestReadingSencor(uint8_t channel) {
        return latestReadingsSencor[channel - 1];
    }

    LightIntensityReading& getLatestReadingIntensityOutdoor() {
        return latestReadingIntensityOutdoor;
    }

    TempReading& getLatestReadingTemperatueOutdoor() {
        return latestReadingTemperatueOutdoor;
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
                    out.print("1");
                else
                    out.print("0");
                myNum = myNum << 1;
            }
        }
    }

    static int16_t parse12bitNumber(uint64_t& dataReceived, uint8_t startBit);
    static uint8_t parse8bitNumber(uint64_t& dataReceived, uint8_t startBit);

    static const uint8_t MAX_CHANNELS_SENCOR = 3;

    // Constants
    static const unsigned long sync_MIN = 4300; // Minimum Sync time in micro seconds
    static const unsigned long sync_MAX = 4700;

    static const unsigned long bit1_MIN = 2300;
    static const unsigned long bit1_MAX = 2700;

    static const unsigned long bit0_MIN = 1300;
    static const unsigned long bit0_MAX = 1700;

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

    WirelessTempSensorReading latestReadingsSencor[MAX_CHANNELS_SENCOR] = {
            {WeatherStation::SensorValueId::WIRELESS_TEMPERTAURE_SWSTS_CH1},
            {WeatherStation::SensorValueId::WIRELESS_TEMPERTAURE_SWSTS_CH2},
            {WeatherStation::SensorValueId::WIRELESS_TEMPERTAURE_SWSTS_CH3} };

    LightIntensityReading latestReadingIntensityOutdoor;
    TempReading latestReadingTemperatueOutdoor;
};

#endif /* WIRELESS433MHZTASK_H_ */

#endif
