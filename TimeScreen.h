/*
 * TimeScreen.h
 *
 *  Created on: 26. 1. 2016
 *      Author: jindra
 */

#ifndef TIMESCREEN_H_
#define TIMESCREEN_H_

#include "ToDraw.h"

class TimeScreen: public ToDraw {
public:
	virtual void draw(LCD & display);
};

#endif /* TIMESCREEN_H_ */
