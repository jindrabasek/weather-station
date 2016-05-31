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

public:
    WifiWatchdogTask(unsigned long periodMs);

    WifiWatchdogTask(const WifiWatchdogTask& that) = delete;
    void operator=(const WifiWatchdogTask& that) = delete;

    virtual void run();

    void forceWifiRestart() {
        this->forceRestart = true;
    }
};

#endif /* WIFIWATCHDOGTASK_H_ */
