/*
 * PrgState.h
 *
 *  Created on: 13. 1. 2016
 *      Author: jindra
 */

#ifndef PROGRAMSTATE_H_
#define PROGRAMSTATE_H_

#include "ProgramState.h"

#include <avr/pgmspace.h>
#include <Debouncer.h>
#include <pins_arduino.h>
#include <PciManager.h>
#include <sensors/LightIntensityMeasureTask.h>
#include <sensors/LightIntensityReading.h>
#include <sensors/TempReading.h>
#include <stddef.h>
#include <stdint.h>
#include <SensorIds.h>
#include <SingleThreadPool.h>
#include <SoftTimer.h>
#include <Task.h>

#include "controls/Buttons.h"
#include "controls/SerialVirtButtonsTask.h"
#include "display/BackLightHandler.h"
#include "display/BackLightTask.h"
#include "display/Display.h"
#include "display/DrawOnDisplayTask.h"
#include "display/SwitchScreenHandler.h"
#include "display/ToDraw.h"
#include "menu/ProgramMenu.h"
#include "net/AppStartUploadFlags.h"
#include "net/MqttLoopTask.h"
#include "net/MqttPublishTask.h"
#include "net/NetworkTestTask.h"
#ifdef ENABLE_SMART_LIVING
#include "net/SmartLivingPublishTask.h"
#endif
#include "net/WifiWatchdogTask.h"
#include "ProgramSettings.h"
#include "sensors/AirPressureMeasureTask.h"
#include "sensors/AirPressureReading.h"
#include "sensors/SensorReadingScreen.h"
#include "sensors/Si7010TempMeasureTask.h"
#ifdef ENABLE_W433_SENSORS
#include "sensors/Wireless433MhzTask.h"
#include "sensors/WirelessTempScreen.h"
#include "sensors/WirelessTempSensorReading.h"
#endif
#include "time/TimeScreen.h"
#include "time/TimeSyncTask.h"

class ToDraw;

class ProgramState {
public:
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
#ifdef ENABLE_LIGHT_SENSOR
    static const int LIGHT_SCREEN_NUMBER = PRESSURE_SCREEN_NUMBER + 1;
#ifdef ENABLE_W433_SENSORS
    static const int TEMP_SCREEN_OUTDOOR_NUMBER = LIGHT_SCREEN_NUMBER + 1;
    static const int LIGHT_SCREEN_OUTDOOR_NUMBER = TEMP_SCREEN_OUTDOOR_NUMBER + 1;
    static const int SENCOR_WIRELESS_SCREEN_NUMBER = LIGHT_SCREEN_OUTDOOR_NUMBER + 1;
    static const int COUNT_OF_SCREENS = SENCOR_WIRELESS_SCREEN_NUMBER + 1;
#endif
#else
#ifdef ENABLE_W433_SENSORS
    static const int TEMP_SCREEN_OUTDOOR_NUMBER = PRESSURE_SCREEN_NUMBER + 1;
    static const int LIGHT_SCREEN_OUTDOOR_NUMBER = TEMP_SCREEN_OUTDOOR_NUMBER + 1;
    static const int SENCOR_WIRELESS_SCREEN_NUMBER = LIGHT_SCREEN_OUTDOOR_NUMBER + 1;
    static const int COUNT_OF_SCREENS = SENCOR_WIRELESS_SCREEN_NUMBER + 1;
#else
    static const int COUNT_OF_SCREENS = PRESSURE_SCREEN_NUMBER + 1;
#endif
#endif


//-----------------------------------------------------------------------------

private:
    ProgramSettings settings;

    Display disp;

    SingleThreadPool measureThread;
    SingleThreadPool displayThread;
    SingleThreadPool networkThread;

    Si7010TempMeasureTask measureTempTask;
    AirPressureMeasureTask measureAirPressureTask;
#ifdef ENABLE_LIGHT_SENSOR
    LightIntensityMeasureTask measureLightIntensityTask;
#endif

#ifdef ENABLE_W433_SENSORS
    Wireless433MhzTask wireless433MhzTask;
#endif

    TimeScreen timeScreen;
    SensorReadingScreen tempScreen;
    SensorReadingScreen airPressureScreen;
#ifdef ENABLE_LIGHT_SENSOR
    SensorReadingScreen lightIntensityScreen;
#endif
#ifdef ENABLE_W433_SENSORS
    SensorReadingScreen tempOutdoorScreen;
    SensorReadingScreen lightIntensityOutdoorScreen;
    WirelessTempScreen wirelessTempSencorScreen;
#endif

