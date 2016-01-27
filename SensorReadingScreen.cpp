/*
 * ScreenToDraw.cpp
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#include "SensorReadingScreen.h"

SensorReadingScreen::SensorReadingScreen(SensorReading & toDraw, TimeTask & time) :
		toDraw(toDraw), time(time) {

}

void SensorReadingScreen::draw(LCD & display) {
	display.setCursor(0, 0);
	display.print(toDraw.getHeaderText());
	char buffer[9];
	time.getTime(true).timeToStr(buffer);
	display.setCursor(12, 0);
	display.print(buffer);
	toDraw.printToDisplay(display);
}

