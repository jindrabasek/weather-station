/*
 * SerialVirtButtonsTask.h
 *
 *  Created on: 14. 2. 2016
 *      Author: jindra
 */

#ifndef SERIALVIRTBUTTONSTASK_H_
#define SERIALVIRTBUTTONSTASK_H_

#include <Task.h>

class SerialVirtButtonsTask : public Task {
private:
    static const char UP_CHAR = 'w';
    static const char DOWN_CHAR = 's';
    static const char LEFT_CHAR = 'a';
    static const char RIGHT_CHAR = 'd';
    static const char BACKLIGHT_CHAR = 'b';
    static const char ENTER_CHAR = 'e';
    static const char ESC_CHAR = 'q';
    static const char RESET_CHAR = 'r';
    static const char LOG_DUMP_CHAR = 'l';
    static const char LIST_NETWORKS_CHAR = 'n';
    static const char PRINT_MEMORY_USAGE_CHAR = 'm';
    static const char NETWORK_STATUS_CHAR = 'k';
    static const char DO_INFINITE_LOOP_CHAR = 'x';
    static const char ENABLE_WATCHDOG_CHAR = 'g';
    static const char DISABLE_WATCHDOG_CHAR = 'h';

    static const int DO_RESET_PIN = 5;
    static const int RESET_DELAY = 5000;

    static void doReset();

    static void printMemoryUsage();

public:
    SerialVirtButtonsTask(unsigned long periodMs);
    virtual void run();
};

#endif /* SERIALVIRTBUTTONSTASK_H_ */
