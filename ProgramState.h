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
#include <stdint.h>
#include <SingleThreadPool.h>
#include <SoftTimer.h>
#include <Task.h>

#include "controls/Buttons.h"
#include "controls/SerialVirtButtonsSchedulable.h"
#include "display/BackLightHandler.h"
#include "display/BackLightTask.h"
#include "display/Display.h"
#include "display/DrawOnDisplaySchedulable.h"
#include "display/SwitchScreenHandler.h"
#include "display/ToDraw.h"
#include "menu/ProgramMenu.h"
#include "net/Network.h"
#include "net/NetworkTestSchedulable.h"
#include "net/SmartLivingPublishSchedulable.h"
#include "net/WifiWatchdogSchedulable.h"
#include "ProgramSettings.h"
#include "sensors/AirPressureMeasureSchedulable.h"
#include "sensors/LightIntensityMeasureSchedulable.h"
#include "sensors/SensorReading.h"
#include "sensors/SensorReadingScreen.h"
#include "sensors/Sensors.h"
#include "sensors/TempMeasureSchedulable.h"
#include "time/Clock.h"
#include "time/TimeReading.h"
#include "time/TimeScreen.h"
#include "time/TimeSyncSchedulable.h"

/*
 *Program:   61884 bytes (23.6% Full)
(.text + .data + .bootloader)

Data:       2797 bytes (34.1% Full)
(.data + .bss + .noinit)
 *
 *
 */

class ToDraw;

class ProgramState {
public:
    static const int DHT_PIN = 30;

    //static const int LEFT_PIN = A12; //11;
    //static const int RIGHT_PIN = A13; //10;
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

    TempMeasureSchedulable measureTempSchedulable;
    Task measureTempTask;
    AirPressureMeasureSchedulable measureAirPressureSchedulable;
    Task measureAirPressureTask;
    LightIntensityMeasureSchedulable measureLightIntensitySchedulable;
    Task measureLightIntensityTask;

    TimeScreen timeScreen;
    SensorReadingScreen tempScreen;
    SensorReadingScreen airPressureScreen;
    SensorReadingScreen lightIntensityScreen;

    ToDraw * displayScreens[COUNT_OF_SCREENS] = { &timeScreen, &tempScreen,
            &airPressureScreen, &lightIntensityScreen };

    BackLightTask backLightTask;
    DrawOnDisplaySchedulable drawOnDisplaySchedulable;
    Task drawOnDisplayTask;

    ProgramMenu menu;

    SwitchScreenHandler nextScreen;
    SwitchScreenHandler prevScreen;
    BackLightHandler backLightHandler;

    Debouncer buttons[WeatherStation::Buttons::buttonsEnumSize];

    SerialVirtButtonsSchedulable serialVirtButtonsSchedulable;
    Task serialVirtButtonsTask;

    volatile uint8_t currentScreen;

    volatile bool backLight;

    SensorReading * sensorValues[WeatherStation::Sensors::sensorsEnumSize];

    NetworkTestSchedulable networkTestSchedulable;
    Task networkTestTask;
    TimeSyncSchedulable timeSyncSchedulable;
    LongTask timeSyncTask;
    SmartLivingPublishSchedulable dataUploadSchedulable;
    Task dataUploadTask;
    WifiWatchdogSchedulable wifiWatchDogSchedulable;
    Task wifiWatchDogTask;



//-----------------------------------------------------------------------------

public:
    ProgramState(const ProgramState& that) = delete;
    void operator=(const ProgramState& that) = delete;
    static ProgramState& instance();

    volatile uint8_t getCurrentScreen() const {
        return currentScreen;
    }

    void setCurrentScreen(volatile uint8_t currentScreen) {
        this->currentScreen = currentScreen;
    }

    ToDraw ** getDisplayScreens() {
        return displayScreens;
    }

    Task& getDrawOnDisplayTask() {
        return drawOnDisplayTask;
    }

    DrawOnDisplaySchedulable& getDrawOnDisplaySchedulable() {
        return drawOnDisplaySchedulable;
    }

    Task& getMeasureAirPressureTask() {
        return measureAirPressureTask;
    }

    Task& getMeasureLightIntensityTask() {
        return measureLightIntensityTask;
    }

    Task& getMeasureTempTask() {
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
        return Clock::getTime(updateFirst);
    }

