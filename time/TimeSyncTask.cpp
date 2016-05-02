/*
 * TimeSyncTask.cpp
 *
 *  Created on: 17. 3. 2016
 *      Author: jindra
 */

#include "TimeSyncTask.h"

#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <WiFiEspUdp.h>
#include <WireRtcLib.h>
#include <WString.h>

#include "../Logger.h"
#include "../net/Network.h"
#include "../ProgramState.h"
#include "Clock.h"

TimeSyncTask::TimeSyncTask(unsigned long periodHours, bool enabled) :
        LongTask(periodHours, 0, enabled) {
    startAtEarliestOportunity();
}

void TimeSyncTask::run() {

    if (ProgramState::instance().getNetwork().networkConnected()) {

        WiFiEspUDP udp;
        static int udpInited = udp.begin(123); // open socket on arbitrary port
        const char timeServer[] = "pool.ntp.org";  // NTP server

        // Only the first four bytes of an outgoing NTP packet need to be set
        // appropriately, the rest can be whatever.
        const long ntpFirstFourBytes = 0xEC0600E3; // NTP request header

        // Fail if WiFiUdp.begin() could not init a socket
        if (!udpInited) {
            LOG_WARN(F("TimeSync: UDP failed"));
            return;
        }

        // Send an NTP request
        if (!(udp.beginPacket(timeServer, 123) // 123 is the NTP port
        && udp.write((byte *) &ntpFirstFourBytes, 48) == 48 && udp.endPacket())) {
            LOG_WARN(F("TimeSync: request failed"));
            return;               // sending request failed
        }

        // Wait for response; check every pollIntv ms up to maxPoll times
        const int pollIntv = 150;     // poll every this many ms
        const byte maxPoll = 15;      // poll up to this many times
        int pktLen;               // received packet length
        for (byte i = 0; i < maxPoll; i++) {
            if ((pktLen = udp.parsePacket()) == 48)
                break;
            delay(pollIntv);
        }
        if (pktLen != 48) {
            LOG_WARN(F("TimeSync: invalid data"));
            return;               // no correct packet received
        }

        // Read and discard the first useless bytes
        // Set useless to 32 for speed; set to 40 for accuracy.
        const byte useless = 40;
        for (byte i = 0; i < useless; ++i)
            udp.read();

        // Read the integer part of sending time
        unsigned long time = udp.read();  // NTP time
        for (byte i = 1; i < 4; i++)
            time = time << 8 | udp.read();

        // Round to the nearest second if we want accuracy
        // The fractionary part is the next byte divided by 256: if it is
        // greater than 500ms we round to the next second; we also account
        // for an assumed network delay of 50ms, and (0.5-0.05)*256=115;
        // additionally, we account for how much we delayed reading the packet
        // since its arrival, which we assume on average to be pollIntv/2.
        time += (udp.read() > 115 - pollIntv / 8);

        // Discard the rest of the packet
        udp.flush();
        udp.stop();

        // convert NTP time to Unix time
        long timeUnix = time - 2208988800ul;
        // adjust time with time zone
        timeUnix += (ProgramState::instance().getSettings().getTimeZone() * 3600);
        WireRtcLib rtc;
        rtc.setTime(WireRtcLib::breakTime(timeUnix));
        LOG_INFO1(F("TimeSync: synced "), timeUnix);
    } else {
        LOG_WARN(F("Cannot sync time, network not connected."));
    }
}
