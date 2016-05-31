/*
 * SensorFlags.h
 *
 *  Created on: 31. 5. 2016
 *      Author: jindra
 */

#ifndef SENSORFLAGS_H_
#define SENSORFLAGS_H_

#include <defines.h>

#ifdef USE_SENSOR_FLAGS

#include <BitBool.h>
#include <stdbool.h>
#include <SensorIds.h>

namespace WeatherStation {

    class SensorFlags {
    private:
        static BitBool<SensorsEnumSize> sensorFlags[ReadingUploaderSize];

    public:
        static void writeFlag(SensorValueId sensorId, bool value, ReadingUploader uploader = ReadingUploaderSize);
        static bool isFlag(SensorValueId sensorId, ReadingUploader uploader);
    };

} /* namespace WeatherStation */

#endif

#endif /* SENSORFLAGS_H_ */
