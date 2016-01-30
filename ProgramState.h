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

#include "Display.h"
#include "ProgramState.h"
#include "DrawOnDisplayTask.h"
#include "SwitchScreenHandler.h"
#include "AirPressureMeasureTask.h"
#include "LightIntensityMeasureTask.h"
#include "TempMeasureTask.h"
#include "BackLightTask.h"
#include "BackLightHandler.h"
#include "ProgramSettings.h"
#include "TimeScreen.h"
#include "TimeReading.h"
#include "SensorReadingScreen.h"
#include "Time.h"

#define DEFAULT_SCREEN 0

#define DHT_PIN 7

#define ON_BOARD_LED_PIN 13

#define LEFT_PIN 11
#define RIGHT_PIN 10
#define UP_PIN 12
#define DOWN_PIN 9
#define BACKLIGHT_PIN 5
#define ENTER_PIN 6
#define ESC_PIN 8

#define COUNT_OF_SCREENS 4

#define SOFTWARE_SERIAL_RX_PIN 2
#define SOFTWARE_SERIAL_TX_PIN 3

class ToDraw;

class ProgramState {
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

	SwitchScreenHandler nextScreen;
	SwitchScreenHandler prevScreen;
	BackLightHandler backLightHandler;

	Debouncer leftButton;
	Debouncer rightButton;
	Debouncer backLightButton;

	SoftwareSerial mySerial;

	volatile byte currentScreen;

	volatile bool backLight;

//-----------------------------------------------------------------------------

public:
	ProgramState() :
			measureTempTask(DHT_PIN, 2000),
			measureAirPressureTask(1000),
			measureLightIntensityTask(1000),

			tempScreen(measureTempTask.getLatestReading()),
			airPressureScreen(measureAirPressureTask.getLatestReading()),
			lightIntensityScreen(measureLightIntensityTask.getLatestReading()),

			backLightTask(disp.getLcd()),
			drawOnDisplayTask(500, disp.getLcd(), displayScreens[DEFAULT_SCREEN]),
			nextScreen(1),
			prevScreen(-1),

			leftButton(LEFT_PIN, MODE_CLOSE_ON_PUSH, &prevScreen),
			rightButton(RIGHT_PIN, MODE_CLOSE_ON_PUSH, &nextScreen),
			backLightButton(BACKLIGHT_PIN, MODE_CLOSE_ON_PUSH, &backLightHandler),

			mySerial(SOFTWARE_SERIAL_RX_PIN, SOFTWARE_SERIAL_TX_PIN),

			currentScreen(DEFAULT_SCREEN),
			backLight(true) {
	}

	void init() {
		SoftTimer.add(&measureTempTask);
		SoftTimer.add(&measureAirPressureTask);
		SoftTimer.add(&measureLightIntensityTask);
		SoftTimer.add(&drawOnDisplayTask);
		SoftTimer.add(&backLightTask);
		noInterrupts();
		PciManager.registerListener(&leftButton);
		PciManager.registerListener(&rightButton);
		PciManager.registerListener(&backLightButton);
		interrupts();

		mySerial.begin(9600);

		disp.doSetup();
	}

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
};

extern ProgramState state;

#endif /* PROGRAMSTATE_H_ */
