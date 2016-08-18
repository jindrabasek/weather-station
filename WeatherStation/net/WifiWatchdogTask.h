/*
 * WifiWatchdogTask.h
 *
 *  Created on: 1. 5. 2016
 *      Author: jindra
 */

#ifndef WIFIWATCHDOGTASK_H_
#define WIFIWATCHDOGTASK_H_

#include <Task.h>

class WifiWatchdogTask  : public Task {
private:
    static const uint8_t DO_HARD_RESET_FLAG = 0;
    static const uint8_t FORCE_RESTART_FLAG = DO_HARD_RESET_FLAG + 1;

    static volatile uint8_t flags;
    static volatile uint8_t failedConnections;
    static const uint8_t RESET_AFTER_N_FAILED = 2;

    static bool isForceRestart(){
        return bitRead(flags, FORCE_RESTART_FLAG);
    }

    static bool isDoHardReset(){
        return bitRead(flags, DO_HARD_RESET_FLAG);
    }

    static void clearForceWifiRestart() {
        bitClear(flags, FORCE_RESTART_FLAG);
    }

public:
    WifiWatchdogTask(unsigned long periodMs);

    WifiWatchdogTask(const WifiWatchdogTask& that) = delete;
    void operator=(const WifiWatchdogTask& that) = delete;

    static void aliveOrNot(bool connectionSucceded);

    virtual void run();

    static void forceWifiRestart() {
        bitSet(flags, FORCE_RESTART_FLAG);
    }

    static void doHardReset() {
        bitSet(flags, DO_HARD_RESET_FLAG);
    }

    static void doSoftReset() {
        bitClear(flags, DO_HARD_RESET_FLAG);
    }
};

#endif /* WIFIWATCHDOGTASK_H_ */
