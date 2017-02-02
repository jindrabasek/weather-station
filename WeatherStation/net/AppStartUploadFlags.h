/*
 * AppStartUploadFlags.h
 *
 *  Created on: 31. 1. 2017
 *      Author: jindra
 */

#ifndef NET_APPSTARTUPLOADFLAGS_H_
#define NET_APPSTARTUPLOADFLAGS_H_

#include <BitBool.h>
#include <SensorIds.h>

namespace WeatherStation {
	class AppStartUploadFlags {
	public:
		static void appStarted();
		static void statusUploaded(ReadingUploader uploader);
		static bool isFlag(ReadingUploader uploader);
	private:
		static BitBool<ReadingUploaderSize> startFlag;

	};
}

#endif /* NET_APPSTARTUPLOADFLAGS_H_ */
