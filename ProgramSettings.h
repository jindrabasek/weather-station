/*
 * ProgramSettings.h
 *
 *  Created on: 22. 1. 2016
 *      Author: jindra
 */

#ifndef PROGRAMSETTINGS_H_
#define PROGRAMSETTINGS_H_

#include <OMEEPROM.h>

class ProgramSettings {
private:
	float altitude;
	byte startupScreen;
	unsigned long measureTempFreq;
	unsigned long measurePressureFreq;
	unsigned long measureLightFreq;
	unsigned long displayDrawFreq;

public:
	static const float DEFAULT_ALTITUDE;
	static const byte DEFAULT_STARTUP_SCREEN = 0;
	static const unsigned int DEFAULT_MEASURE_TEMP_FREQ = 2;
	static const unsigned int DEFAULT_MEASURE_PRESSURE_FREQ = 1;
	static const unsigned int DEFAULT_MEASURE_LIGHT_FREQ = 1;
	static const unsigned int DEFAULT_DISPLAY_DRAW_FREQ = 1;

	static const unsigned int MIN_ALTITUDE = 0;
	static const unsigned int MIN_MEASURE_TEMP_FREQ = 2;
	static const unsigned int MIN_MEASURE_PRESSURE_FREQ = 1;
	static const unsigned int MIN_MEASURE_LIGHT_FREQ = 1;
	static const unsigned int MIN_DISPLAY_DRAW_FREQ = 1;

	static const unsigned int SEC_IN_HOUR = 3600;

	static const unsigned int MAX_ALTITUDE = 10000;
	static const unsigned int MAX_MEASURE_TEMP_FREQ = SEC_IN_HOUR;
	static const unsigned int MAX_MEASURE_PRESSURE_FREQ = SEC_IN_HOUR;
	static const unsigned int MAX_MEASURE_LIGHT_FREQ = SEC_IN_HOUR;
	static const unsigned int MAX_DISPLAY_DRAW_FREQ = SEC_IN_HOUR;

	static const unsigned long ONE_SEC_IN_US = 1000000;

	static const unsigned long RESOLUTION_MEASURE_TEMP_FREQ = ONE_SEC_IN_US;
	static const unsigned long RESOLUTION_MEASURE_PRESSURE_FREQ = ONE_SEC_IN_US;
	static const unsigned long RESOLUTION_MEASURE_LIGHT_FREQ = ONE_SEC_IN_US;
	static const unsigned long RESOLUTION_DISPLAY_DRAW_FREQ = ONE_SEC_IN_US;

	static const int ALTITUDE_EPROM_ADDR = 8;
	static const int STARTUP_SCREEN_EPROM_ADDR = ALTITUDE_EPROM_ADDR + sizeof(altitude);
	static const int MEASURE_TEMP_FREQ_EPROM_ADDR = STARTUP_SCREEN_EPROM_ADDR + sizeof(startupScreen);
	static const int MEASURE_PRESSURE_FREQ_EPROM_ADDR = MEASURE_TEMP_FREQ_EPROM_ADDR + sizeof(measureTempFreq);
	static const int MEASURE_LIGHT_FREQ_EPROM_ADDR = MEASURE_PRESSURE_FREQ_EPROM_ADDR + sizeof(measurePressureFreq);
	static const int DISPLAY_DRAW_FREQ_EPROM_ADDR = MEASURE_LIGHT_FREQ_EPROM_ADDR + sizeof(measureLightFreq);

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

	friend class ProgramMenu;

};

#endif /* PROGRAMSETTINGS_H_ */
