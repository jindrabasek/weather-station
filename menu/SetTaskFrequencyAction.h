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
    unsigned long multiplier;
public:
    SetTaskFrequencyAction(Task & target, unsigned int (ProgramSettings::*period)() const,
                           unsigned long multiplier);
    virtual void doAction();
};

#endif /* SETTASKFREQUENCYACTION_H_ */
