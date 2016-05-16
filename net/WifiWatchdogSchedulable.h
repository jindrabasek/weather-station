/*
 * WifiWatchdogTask.h
 *
 *  Created on: 1. 5. 2016
 *      Author: jindra
 */

#ifndef WIFIWATCHDOGSCHEDULABLE_H_
#define WIFIWATCHDOGSCHEDULABLE_H_

#include <stdbool.h>
#include <Schedulable.h>
#include <Task.h>

class WifiWatchdogSchedulable  : public Schedulable {
private:
    bool forceRestart = false;

public:
    WifiWatchdogSchedulable(){
    }

    WifiWatchdogSchedulable(const WifiWatchdogSchedulable& that) = delete;
    void operator=(const WifiWatchdogSchedulable& that) = delete;

    virtual void run(Task * task);

    void forceWifiRestart() {
        this->forceRestart = true;
    }
};

#endif /* WIFIWATCHDOGSCHEDULABLE_H_ */
