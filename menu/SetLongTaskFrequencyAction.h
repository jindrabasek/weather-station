/*
 * SetLongTaskFrequencyAction.h
 *
 *  Created on: 22. 4. 2016
 *      Author: jindra
 */

#ifndef SETLONGTASKFREQUENCYACTION_H_
#define SETLONGTASKFREQUENCYACTION_H_

#include <LongTask.h>
#include <MenuAction.h>

class SetLongTaskFrequencyAction : public MenuAction {
private:
    LongTask & target;
    unsigned long & periodHours;
public:
    SetLongTaskFrequencyAction(LongTask & target, unsigned long & periodHours);
    virtual void doAction();
};

#endif /* SETLONGTASKFREQUENCYACTION_H_ */
