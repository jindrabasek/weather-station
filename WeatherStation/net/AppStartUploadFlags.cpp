/*
 * AppStartUploadFlags.cpp
 *
 *  Created on: 31. 1. 2017
 *      Author: jindra
 */

#include "AppStartUploadFlags.h"

BitBool<WeatherStation::ReadingUploaderSize> WeatherStation::AppStartUploadFlags::startFlag;

void WeatherStation::AppStartUploadFlags::appStarted() {
	for (uint8_t i = 0; i < ReadingUploader::ReadingUploaderSize; i++) {
		startFlag[i] = true;
	}
}

void WeatherStation::AppStartUploadFlags::statusUploaded(
		ReadingUploader uploader) {
	startFlag[uploader] = false;
}

bool WeatherStation::AppStartUploadFlags::isFlag(ReadingUploader uploader) {
    return startFlag[uploader];
}

