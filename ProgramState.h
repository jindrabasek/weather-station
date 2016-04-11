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
#include <HardwareSerial.h>
#include <HttpClient.h>
#include <pins_arduino.h>
#include <PciManager.h>
#include <stdbool.h>
#include <SoftTimer.h>
#include <utility/EspDrv.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WString.h>

#include "controls/SerialVirtButtonsTask.h"
#include "display/BackLightHandler.h"
#include "display/BackLightTask.h"
#include "display/Display.h"
#include "display/DrawOnDisplayTask.h"
#include "display/SwitchScreenHandler.h"
#include "display/ToDraw.h"
#include "menu/ProgramMenu.h"
#include "ProgramSettings.h"
#include "sensors/AirPressureMeasureTask.h"
#include "sensors/LightIntensityMeasureTask.h"
#include "sensors/SensorReadingScreen.h"
#include "sensors/TempMeasureTask.h"
#include "time/Time.h"
#include "time/TimeReading.h"
#include "time/TimeScreen.h"

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

    Time time;
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

    Debouncer leftButton;
    Debouncer rightButton;
    Debouncer backLightButton;
    Debouncer upButton;
    Debouncer downButton;
    Debouncer enterButton;
    Debouncer escButton;

    SerialVirtButtonsTask serialVirtButtonsTask;

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

    Debouncer& getEscButton() {
        return escButton;
    }

    ProgramMenu& getMenu() {
        return menu;
    }

private:
    ProgramState() :
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

            leftButton(LEFT_PIN, MODE_CLOSE_ON_PUSH, &prevScreen),
            rightButton(RIGHT_PIN, MODE_CLOSE_ON_PUSH, &nextScreen),
            backLightButton(BACKLIGHT_PIN, MODE_CLOSE_ON_PUSH,
                    &backLightHandler),
            upButton(UP_PIN, MODE_CLOSE_ON_PUSH,
                    &ButtonHandler::voidButtonHandler()),
            downButton(DOWN_PIN, MODE_CLOSE_ON_PUSH,
                    &ButtonHandler::voidButtonHandler()),
            enterButton(ENTER_PIN, MODE_CLOSE_ON_PUSH,
                    &menu.getEnterMenuHandler()),
            escButton(ESC_PIN, MODE_CLOSE_ON_PUSH,
                    &ButtonHandler::voidButtonHandler()),

            serialVirtButtonsTask(100),

            currentScreen(settings.getStartupScreen()),
            backLight(true) {

        pinMode(LED_BUILTIN, OUTPUT);

        SoftTimer & timer = SoftTimer::instance();
        timer.add(&measureTempTask);
        timer.add(&measureAirPressureTask);
        timer.add(&measureLightIntensityTask);
        timer.add(&drawOnDisplayTask);
        timer.add(&backLightTask);
        timer.add(&serialVirtButtonsTask);

        PciManager & pciManager = PciManager::instance();
        pciManager.registerListener(&leftButton);
        pciManager.registerListener(&rightButton);
        pciManager.registerListener(&backLightButton);
        pciManager.registerListener(&upButton);
        pciManager.registerListener(&downButton);
        pciManager.registerListener(&enterButton);
        pciManager.registerListener(&escButton);

        //mySerial.begin(9600);

        disp.doSetup();

        pciManager.setEnabled(true);

        // initialize ESP module
        WiFi.init(&Serial1, 9600);

        // check for the presence of the shield
        if (WiFi.status() == WL_NO_SHIELD) {
            Serial.println(F("WiFi shield not present"));
        } else {
            char ssid[] = "***REMOVED***";            // your network SSID (name)
            char pass[] = "***REMOVED***";        // your network password

            // attempt to connect to WiFi network
            Serial.print(F("Attempting to connect to SSID: "));
            Serial.println(ssid);

            int status = WL_IDLE_STATUS;
            // Connect to WPA/WPA2 network
            status = WiFi.begin(ssid, pass);

            if (status == WL_CONNECTED) {
                Serial.println(F("Connected to AP"));

                WiFiEspClient client;

                HttpClient http(client);

                Serial.println(F("Getting page...\n"));

                int err = http.get("arduino.cc", "/asciilogo.txt");
                if (err == 0) {
                    err = http.responseStatusCode();
                    if (err >= 0) {

                        // Usually you'd check that the response code is 200 or a
                        // similar "success" code (200-299) before carrying on,
                        // but we'll print out whatever response we get

                        err = http.skipResponseHeaders();
                        if (err >= 0) {
                            // Whilst we haven't timed out & haven't reached the end of the body
                            while (http.available()) {
                                char c = http.read();
                                // Print out this character
                                Serial.print(c);
                            }
                            Serial.println(F("Page loaded!\n"));
                        } else {
                            Serial.print("Failed to skip response headers: ");
                            Serial.println(err);
                        }
                    } else {
                        Serial.print("Getting response failed: ");
                        Serial.println(err);
                    }
                } else {
                    Serial.print("Connect failed: ");
                    Serial.println(err);
                }
                http.stop();

            } else {
                Serial.println(F("WiFi connection failed!"));
            }
        }

    }
};

#endif /* PROGRAMSTATE_H_ */
