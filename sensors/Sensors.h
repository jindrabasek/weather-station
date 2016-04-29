/*
 * Sensors.h
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#ifndef SENSORS_H_
#define SENSORS_H_

namespace WeatherStation {

    enum Sensors {
        PRESSURE,
        PRESSURE_SEAL_LEVEL,
        BMP_TEMPERATURE,
        LIGHT_INTENSITY,
        DHT_HUMIDITY,
        DHT_TEMPERTAURE_REAL_FEEL,
        DHT_TEMPERTAURE,
        sensorsEnumSize,
        PRINT_VALUE_STRING_LENGTH = 10
    };

} /* namespace WeatherStation */

#endif /* SENSORS_H_ */
