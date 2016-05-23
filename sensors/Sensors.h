/*
 * Sensors.h
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <Print.h>
#include <stdint.h>

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
        SensorsEnumSize,
    };

    enum SensorValueUnit {
        N_A,
        DEGREE_CELSIUS,
        HECTOPASCAL,
        LIGHT_INTENSITY_LUX,
        PERCENT,
        G_PER_CUBIC_METER,
        SensorValueUnitsEnumSize,
    };

    class Sensors {
    public:

        static uint8_t sensorUnitNameLength(SensorValueUnit unitId);
        static void printSensorUnit(SensorValueUnit unitId, Print & out);

    };



} /* namespace WeatherStation */

#endif /* SENSORS_H_ */
