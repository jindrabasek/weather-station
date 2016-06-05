/*
 * SmartLivingPublishTask.h
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#ifndef WIRELESSSEND433MHZTASK_H_
#define WIRELESSSEND433MHZTASK_H_

#include <Arduino.h>
#include <digitalWriteFast.h>
#include <stdint.h>
#include <Task.h>

class WirelessSend433MhzTask  : public Task {
public:
    WirelessSend433MhzTask(unsigned long periodMs);

    WirelessSend433MhzTask(const WirelessSend433MhzTask& that) = delete;
    void operator=(const WirelessSend433MhzTask& that) = delete;

    virtual void run();

private:
    static const uint8_t SENDER_PORT = 3;

    static const uint8_t REPEAT_SENDS = 6;

    static const unsigned long SYNC_LENGTH = 4;
    static const unsigned long SYNC_UP_LENGTH = 500;
    static const unsigned long BIT1_LENGTH = 2;
    static const unsigned long BIT0_LENGTH = 1;

    static void lineUp(){
        digitalWriteFast(SENDER_PORT, HIGH);
        delayMicroseconds(SYNC_UP_LENGTH);
        digitalWriteFast(SENDER_PORT, LOW);
    }
    static void sync(){
        lineUp();
        delay(SYNC_LENGTH);
    }
    static void bit0(){
        lineUp();
        delay(BIT0_LENGTH);
    }
    static void bit1(){
        lineUp();
        delay(BIT1_LENGTH);
    }

    static void send12bit(int16_t value){
        if (value < 0) {
            bit1();
            value *= -1;
        } else {
            bit0();
        }

        // move to start bit
        value = value << 5;

        for (int i = 0; i < 11; i++) {
            if (value & 0x8000) {
                bit1();
            } else {
                bit0();
            }
            value = value << 1;
        }
    }
};


#endif /* WIRELESSSEND433MHZTASK_H_ */
