/*
 * ProgramSettings.h
 *
 *  Created on: 22. 1. 2016
 *      Author: jindra
 */

#ifndef PROGRAMSETTINGS_H_
#define PROGRAMSETTINGS_H_

#include <EEPROM.h>
#include <OMEEPROM.h>
#include <stdint.h>

class ProgramSettings {
public:
    static const unsigned int SETTINGS_VERSION = 9;

    static const int WIFI_MAX_PASSWD_LENGTH = 63;
    static const int WIFI_MAX_SSID_LENGTH = 32;
    static const int DEPRECATED_WIFI_PASSWD_ARRAY_LENGTH = WIFI_MAX_PASSWD_LENGTH + 1;
    static const int DEPRECATED_WIFI_SSID_ARRAY_LENGTH = WIFI_MAX_SSID_LENGTH + 1;
    static const float DEFAULT_ALTITUDE;
    static const uint8_t DEFAULT_STARTUP_SCREEN = 0;
    static const unsigned int DEFAULT_MEASURE_TEMP_FREQ = 2;
    static const unsigned int DEFAULT_MEASURE_PRESSURE_FREQ = 1;
    static const unsigned int DEFAULT_MEASURE_LIGHT_FREQ = 1;
    static const unsigned int DEFAULT_DISPLAY_DRAW_FREQ = 1;
    static const int DEFAULT_TIME_ZONE = 2;
    static const unsigned int DEFAULT_SYNC_TIME_FREQ = 24;
    static const unsigned int DEFAULT_DATA_UPLOAD_MIN_FREQ = 3;
    static const unsigned int DEFAULT_WIFI_WATCHDOG_MIN_FREQ = 2;

    static const unsigned int MIN_ALTITUDE = 0;
    static const unsigned int MIN_MEASURE_TEMP_FREQ = 2;
    static const unsigned int MIN_MEASURE_PRESSURE_FREQ = 1;
#ifdef ENABLE_LIGHT_SENSOR
    static const unsigned int MIN_MEASURE_LIGHT_FREQ = 1;
#endif
    static const unsigned int MIN_DISPLAY_DRAW_FREQ = 1;
    static const unsigned int MIN_SYNC_TIME_FREQ = 1;
    static const int MIN_TIME_ZONE = -12;
    static const unsigned int MIN_DATA_UPLOAD_MIN_FREQ = 1;
    static const unsigned int MIN_WIFI_WATCHDOG_MIN_FREQ = 1;

    static const unsigned int SEC_IN_HOUR = 3600;

    static const unsigned int MAX_ALTITUDE = 10000;
    static const unsigned int MAX_MEASURE_TEMP_FREQ = SEC_IN_HOUR;
    static const unsigned int MAX_MEASURE_PRESSURE_FREQ = SEC_IN_HOUR;
#ifdef ENABLE_LIGHT_SENSOR
    static const unsigned int MAX_MEASURE_LIGHT_FREQ = SEC_IN_HOUR;
#endif
    static const unsigned int MAX_DISPLAY_DRAW_FREQ = SEC_IN_HOUR;
    static const unsigned int MAX_SYNC_TIME_FREQ = 9999;
    static const int MAX_TIME_ZONE = 12;
    static const unsigned int MAX_DATA_UPLOAD_MIN_FREQ = 60;
    static const unsigned int MAX_WIFI_WATCHDOG_MIN_FREQ = 60;

    static const unsigned long ONE_SEC_IN_US = 1000000;
    static const unsigned long ONE_MIN_IN_SEC = 60;

    static const unsigned long SECOND_RESOLUTION_MEASURE_TEMP_FREQ = 1;
    static const unsigned long SECOND_RESOLUTION_MEASURE_PRESSURE_FREQ = 1;
#ifdef ENABLE_LIGHT_SENSOR
    static const unsigned long SECOND_RESOLUTION_MEASURE_LIGHT_FREQ = 1;
#endif
    static const unsigned long SECOND_RESOLUTION_DISPLAY_DRAW_FREQ = 1;
    static const unsigned long SECOND_RESOLUTION_DATA_UPLOAD_MIN_FREQ =
            ONE_MIN_IN_SEC;
    static const unsigned long SECOND_RESOLUTION_WIFI_WATCHDOG_MIN_FREQ =
            ONE_MIN_IN_SEC;