    ToDraw * displayScreens[COUNT_OF_SCREENS] = { &timeScreen, &tempScreen,
            &airPressureScreen
#ifdef ENABLE_LIGHT_SENSOR
			, &lightIntensityScreen
#endif
#ifdef ENABLE_W433_SENSORS
			, &tempOutdoorScreen,
            &lightIntensityOutdoorScreen,
			&wirelessTempSencorScreen
#endif
    };

    BackLightTask backLightTask;
    DrawOnDisplayTask drawOnDisplayTask;

    ProgramMenu menu;

    SwitchScreenHandler nextScreen;
    SwitchScreenHandler prevScreen;
    BackLightHandler backLightHandler;

    Debouncer buttons[WeatherStation::Buttons::ButtonsEnumSize];

    SerialVirtButtonsTask serialVirtButtonsTask;

    volatile uint8_t currentScreen;

    volatile bool backLight;

    SensorReading * sensorValues[WeatherStation::SensorValueId::SensorsEnumSize] =
            { NULL };

    NetworkTestTask networkTestTask;
    TimeSyncTask timeSyncTask;
    MqttLoopTask mqttLoopTask;
    MqttPublishTask mqttPublishTask;

#ifdef ENABLE_SMART_LIVING
    SmartLivingPublishTask dataUploadTask;
#endif
    WifiWatchdogTask wifiWatchDogTask;

    void setStateRef();

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

    DrawOnDisplayTask& getDrawOnDisplayTask() {
        return drawOnDisplayTask;
    }

    AirPressureMeasureTask& getMeasureAirPressureTask() {
        return measureAirPressureTask;
    }

#ifdef ENABLE_LIGHT_SENSOR
    LightIntensityMeasureTask& getMeasureLightIntensityTask() {
        return measureLightIntensityTask;
    }
#endif

