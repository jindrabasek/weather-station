/*
 * SerialVirtButtonsTask.h
 *
 *  Created on: 14. 2. 2016
 *      Author: jindra
 */

#ifndef SERIALVIRTBUTTONSSCHEDULABLE_H_
#define SERIALVIRTBUTTONSSCHEDULABLE_H_

#include <Schedulable.h>

class SerialVirtButtonsSchedulable : public Schedulable {
private:
    static const char UP_CHAR = 'w';
    static const char DOWN_CHAR = 's';
    static const char LEFT_CHAR = 'a';
    static const char RIGHT_CHAR = 'd';
    static const char BACKLIGHT_CHAR = 'b';
    static const char ENTER_CHAR = 'e';
    static const char ESC_CHAR = 'q';

public:
    SerialVirtButtonsSchedulable(){

    }
    virtual void run(Task * task);
};

#endif /* SERIALVIRTBUTTONSSCHEDULABLE_H_ */
