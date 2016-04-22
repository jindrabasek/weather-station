/*
 * ProgramMenu.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "ProgramMenu.h"

#include <Arduino.h>
#include <LCD.h>
#include <MenuValueHolder.h>
#include <OMMenuMgr.h>

#include "../ProgramSettings.h"
#include "../ProgramState.h"

MenuValueHolder<float> altitudeHolder;
MenuValueHolder<byte> startupScreenHolder;
MenuValueHolder<unsigned long> measureTempFreqHolder;
MenuValueHolder<unsigned long> measurePressureFreqHolder;
MenuValueHolder<unsigned long> measureLightFreqHolder;
MenuValueHolder<unsigned long> displayDrawFreqHolder;
MenuValueHolder<unsigned long> syncTimeFreqHolder;
MenuValueHolder<int> timeZoneHolder;

MenuValueHolder<MenuAction> measureTempFreqCallbackHolder;
MenuValueHolder<MenuAction> measurePressureFreqCallbackHolder;
MenuValueHolder<MenuAction> measureLightFreqCallbackHolder;
MenuValueHolder<MenuAction> displayDrawFreqCallbackHolder;
MenuValueHolder<MenuAction> syncTimeFreqCallbackHolder;

// Create a list of states and values for a select input
MENU_SELECT_ITEM  selTimeScreen = { ProgramState::TIME_SCREEN_NUMBER, {"Time and Date"} };
MENU_SELECT_ITEM  selTempScreen = { ProgramState::TEMP_SCREEN_NUMBER, {"Thermometer"} };
MENU_SELECT_ITEM  selPressureScreen = { ProgramState::PRESSURE_SCREEN_NUMBER, {"Barometer"} };
MENU_SELECT_ITEM  selLightScreen = { ProgramState::LIGHT_SCREEN_NUMBER, {"Light Intensity"} };

MENU_SELECT_LIST  selScreenslist[] = { &selTimeScreen, &selTempScreen, &selPressureScreen, &selLightScreen };

MENU_SELECT startupScreenSelect = { &startupScreenHolder,  MENU_SELECT_SIZE(selScreenslist),   MENU_TARGET(&selScreenslist) };

MENU_VALUE startupScreenValue = { TYPE_SELECT, 0, 0, MENU_TARGET(&startupScreenSelect), ProgramSettings::STARTUP_SCREEN_EPROM_ADDR };
MENU_ITEM startupScreen    = { {"Startup Screen"}, ITEM_VALUE,  0, MENU_TARGET(&startupScreenValue) };

MENU_VALUE_AND_ACTION measureTempFreqValueAction = {
		MENU_TARGET(&measureTempFreqHolder),
		MENU_TARGET(&measureTempFreqCallbackHolder)};
MENU_VALUE measureTempFreqValue = {
		TYPE_UINT,
		ProgramSettings::MAX_MEASURE_TEMP_FREQ,
		ProgramSettings::MIN_MEASURE_TEMP_FREQ,
		MENU_TARGET(&measureTempFreqValueAction),
		ProgramSettings::MEASURE_TEMP_FREQ_EPROM_ADDR };
MENU_ITEM measureTempFreq    = { {"Thermometer (s)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&measureTempFreqValue) };

MENU_VALUE_AND_ACTION measurePressureFreqValueAction = {
		MENU_TARGET(&measurePressureFreqHolder),
		MENU_TARGET(&measurePressureFreqCallbackHolder)};
MENU_VALUE measurePressureFreqValue = {
		TYPE_UINT,
		ProgramSettings::MAX_MEASURE_PRESSURE_FREQ,
		ProgramSettings::MIN_MEASURE_PRESSURE_FREQ,
		MENU_TARGET(&measurePressureFreqValueAction),
		ProgramSettings::MEASURE_PRESSURE_FREQ_EPROM_ADDR };
MENU_ITEM measurePressureFreq    = { {"Barometer (s)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&measurePressureFreqValue) };

MENU_VALUE_AND_ACTION measureLightFreqValueAction = {
		MENU_TARGET(&measureLightFreqHolder),
		MENU_TARGET(&measureLightFreqCallbackHolder)};
MENU_VALUE measureLightFreqValue = {
		TYPE_UINT,
		ProgramSettings::MAX_MEASURE_LIGHT_FREQ,
		ProgramSettings::MIN_MEASURE_LIGHT_FREQ,
		MENU_TARGET(&measureLightFreqValueAction),
		ProgramSettings::MEASURE_LIGHT_FREQ_EPROM_ADDR };
MENU_ITEM measureLightFreq    = { {"Light Intensity (s)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&measureLightFreqValue) };

MENU_LIST measureFreqencyList[]   = { &measureTempFreq, &measurePressureFreq, &measureLightFreq };
MENU_ITEM measureFreqency     = { {"Measure Frequency"}, ITEM_MENU, MENU_SIZE(measureFreqencyList), MENU_TARGET(&measureFreqencyList) };

MENU_VALUE_AND_ACTION displayDrawFreqValueAction = {
		MENU_TARGET(&displayDrawFreqHolder),
		MENU_TARGET(&displayDrawFreqCallbackHolder)};
MENU_VALUE displayDrawFreqValue = {
		TYPE_UINT,
		ProgramSettings::MAX_DISPLAY_DRAW_FREQ,
		ProgramSettings::MIN_DISPLAY_DRAW_FREQ,
		MENU_TARGET(&displayDrawFreqValueAction),
		ProgramSettings::DISPLAY_DRAW_FREQ_EPROM_ADDR };
MENU_ITEM displayDrawFreq    = { {"Disp draw freq (s)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&displayDrawFreqValue) };

MENU_LIST displaySettingsList[]   = { &displayDrawFreq };
MENU_ITEM displaySettings     = { {"Display Settings"}, ITEM_MENU, MENU_SIZE(displaySettingsList), MENU_TARGET(&displaySettingsList) };


MENU_VALUE altitudeValue = {
		TYPE_FLOAT_10,
		ProgramSettings::MAX_ALTITUDE,
		ProgramSettings::MIN_ALTITUDE,
		MENU_TARGET(&altitudeHolder),
		ProgramSettings::ALTITUDE_EPROM_ADDR };
MENU_ITEM altitude    = { {"Altitude (m)"}, ITEM_VALUE, 0, MENU_TARGET(&altitudeValue) };

MENU_LIST barometerSettingsList[]   = { &altitude };
MENU_ITEM barometerSettings     = { {"Barometer Settings"}, ITEM_MENU, MENU_SIZE(barometerSettingsList), MENU_TARGET(&barometerSettingsList) };


MENU_VALUE_AND_ACTION syncTimeFreqValueAction = {
        MENU_TARGET(&syncTimeFreqHolder),
        MENU_TARGET(&syncTimeFreqCallbackHolder)};
MENU_VALUE syncTimeFreqValue = {
        TYPE_UINT,
        ProgramSettings::MAX_SYNC_TIME_FREQ,
        ProgramSettings::MIN_SYNC_TIME_FREQ,
        MENU_TARGET(&syncTimeFreqValueAction),
        ProgramSettings::SYNC_TIME_FREQ_EPROM_ADDR };
MENU_ITEM syncTimeFreq    = { {"Sync time freq (h)"}, ITEM_VALUE_WITH_CALLBACK, 0, MENU_TARGET(&syncTimeFreqValue) };

MENU_VALUE timeZoneValue = {
        TYPE_INT,
        ProgramSettings::MAX_TIME_ZONE,
        ProgramSettings::MIN_TIME_ZONE,
        MENU_TARGET(&timeZoneHolder),
        ProgramSettings::TIME_ZONE_EPROM_ADDR };
MENU_ITEM timeZone    = { {"Time zone"}, ITEM_VALUE, 0, MENU_TARGET(&timeZoneValue) };

MENU_LIST timeSettingsList[]   = { &syncTimeFreq, &timeZone };
MENU_ITEM timeSettings     = { {"Time Settings"}, ITEM_MENU, MENU_SIZE(timeSettingsList), MENU_TARGET(&timeSettingsList) };


MENU_LIST root_list[]   = { &startupScreen, &measureFreqency, &displaySettings, &barometerSettings, &timeSettings };

MENU_ITEM menu_root     = { {"Root"}, ITEM_MENU, MENU_SIZE(root_list), MENU_TARGET(&root_list) };

ProgramMenu::ProgramMenu(LCD & lcd, ProgramState * state, ProgramSettings & settings) :
	lcd (lcd),
	menuScreen(buttonsCache, menu),
	enterMenuHandler(buttonsCache, menuScreen, buttonsBackup),
	menuDraw(lcd),
	menuExit(lcd, enterMenuHandler, buttonsBackup),
	setTempMeasureFreqAction(state->getMeasureTempTask(), settings.measureTempFreq),
	setPressureMeasureFreqAction(state->getMeasureAirPressureTask(), settings.measurePressureFreq),
	setLightMeasureFreqAction(state->getMeasureLightIntensityTask(), settings.measureLightFreq),
	setDisplayRedrawFreqAction(state->getDrawOnDisplayTask(), settings.displayDrawFreq),
	setTimeSyncFreqAction(state->getTimeSyncTask(), settings.syncTimeFreq),
	menu(&menu_root){

	altitudeHolder.setValuePtr(&settings.altitude);
	startupScreenHolder.setValuePtr(&settings.startupScreen);
	measureTempFreqHolder.setValuePtr(&settings.measureTempFreq);
	measurePressureFreqHolder.setValuePtr(&settings.measurePressureFreq);
	measureLightFreqHolder.setValuePtr(&settings.measureLightFreq);
	displayDrawFreqHolder.setValuePtr(&settings.displayDrawFreq);
	syncTimeFreqHolder.setValuePtr(&settings.syncTimeFreq);
	timeZoneHolder.setValuePtr(&settings.timeZone);

	measureTempFreqCallbackHolder.setValuePtr(&setTempMeasureFreqAction);
	measurePressureFreqCallbackHolder.setValuePtr(&setPressureMeasureFreqAction);
	measureLightFreqCallbackHolder.setValuePtr(&setLightMeasureFreqAction);
    displayDrawFreqCallbackHolder.setValuePtr(&setDisplayRedrawFreqAction);
    syncTimeFreqCallbackHolder.setValuePtr(&setTimeSyncFreqAction);
}
