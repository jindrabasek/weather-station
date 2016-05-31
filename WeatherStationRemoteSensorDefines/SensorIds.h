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
        LIGHT_INTENSITY,
        DHT_HUMIDITY,
        DHT_TEMPERTAURE_REAL_FEEL,
        DHT_TEMPERTAURE,
        ABSOLUTE_HUMIDITY,
        SensorsEnumSize,
    };

} /* namespace WeatherStation */



#endif /* SENSORIDS_H_ */
