/*
 * SetTaskFrequencyAction.h
 *
 *  Created on: 21. 2. 2016
 *      Author: jindra
 */

#ifndef SETTASKFREQUENCYACTION_H_
#define SETTASKFREQUENCYACTION_H_

#include <MenuAction.h>
#include <Task.h>

#include "../ProgramSettings.h"

class SetTaskFrequencyAction : public MenuAction {
private:
    Task & target;
    unsigned int (ProgramSettings::*period)() const;
    uint8_t multiplierSec;
public:
    SetTaskFrequencyAction(Task & target, unsigned int (ProgramSettings::*period)() const,
                           uint8_t multiplierSec);
    virtual void doAction();
};

#endif /* SETTASKFREQUENCYACTION_H_ */
