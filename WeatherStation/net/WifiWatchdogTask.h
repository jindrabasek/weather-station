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
    bool forceRestart = false;
    static uint8_t failedConnections;
    static const uint8_t RESET_AFTER_N_FAILED = 2;

public:
    WifiWatchdogTask(unsigned long periodMs);

    WifiWatchdogTask(const WifiWatchdogTask& that) = delete;
    void operator=(const WifiWatchdogTask& that) = delete;

    static void aliveOrNot(bool connectionSucceded);

    virtual void run();

    void forceWifiRestart() {
        this->forceRestart = true;
    }
};

#endif /* WIFIWATCHDOGTASK_H_ */
