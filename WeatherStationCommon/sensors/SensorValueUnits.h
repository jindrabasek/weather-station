/*
 * Sensors.h
 *
 *  Created on: 24. 4. 2016
 *      Author: jindra
 */

#ifndef SENSORVALUEUNITS_H_
#define SENSORVALUEUNITS_H_

#include <Print.h>
#include <stdint.h>

namespace WeatherStation {

    enum SensorValueUnit {
        N_A,
        DEGREE_CELSIUS,
        HECTOPASCAL,
        LIGHT_INTENSITY_LUX,
        PERCENT,
        G_PER_CUBIC_METER,
        SensorValueUnitsEnumSize,
    };

    class SensorValueUnits {
    public:
        static uint8_t sensorUnitNameLength(SensorValueUnit unitId);
        static void printSensorUnit(SensorValueUnit unitId, Print & out);
        static void getSensorUnit(char* buffer, SensorValueUnit unitId);

    };

} /* namespace WeatherStation */

#endif /* SENSORVALUEUNITS_H_ */
