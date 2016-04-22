/*
 * PrgState.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef PROGRAMSTATE_H_
#define PROGRAMSTATE_H_

#include "ProgramState.h"

#include <Arduino.h>
#include <Debouncer.h>
#include <pins_arduino.h>
#include <PciManager.h>
#include <stdbool.h>
#include <SingleThreadPool.h>
#include <SoftTimer.h>
#include <Task.h>

#include "Buttons.h"
#include "controls/SerialVirtButtonsTask.h"
#include "display/BackLightHandler.h"
#include "display/BackLightTask.h"
#include "display/Display.h"
#include "display/DrawOnDisplayTask.h"
#include "display/SwitchScreenHandler.h"
#include "display/ToDraw.h"
#include "menu/ProgramMenu.h"
#include "net/Network.h"
#include "net/NetworkTestTask.h"
#include "ProgramSettings.h"
#include "sensors/AirPressureMeasureTask.h"
#include "sensors/LightIntensityMeasureTask.h"
#include "sensors/SensorReadingScreen.h"
#include "sensors/TempMeasureTask.h"
#include "time/Clock.h"
#include "time/TimeReading.h"
#include "time/TimeScreen.h"
#include "time/TimeSyncTask.h"

class ToDraw;

class ProgramState {
public:
    static const int DHT_PIN = 30;

    static const int LEFT_PIN = A12; //11;
    static const int RIGHT_PIN = A13; //10;
    static const int UP_PIN = A14; //12;
    static const int DOWN_PIN = A8; //9;
    static const int BACKLIGHT_PIN = A9; //5;
    static const int ENTER_PIN = A10; //6;
    static const int ESC_PIN = A11; //8;

    static const int TIME_SCREEN_NUMBER = 0;
    static const int TEMP_SCREEN_NUMBER = TIME_SCREEN_NUMBER + 1;
    static const int PRESSURE_SCREEN_NUMBER = TEMP_SCREEN_NUMBER + 1;
    static const int LIGHT_SCREEN_NUMBER = PRESSURE_SCREEN_NUMBER + 1;

    static const int COUNT_OF_SCREENS = LIGHT_SCREEN_NUMBER + 1;

//-----------------------------------------------------------------------------

private:
    ProgramSettings settings;

    Display disp;

    SingleThreadPool measureThread;
    SingleThreadPool displayThread;
    SingleThreadPool networkThread;

    Clock clock;
    TempMeasureTask measureTempTask;
    AirPressureMeasureTask measureAirPressureTask;
    LightIntensityMeasureTask measureLightIntensityTask;

    TimeScreen timeScreen;
    SensorReadingScreen tempScreen;
    SensorReadingScreen airPressureScreen;
    SensorReadingScreen lightIntensityScreen;

    ToDraw * displayScreens[COUNT_OF_SCREENS] = { &timeScreen, &tempScreen,
            &airPressureScreen, &lightIntensityScreen };

    BackLightTask backLightTask;
    DrawOnDisplayTask drawOnDisplayTask;

    ProgramMenu menu;

    SwitchScreenHandler nextScreen;
    SwitchScreenHandler prevScreen;
    BackLightHandler backLightHandler;

    Debouncer buttons[WeatherStation::Buttons::enumSize];

    SerialVirtButtonsTask serialVirtButtonsTask;

    volatile byte currentScreen;

    volatile bool backLight;

    Network network;
    NetworkTestTask networkTestTask;
    TimeSyncTask timeSyncTask;

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
        return clock.getTime(updateFirst);
    }

    unsigned long getTimeStamp(bool updateFirst = false) {
        return clock.getTime(updateFirst).getTimeStamp();
    }

    Clock& getClock() {
        return this->clock;
    }

    ProgramSettings& getSettings() {
        return settings;
    }

    Debouncer * getButtons() {
        return buttons;
    }

    ProgramMenu& getMenu() {
        return menu;
    }

    Network& getNetwork() {
        return network;
    }

    TimeSyncTask& getTimeSyncTask() {
        return timeSyncTask;
    }

private:
    ProgramState() :
            measureThread(512),
            displayThread(512),
            networkThread(512),

            measureTempTask(DHT_PIN, settings.getMeasureTempFreq()),
            measureAirPressureTask(settings.getMeasurePressureFreq()),
            measureLightIntensityTask(settings.getMeasureLightFreq()),

            tempScreen(measureTempTask.getLatestReading()),
            airPressureScreen(measureAirPressureTask.getLatestReading()),
            lightIntensityScreen(measureLightIntensityTask.getLatestReading()),

            backLightTask(disp.getLcd()),
            drawOnDisplayTask(settings.getDisplayDrawFreq(), disp.getLcd(),
                    displayScreens[settings.getStartupScreen()]),

            menu(disp.getLcd(), this, settings),

            nextScreen(1),
            prevScreen(-1),

            buttons { {LEFT_PIN, MODE_CLOSE_ON_PUSH, &prevScreen},
                    {RIGHT_PIN, MODE_CLOSE_ON_PUSH, &nextScreen},
                    {BACKLIGHT_PIN, MODE_CLOSE_ON_PUSH, &backLightHandler},
                    {UP_PIN, MODE_CLOSE_ON_PUSH, &ButtonHandler::voidButtonHandler()},
                    {DOWN_PIN, MODE_CLOSE_ON_PUSH, &ButtonHandler::voidButtonHandler()},
                    {ENTER_PIN, MODE_CLOSE_ON_PUSH, &menu.getEnterMenuHandler()},
                    {ESC_PIN, MODE_CLOSE_ON_PUSH, &ButtonHandler::voidButtonHandler()} },

            serialVirtButtonsTask(100),

            currentScreen(settings.getStartupScreen()),
            backLight(true),
            timeSyncTask(settings.getSyncTimeFreq()){

        pinMode(LED_BUILTIN, OUTPUT);

        measureTempTask.setThreadPool(&measureThread);
        measureAirPressureTask.setThreadPool(&measureThread);
        measureLightIntensityTask.setThreadPool(&measureThread);

        drawOnDisplayTask.setThreadPool(&displayThread);
        backLightTask.setThreadPool(&displayThread);

        SoftTimer & timer = SoftTimer::instance();
        timer.add(&measureTempTask);
        timer.add(&measureAirPressureTask);
        timer.add(&measureLightIntensityTask);
        timer.add(&drawOnDisplayTask);
        timer.add(&backLightTask);
        timer.add(&serialVirtButtonsTask);

        PciManager & pciManager = PciManager::instance();
        for (unsigned int i = 0; i < WeatherStation::Buttons::enumSize; i++) {
            pciManager.registerListener(&buttons[i]);
        }

        disp.doSetup();

        network.connect(settings);
        networkTestTask.setThreadPool(&networkThread);
        timeSyncTask.setThreadPool(&networkThread);
        timer.add(&networkTestTask);
        timer.add(&timeSyncTask);

        pciManager.setEnabled(true);
    }
};

#endif /* PROGRAMSTATE_H_ */
