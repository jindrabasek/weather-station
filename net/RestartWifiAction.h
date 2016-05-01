/*
 * RestartWifiAction.h
 *
 *  Created on: 1. 5. 2016
 *      Author: jindra
 */

#ifndef RESTARTWIFIACTION_H_
#define RESTARTWIFIACTION_H_

#include <MenuAction.h>

class RestartWifiAction : public MenuAction {
public:
    RestartWifiAction() {
    }
    virtual void doAction();
};

#endif /* RESTARTWIFIACTION_H_ */