    unsigned long getTimeStamp(bool updateFirst = false) {
        return Clock::getTime(updateFirst).getTimeStamp();
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

    LongTask& getTimeSyncTask() {
        return timeSyncTask;
    }

    SensorReading** getSensorValues() {
        return sensorValues;
    }

    Task& getDataUploadTask() {
        return dataUploadTask;
    }

    Task& getWifiWatchDogTask() {
        return wifiWatchDogTask;
    }

    WifiWatchdogSchedulable& getWifiWatchDogSchedulable() {
        return wifiWatchDogSchedulable;
    }

private:
    ProgramState() :
            measureThread(512),
            displayThread(512),
            networkThread(512),

            measureTempSchedulable(DHT_PIN),
            measureTempTask(&measureTempSchedulable,
                    settings.getMeasureTempSecondFreq()
                            * ProgramSettings::USEC_RESOLUTION_MEASURE_TEMP_FREQ),
            measureAirPressureTask(&measureAirPressureSchedulable,
                    settings.getMeasurePressureSecondFreq()
                            * ProgramSettings::USEC_RESOLUTION_MEASURE_PRESSURE_FREQ),
            measureLightIntensityTask(&measureLightIntensitySchedulable,
                    settings.getMeasureLightSecondFreq()
                            * ProgramSettings::USEC_RESOLUTION_MEASURE_LIGHT_FREQ),

            tempScreen(measureTempSchedulable.getLatestReading()),
            airPressureScreen(measureAirPressureSchedulable.getLatestReading()),
            lightIntensityScreen(measureLightIntensitySchedulable.getLatestReading()),

            backLightTask(disp.getLcd()),
            drawOnDisplaySchedulable(disp.getLcd(), displayScreens[settings.getStartupScreen()]),
            drawOnDisplayTask(&drawOnDisplaySchedulable,
                    settings.getDisplayDrawSecondFreq()
                            * ProgramSettings::USEC_RESOLUTION_DISPLAY_DRAW_FREQ),

            menu(disp.getLcd(), this, settings),

            nextScreen(1),
            prevScreen(-1),

            buttons { //{ LEFT_PIN, MODE_CLOSE_ON_PUSH, &prevScreen },
                      //{ RIGHT_PIN, MODE_CLOSE_ON_PUSH, &nextScreen },
                      { BACKLIGHT_PIN, MODE_CLOSE_ON_PUSH, &backLightHandler },
                      { UP_PIN, MODE_CLOSE_ON_PUSH, &prevScreen },
                      { DOWN_PIN, MODE_CLOSE_ON_PUSH, &nextScreen },
                      { ENTER_PIN, MODE_CLOSE_ON_PUSH, &menu.getEnterMenuHandler() },
                      { ESC_PIN, MODE_CLOSE_ON_PUSH, &ButtonHandler::voidButtonHandler } },

            serialVirtButtonsTask(&serialVirtButtonsSchedulable, 100),

            currentScreen(settings.getStartupScreen()),
            backLight(true),
            networkTestTask(&networkTestSchedulable, 0),
            timeSyncTask(&timeSyncSchedulable, settings.getSyncTimeHourFreq(), 0),
            dataUploadTask(&dataUploadSchedulable,
                    settings.getDataUploadMinutesFreq()
                            * ProgramSettings::USEC_RESOLUTION_DATA_UPLOAD_MIN_FREQ),
            wifiWatchDogTask(&wifiWatchDogSchedulable, settings.getWifiWatchdogMinutesFreq()
                    * ProgramSettings::USEC_RESOLUTION_WIFI_WATCHDOG_MIN_FREQ){

        pinMode(LED_BUILTIN, OUTPUT);

        measureTempTask.setThreadPool(&measureThread);
        measureAirPressureTask.setThreadPool(&measureThread);
        measureLightIntensityTask.setThreadPool(&measureThread);

        drawOnDisplayTask.setThreadPool(&displayThread);
        backLightTask.setThreadPool(&displayThread);

        SoftTimer.add(&measureTempTask);
        SoftTimer.add(&measureAirPressureTask);
        SoftTimer.add(&measureLightIntensityTask);
        SoftTimer.add(&drawOnDisplayTask);
        SoftTimer.add(&backLightTask);
        SoftTimer.add(&serialVirtButtonsTask);

        for (uint8_t i = 0; i < WeatherStation::Buttons::buttonsEnumSize;
                i++) {
            PciManager.registerListener(&buttons[i]);
        }

        disp.doSetup();

        measureTempSchedulable.getLatestReading().registerSensorValues(sensorValues);
        measureAirPressureSchedulable.getLatestReading().registerSensorValues(
                sensorValues);
        measureLightIntensitySchedulable.getLatestReading().registerSensorValues(
                sensorValues);

        Network::connect(settings);
        networkTestTask.setThreadPool(&networkThread);
        networkTestTask.startAtEarliestOportunity();
        timeSyncTask.setThreadPool(&networkThread);
        timeSyncTask.startAtEarliestOportunity();
        dataUploadTask.setThreadPool(&networkThread);
        dataUploadTask.startAtEarliestOportunity();
        wifiWatchDogTask.setThreadPool(&networkThread);
        SoftTimer.add(&networkTestTask);
        SoftTimer.add(&timeSyncTask);
        SoftTimer.add(&dataUploadTask);
        SoftTimer.add(&wifiWatchDogTask);

        PciManager.setEnabled(true);
    }
};

#endif /* PROGRAMSTATE_H_ */
