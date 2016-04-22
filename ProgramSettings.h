/*
 * ProgramSettings.h
 *
 *  Created on: 22. 1. 2016
 *      Author: jindra
 */

#ifndef PROGRAMSETTINGS_H_
#define PROGRAMSETTINGS_H_

#include <Arduino.h>
#include <stdbool.h>

class ProgramSettings {
public:
    static const unsigned int SETTINGS_VERSION = 5;

    static const int WIFI_MAX_PASSWD_LENGTH = 63;
    static const int WIFI_MAX_SSID_LENGTH = 32;
    static const float DEFAULT_ALTITUDE;
    static const byte DEFAULT_STARTUP_SCREEN = 0;
    static const unsigned int DEFAULT_MEASURE_TEMP_FREQ = 2;
    static const unsigned int DEFAULT_MEASURE_PRESSURE_FREQ = 1;
    static const unsigned int DEFAULT_MEASURE_LIGHT_FREQ = 1;
    static const unsigned int DEFAULT_DISPLAY_DRAW_FREQ = 1;
    static const int DEFAULT_TIME_ZONE = 2;
    static const unsigned int DEFAULT_SYNC_TIME_FREQ = 24;

    static const unsigned int MIN_ALTITUDE = 0;
    static const unsigned int MIN_MEASURE_TEMP_FREQ = 2;
    static const unsigned int MIN_MEASURE_PRESSURE_FREQ = 1;
    static const unsigned int MIN_MEASURE_LIGHT_FREQ = 1;
    static const unsigned int MIN_DISPLAY_DRAW_FREQ = 1;
    static const unsigned int MIN_SYNC_TIME_FREQ = 1;
    static const int MIN_TIME_ZONE = -12;

    static const unsigned int SEC_IN_HOUR = 3600;

    static const unsigned int MAX_ALTITUDE = 10000;
    static const unsigned int MAX_MEASURE_TEMP_FREQ = SEC_IN_HOUR;
    static const unsigned int MAX_MEASURE_PRESSURE_FREQ = SEC_IN_HOUR;
    static const unsigned int MAX_MEASURE_LIGHT_FREQ = SEC_IN_HOUR;
    static const unsigned int MAX_DISPLAY_DRAW_FREQ = SEC_IN_HOUR;
    static const unsigned int MAX_SYNC_TIME_FREQ = 9999;
    static const int MAX_TIME_ZONE = 12;

    static const unsigned long ONE_SEC_IN_US = 1000000;

    static const unsigned long RESOLUTION_MEASURE_TEMP_FREQ = ONE_SEC_IN_US;
    static const unsigned long RESOLUTION_MEASURE_PRESSURE_FREQ = ONE_SEC_IN_US;
    static const unsigned long RESOLUTION_MEASURE_LIGHT_FREQ = ONE_SEC_IN_US;
    static const unsigned long RESOLUTION_DISPLAY_DRAW_FREQ = ONE_SEC_IN_US;

private:
    float altitude;
    byte startupScreen;
    unsigned long measureTempFreq;
    unsigned long measurePressureFreq;
    unsigned long measureLightFreq;
    unsigned long displayDrawFreq;
    char wifiPasswd[WIFI_MAX_PASSWD_LENGTH + 1] = {0};
    char wifiSsid[WIFI_MAX_SSID_LENGTH + 1] = {0};
    int timeZone;
    unsigned long syncTimeFreq;

public:

    static const int ALTITUDE_EPROM_ADDR = 16;
    static const int STARTUP_SCREEN_EPROM_ADDR = ALTITUDE_EPROM_ADDR
            + sizeof(altitude);
    static const int MEASURE_TEMP_FREQ_EPROM_ADDR = STARTUP_SCREEN_EPROM_ADDR
            + sizeof(startupScreen);
    static const int MEASURE_PRESSURE_FREQ_EPROM_ADDR =
            MEASURE_TEMP_FREQ_EPROM_ADDR + sizeof(measureTempFreq);
    static const int MEASURE_LIGHT_FREQ_EPROM_ADDR =
            MEASURE_PRESSURE_FREQ_EPROM_ADDR + sizeof(measurePressureFreq);
    static const int DISPLAY_DRAW_FREQ_EPROM_ADDR =
            MEASURE_LIGHT_FREQ_EPROM_ADDR + sizeof(measureLightFreq);
    static const int WIFI_PASSWORD_EPROM_ADDR =
            8 + DISPLAY_DRAW_FREQ_EPROM_ADDR + sizeof(displayDrawFreq);
    static const int WIFI_SSID_EPROM_ADDR =
            WIFI_PASSWORD_EPROM_ADDR + sizeof(wifiPasswd);
    static const int TIME_ZONE_EPROM_ADDR =
            8 + WIFI_SSID_EPROM_ADDR + sizeof(wifiSsid);
    static const int SYNC_TIME_FREQ_EPROM_ADDR =
            1 + TIME_ZONE_EPROM_ADDR + sizeof(timeZone);

    ProgramSettings();

    ProgramSettings(const ProgramSettings& that) = delete;
    void operator=(const ProgramSettings& that) = delete;

    void loadSettings();

    float getAltitude() const {
        return altitude;
    }

    unsigned long getDisplayDrawFreq() const {
        return displayDrawFreq * RESOLUTION_DISPLAY_DRAW_FREQ;
    }

    unsigned long getMeasureLightFreq() const {
        return measureLightFreq * RESOLUTION_MEASURE_LIGHT_FREQ;
    }

    unsigned long getMeasurePressureFreq() const {
        return measurePressureFreq * RESOLUTION_MEASURE_PRESSURE_FREQ;
    }

    unsigned long getMeasureTempFreq() const {
        return measureTempFreq * RESOLUTION_MEASURE_TEMP_FREQ;
    }

    byte getStartupScreen() const {
        return startupScreen;
    }

    const char * getWifiPasswd() const {
        return wifiPasswd;
    }

    const char * getWifiSsid() const {
        return wifiSsid;
    }

    unsigned long getSyncTimeFreq() const {
        return syncTimeFreq;
    }

    int getTimeZone() const {
        return timeZone;
    }

    friend class ProgramMenu;

};

#endif /* PROGRAMSETTINGS_H_ */
