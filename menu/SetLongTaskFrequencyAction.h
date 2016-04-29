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

#include "../ProgramSettings.h"

class SetLongTaskFrequencyAction : public MenuAction {
private:
    LongTask & target;
    unsigned int (ProgramSettings::*periodHours)() const;
public:
    SetLongTaskFrequencyAction(LongTask & target, unsigned int (ProgramSettings::*periodHours)() const);
    virtual void doAction();
};

#endif /* SETLONGTASKFREQUENCYACTION_H_ */
