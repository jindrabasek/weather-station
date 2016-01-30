/*
 * ScreenToDraw.cpp
 *
 *  Created on: 20. 1. 2016
 *      Author: jindra
 */

#include "SensorReadingScreen.h"
#include "../ProgramState.h"
#include "../display/LcdNewLiner.h"

SensorReadingScreen::SensorReadingScreen(SensorReading & toDraw) :
		toDraw(toDraw) {

}

void SensorReadingScreen::draw(LCD & display) {
	display.setCursor(0, 0);
	display.print(toDraw.getHeaderText());
	char buffer[9];
	state.getTime(true).timeToStr(buffer);
	display.setCursor(12, 0);
	display.print(buffer);
	LcdNewLiner newLiner(display);
	toDraw.printTo(display, newLiner);
}

