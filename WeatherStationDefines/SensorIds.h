/*
 * SensorIds.h
 *
 *  Created on: 31. 5. 2016
 *      Author: jindra
 */

#ifndef SENSORIDS_H_
#define SENSORIDS_H_


namespace WeatherStation {

    enum SensorValueId {
        PRESSURE,
        PRESSURE_SEAL_LEVEL,
        BMP_TEMPERATURE,
        LIGHT_INTENSITY,
        DHT_HUMIDITY,
        DHT_TEMPERTAURE_REAL_FEEL,
        DHT_TEMPERTAURE,
        ABSOLUTE_HUMIDITY,
        WIRELESS_TEMPERTAURE_SWSTS_CH1,
        WIRELESS_TEMPERTAURE_SWSTS_CH2,
        WIRELESS_TEMPERTAURE_SWSTS_CH3,
        LIGHT_INTENSITY_OUTDOOR,
        DHT_HUMIDITY_OUTDOOR,
        DHT_TEMPERTAURE_REAL_FEEL_OUTDOOR,
        DHT_TEMPERTAURE_OUTDOOR,
        ABSOLUTE_HUMIDITY_OUTDOOR,
        SensorsEnumSize,
    };

    enum ReadingUploader {
        SMART_LIVING,
        ReadingUploaderSize,
    };

} /* namespace WeatherStation */



#endif /* SENSORIDS_H_ */
