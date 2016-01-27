/*
 * TimeScreen.cpp
 *
 *  Created on: 26. 1. 2016
 *      Author: jindra
 */

#include "TimeScreen.h"

TimeScreen::TimeScreen(TimeReading & actualTime) : actualTime(actualTime) {

}


void TimeScreen::draw(LCD & display) {
	char buffer[11];

	if (actualTime.getReadState() == READ_OK) {
		snprintf_P(buffer, 9, (const char *) F("%02d:%02d:%02d"), actualTime.getTime()->hour,
				actualTime.getTime()->min, actualTime.getTime()->sec);
		display.setCursor(6, 1);
		display.print(buffer);
		snprintf_P(buffer, 11, (const char *) F("%02d.%02d.20%02d"), actualTime.getTime()->mday,
				actualTime.getTime()->mon, actualTime.getTime()->year);
		display.setCursor(5, 2);
		display.print(buffer);
	} else {
		snprintf_P(buffer, 9, (const char *) F("??:??:??"));
		display.setCursor(6, 1);
		display.print(buffer);
		snprintf_P(buffer, 11, (const char *) F("??.??.????"));
		display.setCursor(5, 2);
		display.print(buffer);
	}
}
