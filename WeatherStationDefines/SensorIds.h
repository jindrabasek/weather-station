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
#ifdef ENABLE_LIGHT_SENSOR
        LIGHT_INTENSITY,
#endif
        DHT_HUMIDITY,
        DHT_TEMPERTAURE_REAL_FEEL,
        DHT_TEMPERTAURE,
        ABSOLUTE_HUMIDITY,
#ifdef ENABLE_W433_SENSORS
		WIRELESS_TEMPERTAURE_SWSTS_CH1,
        WIRELESS_TEMPERTAURE_SWSTS_CH2,
        WIRELESS_TEMPERTAURE_SWSTS_CH3,
        LIGHT_INTENSITY_OUTDOOR,
        DHT_HUMIDITY_OUTDOOR,
        DHT_TEMPERTAURE_REAL_FEEL_OUTDOOR,
        DHT_TEMPERTAURE_OUTDOOR,
        ABSOLUTE_HUMIDITY_OUTDOOR,
#endif
        SensorsEnumSize,
    };

    enum ReadingUploader {
#ifdef ENABLE_SMART_LIVING
        SMART_LIVING,
#endif
        MQTT_LOCAL,
        ReadingUploaderSize,
    };

} /* namespace WeatherStation */



#endif /* SENSORIDS_H_ */