    static const unsigned long USEC_RESOLUTION_MEASURE_TEMP_FREQ =
            SECOND_RESOLUTION_MEASURE_TEMP_FREQ * ONE_SEC_IN_US;
    static const unsigned long USEC_RESOLUTION_MEASURE_PRESSURE_FREQ =
            SECOND_RESOLUTION_MEASURE_PRESSURE_FREQ * ONE_SEC_IN_US;
#ifdef ENABLE_LIGHT_SENSOR
    static const unsigned long USEC_RESOLUTION_MEASURE_LIGHT_FREQ =
            SECOND_RESOLUTION_MEASURE_LIGHT_FREQ * ONE_SEC_IN_US;
#endif
    static const unsigned long USEC_RESOLUTION_DISPLAY_DRAW_FREQ =
            SECOND_RESOLUTION_DISPLAY_DRAW_FREQ * ONE_SEC_IN_US;
    static const unsigned long USEC_RESOLUTION_DATA_UPLOAD_MIN_FREQ =
            SECOND_RESOLUTION_DATA_UPLOAD_MIN_FREQ * ONE_SEC_IN_US;
    static const unsigned long USEC_RESOLUTION_WIFI_WATCHDOG_MIN_FREQ =
            SECOND_RESOLUTION_WIFI_WATCHDOG_MIN_FREQ * ONE_SEC_IN_US;

    static const int ALTITUDE_EPROM_ADDR = 16;
    static const int STARTUP_SCREEN_EPROM_ADDR = ALTITUDE_EPROM_ADDR
            + sizeof(float);
    static const int MEASURE_TEMP_FREQ_EPROM_ADDR = STARTUP_SCREEN_EPROM_ADDR
            + sizeof(uint8_t);
    static const int MEASURE_PRESSURE_FREQ_EPROM_ADDR =
            MEASURE_TEMP_FREQ_EPROM_ADDR + sizeof(unsigned int);
    static const int MEASURE_LIGHT_FREQ_EPROM_ADDR =
            MEASURE_PRESSURE_FREQ_EPROM_ADDR + sizeof(unsigned int);
    static const int DISPLAY_DRAW_FREQ_EPROM_ADDR =
            MEASURE_LIGHT_FREQ_EPROM_ADDR + sizeof(unsigned int);
    static const int DEPRECATED_WIFI_PASSWORD_EPROM_ADDR = 8 + DISPLAY_DRAW_FREQ_EPROM_ADDR
            + sizeof(unsigned int);
    static const int DEPRECATED_WIFI_SSID_EPROM_ADDR = DEPRECATED_WIFI_PASSWORD_EPROM_ADDR
            + DEPRECATED_WIFI_PASSWD_ARRAY_LENGTH;
    static const int TIME_ZONE_EPROM_ADDR = 8 + DEPRECATED_WIFI_SSID_EPROM_ADDR
            + DEPRECATED_WIFI_SSID_ARRAY_LENGTH;
    static const int SYNC_TIME_FREQ_EPROM_ADDR = 1 + TIME_ZONE_EPROM_ADDR
            + sizeof(int);
    static const int DATA_UPLOAD_MIN_EPROM_ADDR = SYNC_TIME_FREQ_EPROM_ADDR
            + sizeof(unsigned int);
    static const int WIFI_WATCHDOG_MIN_EPROM_ADDR = DATA_UPLOAD_MIN_EPROM_ADDR
            + sizeof(unsigned int);

    ProgramSettings();

    ProgramSettings(const ProgramSettings& that) = delete;
    void operator=(const ProgramSettings& that) = delete;

    void loadSettings();

    float getAltitude() const {
        return OMEEPROM::read<float>(ALTITUDE_EPROM_ADDR);
    }

    unsigned int getDisplayDrawSecondFreq() const {
        return OMEEPROM::read<unsigned int>(DISPLAY_DRAW_FREQ_EPROM_ADDR);
    }

    unsigned int getMeasureLightSecondFreq() const {
        return OMEEPROM::read<unsigned int>(MEASURE_LIGHT_FREQ_EPROM_ADDR);
    }

    unsigned int getMeasurePressureSecondFreq() const {
        return OMEEPROM::read<unsigned int>(MEASURE_PRESSURE_FREQ_EPROM_ADDR);
    }

    unsigned int getMeasureTempSecondFreq() const {
        return OMEEPROM::read<unsigned int>(MEASURE_TEMP_FREQ_EPROM_ADDR);
    }

    uint8_t getStartupScreen() const {
        return OMEEPROM::read<uint8_t>(STARTUP_SCREEN_EPROM_ADDR);
    }

    unsigned int getSyncTimeHourFreq() const {
        return OMEEPROM::read<unsigned int>(SYNC_TIME_FREQ_EPROM_ADDR);
    }

    int getTimeZone() const {
        return OMEEPROM::read<int>(TIME_ZONE_EPROM_ADDR);
    }

    unsigned int getDataUploadMinutesFreq() const {
        return OMEEPROM::read<unsigned int>(DATA_UPLOAD_MIN_EPROM_ADDR);
    }

    unsigned int getWifiWatchdogMinutesFreq() const {
        return OMEEPROM::read<unsigned int>(WIFI_WATCHDOG_MIN_EPROM_ADDR);
    }

    friend class ProgramMenu;
};

#endif /* PROGRAMSETTINGS_H_ */
