/*
 * NextScreenHandler.h
 *
 *  Created on: 16. 1. 2016
 *      Author: jindra
 */

#ifndef SWITCHSCREENHANDLER_H_
#define SWITCHSCREENHANDLER_H_

#include <ButtonHandler.h>
#include "DrawOnDisplayTask.h"

class SwitchScreenHandler : public ButtonHandler {
private:
    const int8_t switchFor;

//-----------------------------------------------------------------------------

public:
    SwitchScreenHandler(int8_t switchFor);
    void onPressed();
};

#endif /* SWITCHSCREENHANDLER_H_ */
