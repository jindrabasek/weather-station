/*
 * SensorFlags.cpp
 *
 *  Created on: 31. 5. 2016
 *      Author: jindra
 */

#include <sensors/SensorFlags.h>
#include <stdbool.h>

#ifdef USE_SENSOR_FLAGS

#include <BitBool.h>
#include <SensorIds.h>

BitBool<WeatherStation::SensorValueId::SensorsEnumSize> WeatherStation::SensorFlags::sensorFlags[WeatherStation::ReadingUploader::ReadingUploaderSize] = {0};

void WeatherStation::SensorFlags::writeFlag(SensorValueId sensorId, bool value,
                                        ReadingUploader uploader) {
    if (uploader >= ReadingUploader::ReadingUploaderSize){
        for (uint8_t i = 0; i < ReadingUploader::ReadingUploaderSize; i++) {
            sensorFlags[i][sensorId] = value;
        }
    } else {
        sensorFlags[uploader][sensorId] = value;
    }
}

bool WeatherStation::SensorFlags::isFlag(SensorValueId sensorId,
                                     ReadingUploader uploader) {
    return sensorFlags[uploader][sensorId];
}


#endif
