/*
 * ProgramMenu.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "ProgramMenu.h"

#include <LCD.h>
#include <MenuValueHolder.h>
#include <OMMenuMgr.h>
#include <stddef.h>

#include "../ProgramSettings.h"
#include "../ProgramState.h"

static MenuValueHolder<MenuAction> measureTempFreqCallbackHolder;
static MenuValueHolder<MenuAction> measurePressureFreqCallbackHolder;
#ifdef ENABLE_LIGHT_SENSOR
static MenuValueHolder<MenuAction> measureLightFreqCallbackHolder;
#endif
static MenuValueHolder<MenuAction> displayDrawFreqCallbackHolder;
static MenuValueHolder<MenuAction> syncTimeFreqCallbackHolder;
static MenuValueHolder<MenuAction> dataUploadFreqCallbackHolder;
static MenuValueHolder<MenuAction> wifiWatchdogFreqCallbackHolder;
static MenuValueHolder<MenuAction> wifiRestartCallbackHolder;

// Create a list of states and values for a select input
static MENU_SELECT_ITEM  selTimeScreen = { ProgramState::TIME_SCREEN_NUMBER, {"Time and Date"} };
static MENU_SELECT_ITEM  selTempScreen = { ProgramState::TEMP_SCREEN_NUMBER, {"Thermometer"} };
static MENU_SELECT_ITEM  selPressureScreen = { ProgramState::PRESSURE_SCREEN_NUMBER, {"Barometer"} };
#ifdef ENABLE_LIGHT_SENSOR
static MENU_SELECT_ITEM  selLightScreen = { ProgramState::LIGHT_SCREEN_NUMBER, {"Light Intensity"} };
#endif
#ifdef ENABLE_W433_SENSORS
static MENU_SELECT_ITEM  selTempOutdoorScreen = { ProgramState::TEMP_SCREEN_OUTDOOR_NUMBER, {"Thermo Outdoor"} };
static MENU_SELECT_ITEM  selLightOutdoorScreen = { ProgramState::LIGHT_SCREEN_OUTDOOR_NUMBER, {"Light Outdoor"} };
static MENU_SELECT_ITEM  selSencorWirelessScreen = { ProgramState::SENCOR_WIRELESS_SCREEN_NUMBER, {"Sencor Wireless"} };
#endif

static MENU_SELECT_LIST  selScreenslist[] = { &selTimeScreen, &selTempScreen, &selPressureScreen
#ifdef ENABLE_LIGHT_SENSOR
		, &selLightScreen
#endif
#ifdef ENABLE_W433_SENSORS
		, &selTempOutdoorScreen, &selLightOutdoorScreen, &selSencorWirelessScreen
#endif
};

static MENU_SELECT startupScreenSelect = { NULL,  MENU_SELECT_SIZE(selScreenslist),   MENU_TARGET(&selScreenslist) };

static MENU_VALUE startupScreenValue = { TYPE_SELECT, 0, 0, MENU_TARGET(&startupScreenSelect), ProgramSettings::STARTUP_SCREEN_EPROM_ADDR };
static MENU_ITEM startupScreen    = { {"Startup Screen"}, ITEM_VALUE,  0, MENU_TARGET(&startupScreenValue) };

static MENU_VALUE_AND_ACTION measureTempFreqValueAction = {
		NULL,
		MENU_TARGET(&measureTempFreqCallbackHolder)};
static MENU_VALUE measureTempFreqValue = {
		TYPE_UINT,
		ProgramSettings::MAX_MEASURE_TEMP_FREQ,
		ProgramSettings::MIN_MEASURE_TEMP_FREQ,
		MENU_TARGET(&measureTempFreqValueAction),
		ProgramSettings::MEASURE_TEMP_FREQ_EPROM_ADDR };
static MENU_ITEM measureTempFreq    = { {"Thermometer (s)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&measureTempFreqValue) };

static MENU_VALUE_AND_ACTION measurePressureFreqValueAction = {
        NULL,
		MENU_TARGET(&measurePressureFreqCallbackHolder)};
static MENU_VALUE measurePressureFreqValue = {
		TYPE_UINT,
		ProgramSettings::MAX_MEASURE_PRESSURE_FREQ,
		ProgramSettings::MIN_MEASURE_PRESSURE_FREQ,
		MENU_TARGET(&measurePressureFreqValueAction),
		ProgramSettings::MEASURE_PRESSURE_FREQ_EPROM_ADDR };
static MENU_ITEM measurePressureFreq    = { {"Barometer (s)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&measurePressureFreqValue) };

#ifdef ENABLE_LIGHT_SENSOR
static MENU_VALUE_AND_ACTION measureLightFreqValueAction = {
        NULL,
		MENU_TARGET(&measureLightFreqCallbackHolder)};
static MENU_VALUE measureLightFreqValue = {
		TYPE_UINT,
		ProgramSettings::MAX_MEASURE_LIGHT_FREQ,
		ProgramSettings::MIN_MEASURE_LIGHT_FREQ,
		MENU_TARGET(&measureLightFreqValueAction),
		ProgramSettings::MEASURE_LIGHT_FREQ_EPROM_ADDR };
static MENU_ITEM measureLightFreq    = { {"Light Intensity (s)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&measureLightFreqValue) };
#endif

static MENU_LIST measureFreqencyList[]   = { &measureTempFreq, &measurePressureFreq
#ifdef ENABLE_LIGHT_SENSOR
		, &measureLightFreq
#endif
};
static MENU_ITEM measureFreqency     = { {"Measure Frequency"}, ITEM_MENU, MENU_SIZE(measureFreqencyList), MENU_TARGET(&measureFreqencyList) };

static MENU_VALUE_AND_ACTION displayDrawFreqValueAction = {
        NULL,
		MENU_TARGET(&displayDrawFreqCallbackHolder)};
static MENU_VALUE displayDrawFreqValue = {
		TYPE_UINT,
		ProgramSettings::MAX_DISPLAY_DRAW_FREQ,
		ProgramSettings::MIN_DISPLAY_DRAW_FREQ,
		MENU_TARGET(&displayDrawFreqValueAction),
		ProgramSettings::DISPLAY_DRAW_FREQ_EPROM_ADDR };
static MENU_ITEM displayDrawFreq    = { {"Disp draw freq (s)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&displayDrawFreqValue) };

static MENU_LIST displaySettingsList[]   = { &displayDrawFreq };
static MENU_ITEM displaySettings     = { {"Display Settings"}, ITEM_MENU, MENU_SIZE(displaySettingsList), MENU_TARGET(&displaySettingsList) };


static MENU_VALUE altitudeValue = {
		TYPE_FLOAT_10,
		ProgramSettings::MAX_ALTITUDE,
		ProgramSettings::MIN_ALTITUDE,
		NULL,
		ProgramSettings::ALTITUDE_EPROM_ADDR };
static MENU_ITEM altitude    = { {"Altitude (m)"}, ITEM_VALUE, 0, MENU_TARGET(&altitudeValue) };

static MENU_LIST barometerSettingsList[]   = { &altitude };
static MENU_ITEM barometerSettings     = { {"Barometer Settings"}, ITEM_MENU, MENU_SIZE(barometerSettingsList), MENU_TARGET(&barometerSettingsList) };


static MENU_VALUE_AND_ACTION syncTimeFreqValueAction = {
        NULL,
        MENU_TARGET(&syncTimeFreqCallbackHolder)};
static MENU_VALUE syncTimeFreqValue = {
        TYPE_UINT,
        ProgramSettings::MAX_SYNC_TIME_FREQ,
        ProgramSettings::MIN_SYNC_TIME_FREQ,
        MENU_TARGET(&syncTimeFreqValueAction),
        ProgramSettings::SYNC_TIME_FREQ_EPROM_ADDR };
static MENU_ITEM syncTimeFreq    = { {"Sync time freq (h)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&syncTimeFreqValue) };

static MENU_VALUE timeZoneValue = {
        TYPE_INT,
        ProgramSettings::MAX_TIME_ZONE,
        ProgramSettings::MIN_TIME_ZONE,
        NULL,
        ProgramSettings::TIME_ZONE_EPROM_ADDR };
static MENU_ITEM timeZone    = { {"Time zone"}, ITEM_VALUE, 0, MENU_TARGET(&timeZoneValue) };

static MENU_LIST timeSettingsList[]   = { &syncTimeFreq, &timeZone };
static MENU_ITEM timeSettings     = { {"Time Settings"}, ITEM_MENU, MENU_SIZE(timeSettingsList), MENU_TARGET(&timeSettingsList) };


static MENU_VALUE_AND_ACTION dataUploadFreqValueAction = {
        NULL,
        MENU_TARGET(&dataUploadFreqCallbackHolder)};
static MENU_VALUE dataUploadFreqValue = {
        TYPE_UINT,
        ProgramSettings::MAX_DATA_UPLOAD_MIN_FREQ,
        ProgramSettings::MIN_DATA_UPLOAD_MIN_FREQ,
        MENU_TARGET(&dataUploadFreqValueAction),
        ProgramSettings::DATA_UPLOAD_MIN_EPROM_ADDR };
static MENU_ITEM dataUploadFreq    = { {"Upload freq (min)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&dataUploadFreqValue) };

static MENU_VALUE_AND_ACTION wifiWatchdogFreqValueAction = {
        NULL,
        MENU_TARGET(&wifiWatchdogFreqCallbackHolder)};
static MENU_VALUE wifiWatchdogFreqValue = {
        TYPE_UINT,
        ProgramSettings::MAX_WIFI_WATCHDOG_MIN_FREQ,
        ProgramSettings::MIN_WIFI_WATCHDOG_MIN_FREQ,
        MENU_TARGET(&wifiWatchdogFreqValueAction),
        ProgramSettings::WIFI_WATCHDOG_MIN_EPROM_ADDR };
static MENU_ITEM wifiWatchdogFreq    = { {"Watchdog freq (min)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&wifiWatchdogFreqValue) };

static MENU_ITEM restartWifi    = { {"Restart WiFi"}, ITEM_ACTION, 0, MENU_TARGET(&wifiRestartCallbackHolder) };

static MENU_LIST networkSettingsList[]   = { &dataUploadFreq, &wifiWatchdogFreq, &restartWifi };
static MENU_ITEM networkSettings     = { {"Network Settings"}, ITEM_MENU, MENU_SIZE(networkSettingsList), MENU_TARGET(&networkSettingsList) };


static MENU_LIST root_list[]   = { &startupScreen, &measureFreqency, &displaySettings, &barometerSettings, &timeSettings, &networkSettings };

static MENU_ITEM menu_root     = { {"Root"}, ITEM_MENU, MENU_SIZE(root_list), MENU_TARGET(&root_list) };

ProgramMenu::ProgramMenu(LCD & lcd, ProgramState * state) :
	lcd (lcd),
	menuScreen(*this),
	enterMenuHandler(*this),
	menuDraw(lcd),
	menuExit(*this),
        setTempMeasureFreqAction(state->getMeasureTempTask(),
                &ProgramSettings::getMeasureTempSecondFreq,
                ProgramSettings::SECOND_RESOLUTION_MEASURE_TEMP_FREQ),
        setPressureMeasureFreqAction(state->getMeasureAirPressureTask(),
                &ProgramSettings::getMeasurePressureSecondFreq,
                ProgramSettings::SECOND_RESOLUTION_MEASURE_PRESSURE_FREQ),
#ifdef ENABLE_LIGHT_SENSOR
        setLightMeasureFreqAction(state->getMeasureLightIntensityTask(),
                &ProgramSettings::getMeasureLightSecondFreq,
                ProgramSettings::SECOND_RESOLUTION_MEASURE_LIGHT_FREQ),
#endif
        setDisplayRedrawFreqAction(state->getDrawOnDisplayTask(),
                &ProgramSettings::getDisplayDrawSecondFreq,
                ProgramSettings::SECOND_RESOLUTION_DISPLAY_DRAW_FREQ),
        setTimeSyncFreqAction(state->getTimeSyncTask(),
                &ProgramSettings::getSyncTimeHourFreq),
#ifdef ENABLE_SMART_LIVING
        setDataUploadFreqAction(state->getDataUploadTask(),
                &ProgramSettings::getDataUploadMinutesFreq,
                ProgramSettings::SECOND_RESOLUTION_DATA_UPLOAD_MIN_FREQ),
#endif
        setWifiWatchdogFreqAction(state->getWifiWatchDogTask(),
                &ProgramSettings::getWifiWatchdogMinutesFreq,
                ProgramSettings::SECOND_RESOLUTION_WIFI_WATCHDOG_MIN_FREQ),
	menu(&menu_root){

	measureTempFreqCallbackHolder.setValuePtr(&setTempMeasureFreqAction);
	measurePressureFreqCallbackHolder.setValuePtr(&setPressureMeasureFreqAction);
#ifdef ENABLE_LIGHT_SENSOR
	measureLightFreqCallbackHolder.setValuePtr(&setLightMeasureFreqAction);
#endif
    displayDrawFreqCallbackHolder.setValuePtr(&setDisplayRedrawFreqAction);
    syncTimeFreqCallbackHolder.setValuePtr(&setTimeSyncFreqAction);
#ifdef ENABLE_SMART_LIVING
    dataUploadFreqCallbackHolder.setValuePtr(&setDataUploadFreqAction);
#endif
    wifiRestartCallbackHolder.setValuePtr(&restartWifiAction);
}