    Si7010TempMeasureTask& getMeasureTempTask() {
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

    ProgramSettings& getSettings() {
        return settings;
    }

    Debouncer * getButtons() {
        return buttons;
    }

    ProgramMenu& getMenu() {
        return menu;
    }

    TimeSyncTask& getTimeSyncTask() {
        return timeSyncTask;
    }

    SensorReading** getSensorValues() {
        return sensorValues;
    }

#ifdef ENABLE_SMART_LIVING
    SmartLivingPublishTask& getDataUploadTask() {
        return dataUploadTask;
    }
#endif

    WifiWatchdogTask& getWifiWatchDogTask() {
        return wifiWatchDogTask;
    }

#ifdef ENABLE_W433_SENSORS
    Wireless433MhzTask& getWireless433MhzTask() {
        return wireless433MhzTask;
    }
#endif

    MqttLoopTask& getMqttLoopTask() {
        return mqttLoopTask;
    }

private:
    ProgramState() :
            measureThread(700),
            displayThread(700),
            networkThread(800),

            measureTempTask(
                    settings.getMeasureTempSecondFreq()
                            * ProgramSettings::USEC_RESOLUTION_MEASURE_TEMP_FREQ),
            measureAirPressureTask(
                    settings.getMeasurePressureSecondFreq()
                            * ProgramSettings::USEC_RESOLUTION_MEASURE_PRESSURE_FREQ),
#ifdef ENABLE_LIGHT_SENSOR
            measureLightIntensityTask(
                    settings.getMeasureLightSecondFreq()
                            * ProgramSettings::USEC_RESOLUTION_MEASURE_LIGHT_FREQ),
#endif

            tempScreen(measureTempTask.getLatestReading()),
            airPressureScreen(measureAirPressureTask.getLatestReading()),
#ifdef ENABLE_LIGHT_SENSOR
            lightIntensityScreen(measureLightIntensityTask.getLatestReading()),
#endif
#ifdef ENABLE_W433_SENSORS
            tempOutdoorScreen(wireless433MhzTask.getLatestReadingTemperatueOutdoor()),
            lightIntensityOutdoorScreen(wireless433MhzTask.getLatestReadingIntensityOutdoor()),
            wirelessTempSencorScreen(WeatherStation::SensorValueId::WIRELESS_TEMPERTAURE_SWSTS_CH1, PSTR("Sencor Temp")),
#endif

            backLightTask(disp.getLcd()),
            drawOnDisplayTask(
                    settings.getDisplayDrawSecondFreq()
                            * ProgramSettings::USEC_RESOLUTION_DISPLAY_DRAW_FREQ,
                    disp, displayScreens[settings.getStartupScreen()]),

            menu(disp.getLcd(), this),

            nextScreen(1),
            prevScreen(-1),

            buttons { //{ LEFT_PIN, MODE_CLOSE_ON_PUSH, &prevScreen },
                      //{ RIGHT_PIN, MODE_CLOSE_ON_PUSH, &nextScreen },
            { BACKLIGHT_PIN, MODE_CLOSE_ON_PUSH, &backLightHandler }, { UP_PIN,
                    MODE_CLOSE_ON_PUSH, &prevScreen }, { DOWN_PIN,
                    MODE_CLOSE_ON_PUSH, &nextScreen }, { ENTER_PIN,
                    MODE_CLOSE_ON_PUSH, &menu.getEnterMenuHandler() }, {
                    ESC_PIN, MODE_CLOSE_ON_PUSH,
                    &ButtonHandler::voidButtonHandler } },

            serialVirtButtonsTask(100),

            currentScreen(settings.getStartupScreen()),
            backLight(false),
            timeSyncTask(settings.getSyncTimeHourFreq()),
            mqttPublishTask(
                    settings.getDataUploadMinutesFreq()
                            * ProgramSettings::USEC_RESOLUTION_DATA_UPLOAD_MIN_FREQ),
#ifdef ENABLE_SMART_LIVING
            dataUploadTask(
                    settings.getDataUploadMinutesFreq()
                            * ProgramSettings::USEC_RESOLUTION_DATA_UPLOAD_MIN_FREQ),
#endif
            wifiWatchDogTask(
                    settings.getWifiWatchdogMinutesFreq()
                            * ProgramSettings::USEC_RESOLUTION_WIFI_WATCHDOG_MIN_FREQ) {

        measureTempTask.setThreadPool(&measureThread);
        measureAirPressureTask.setThreadPool(&measureThread);
#ifdef ENABLE_LIGHT_SENSOR
        measureLightIntensityTask.setThreadPool(&measureThread);
#endif
#ifdef ENABLE_W433_SENSORS
        wireless433MhzTask.setThreadPool(&measureThread);
#endif

        drawOnDisplayTask.setThreadPool(&displayThread);
        backLightTask.setThreadPool(&displayThread);

        SoftTimer.add(&measureTempTask);
        SoftTimer.add(&measureAirPressureTask);
#ifdef ENABLE_LIGHT_SENSOR
        SoftTimer.add(&measureLightIntensityTask);
#endif
#ifdef ENABLE_W433_SENSORS
        SoftTimer.add(&wireless433MhzTask);
#endif
        SoftTimer.add(&drawOnDisplayTask);
        SoftTimer.add(&backLightTask);
        SoftTimer.add(&serialVirtButtonsTask);

        for (uint8_t i = 0; i < WeatherStation::Buttons::ButtonsEnumSize; i++) {
            PciManager.registerListener(&buttons[i]);
        }

        measureTempTask.getLatestReading().registerSensorValues(sensorValues);
        measureAirPressureTask.getLatestReading().registerSensorValues(
                sensorValues);
#ifdef ENABLE_LIGHT_SENSOR
        measureLightIntensityTask.getLatestReading().registerSensorValues(
                sensorValues);
#endif
#ifdef ENABLE_W433_SENSORS
        wireless433MhzTask.getLatestReadingSencor(1).registerSensorValues(
                sensorValues);
        wireless433MhzTask.getLatestReadingSencor(2).registerSensorValues(
                sensorValues);
        wireless433MhzTask.getLatestReadingSencor(3).registerSensorValues(
                sensorValues);
        wireless433MhzTask.getLatestReadingIntensityOutdoor()
                .registerSensorValues(sensorValues);
        wireless433MhzTask.getLatestReadingTemperatueOutdoor()
                .registerSensorValues(sensorValues);
#endif

        networkTestTask.setThreadPool(&networkThread);
        timeSyncTask.setThreadPool(&networkThread);
        //mqttLoopTask.setThreadPool(&networkThread);
        mqttPublishTask.setThreadPool(&networkThread);
#ifdef ENABLE_SMART_LIVING
        dataUploadTask.setThreadPool(&networkThread);
#endif
        wifiWatchDogTask.setThreadPool(&networkThread);
        SoftTimer.add(&wifiWatchDogTask);
        SoftTimer.add(&networkTestTask);
        SoftTimer.add(&timeSyncTask);
        // do manually from publish task for now
        //SoftTimer.add(&mqttLoopTask);
        SoftTimer.add(&mqttPublishTask);
#ifdef ENABLE_SMART_LIVING
        SoftTimer.add(&dataUploadTask);
#endif

        PciManager.setEnabled(true);

        WeatherStation::AppStartUploadFlags::appStarted();

        setStateRef();
    }
};

#endif /* PROGRAMSTATE_H_ */
