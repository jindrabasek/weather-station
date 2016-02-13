/*
 * PrgState.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef PROGRAMSTATE_H_
#define PROGRAMSTATE_H_

#include <SoftTimer.h>
#include <PciManager.h>
#include <SoftwareSerial.h>
#include <Debouncer.h>

#include "display/Display.h"
#include "ProgramState.h"
#include "display/DrawOnDisplayTask.h"
#include "display/SwitchScreenHandler.h"
#include "sensors/AirPressureMeasureTask.h"
#include "sensors/LightIntensityMeasureTask.h"
#include "sensors/TempMeasureTask.h"
#include "display/BackLightTask.h"
#include "display/BackLightHandler.h"
#include "ProgramSettings.h"
#include "time/TimeScreen.h"
#include "time/TimeReading.h"
#include "sensors/SensorReadingScreen.h"
#include "time/Time.h"
#include "menu/ProgramMenu.h"

class ToDraw;

class ProgramState {
public:
	static const int DEFAULT_SCREEN = 0;

	static const int DHT_PIN = 7;

	static const int ON_BOARD_LED_PIN = 13;

	static const int LEFT_PIN = 11;
	static const int RIGHT_PIN = 10;
	static const int UP_PIN = 12;
	static const int DOWN_PIN = 13; //9;
	static const int BACKLIGHT_PIN = 50; //5;
	static const int ENTER_PIN = 51; //6;
	static const int ESC_PIN = 52; //8;

	static const int COUNT_OF_SCREENS = 4;

	static const int SOFTWARE_SERIAL_RX_PIN = 2;
	static const int SOFTWARE_SERIAL_TX_PIN = 3;

//-----------------------------------------------------------------------------

private:
	ProgramSettings settings;

	Display disp;

	Time time;
	TempMeasureTask measureTempTask;
	AirPressureMeasureTask measureAirPressureTask;
	LightIntensityMeasureTask measureLightIntensityTask;

	TimeScreen timeScreen;
	SensorReadingScreen tempScreen;
	SensorReadingScreen airPressureScreen;
	SensorReadingScreen lightIntensityScreen;

	ToDraw * displayScreens[COUNT_OF_SCREENS] = {
			&timeScreen,
			&tempScreen,
			&airPressureScreen,
			&lightIntensityScreen
	};

	BackLightTask backLightTask;
	DrawOnDisplayTask drawOnDisplayTask;

	ProgramMenu menu;

	SwitchScreenHandler nextScreen;
	SwitchScreenHandler prevScreen;
	BackLightHandler backLightHandler;

	Debouncer leftButton;
	Debouncer rightButton;
	Debouncer backLightButton;
	Debouncer upButton;
	Debouncer downButton;
	Debouncer enterButton;

	SoftwareSerial mySerial;

	volatile byte currentScreen;

	volatile bool backLight;

//-----------------------------------------------------------------------------

public:
	ProgramState(const ProgramState& that) = delete;
	void operator=(const ProgramState& that) = delete;
	static ProgramState& instance();

	volatile byte getCurrentScreen() const {
		return currentScreen;
	}

	void setCurrentScreen(volatile byte currentScreen) {
		this->currentScreen = currentScreen;
	}

	ToDraw ** getDisplayScreens() {
		return displayScreens;
	}

	DrawOnDisplayTask& getDrawOnDisplayTask() {
		return drawOnDisplayTask;
	}

	AirPressureMeasureTask& getMeasureAirPressureTask() {
		return measureAirPressureTask;
	}

	LightIntensityMeasureTask& getMeasureLightIntensityTask() {
		return measureLightIntensityTask;
	}

	TempMeasureTask& getMeasureTempTask() {
		return measureTempTask;
	}

	Display& getDisp() {
		return disp;
	}

	volatile bool isBackLight() const {
		return backLight;
	}

	void setBackLight(volatile bool backLight) {
		this->backLight = backLight;
	}

	BackLightTask& getBackLightTask() {
		return backLightTask;
	}

	TimeReading & getTime(bool updateFirst = false) {
		return time.getTime(updateFirst);
	}

	unsigned long getTimeStamp(bool updateFirst = false) {
		return time.getTime(updateFirst).getTimeStamp();
	}

	ProgramSettings& getSettings() {
		return settings;
	}

	Debouncer& getBackLightButton() {
		return backLightButton;
	}

	Debouncer& getDownButton() {
		return downButton;
	}

	Debouncer& getEnterButton() {
		return enterButton;
	}

	Debouncer& getLeftButton() {
		return leftButton;
	}

	Debouncer& getRightButton() {
		return rightButton;
	}

	Debouncer& getUpButton() {
		return upButton;
	}

private:
	ProgramState() :
			measureTempTask(DHT_PIN, 2000),
			measureAirPressureTask(1000),
			measureLightIntensityTask(1000),

			tempScreen(measureTempTask.getLatestReading()),
			airPressureScreen(measureAirPressureTask.getLatestReading()),
			lightIntensityScreen(measureLightIntensityTask.getLatestReading()),

			backLightTask(disp.getLcd()),
			drawOnDisplayTask(500, disp.getLcd(), displayScreens[DEFAULT_SCREEN]),

			menu(disp.getLcd()),

			nextScreen(1),
			prevScreen(-1),

			leftButton(LEFT_PIN, MODE_CLOSE_ON_PUSH, &prevScreen),
			rightButton(RIGHT_PIN, MODE_CLOSE_ON_PUSH, &nextScreen),
			backLightButton(BACKLIGHT_PIN, MODE_CLOSE_ON_PUSH, &backLightHandler),
			upButton(UP_PIN, MODE_CLOSE_ON_PUSH, &ButtonHandler::voidButtonHandler()),
			downButton(DOWN_PIN, MODE_CLOSE_ON_PUSH, &ButtonHandler::voidButtonHandler()),
			enterButton(ENTER_PIN, MODE_CLOSE_ON_PUSH, &ButtonHandler::voidButtonHandler()),//&menu.getEnterMenuHandler()),

			mySerial(SOFTWARE_SERIAL_RX_PIN, SOFTWARE_SERIAL_TX_PIN),

			currentScreen(DEFAULT_SCREEN),
			backLight(true) {

		SoftTimer & timer = SoftTimer::instance();
		timer.add(&measureTempTask);
		timer.add(&measureAirPressureTask);
		timer.add(&measureLightIntensityTask);
		timer.add(&drawOnDisplayTask);
		timer.add(&backLightTask);

		PciManager & pciManager = PciManager::instance();
		pciManager.registerListener(&leftButton);
		pciManager.registerListener(&rightButton);
		pciManager.registerListener(&backLightButton);
		pciManager.registerListener(&upButton);
		pciManager.registerListener(&downButton);
		pciManager.registerListener(&enterButton);

		mySerial.begin(9600);

		disp.doSetup();

		pciManager.setEnabled(true);
	}
};

#endif /* PROGRAMSTATE_H_ */
