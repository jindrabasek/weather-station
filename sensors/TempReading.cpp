/*
 * temperatureMeasurement.cpp
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#include "TempReading.h"

#include <math.h>
#include <Print.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <WString.h>

#include "SensorReading.h"
#include "Sensors.h"

TempReading::TempReading(float humidity, float humidityAbsolute,float temperatureCelsius,
                         float heatIndexCelsius, unsigned long timeStamp) :
        SensorReading(ReadState::READ_OK, timeStamp),
        humidity(humidity),
        humidityAbsolute(humidityAbsolute),
        temperatureCelsius(temperatureCelsius),
        heatIndexCelsius(heatIndexCelsius) {
}

TempReading::TempReading(bool error, unsigned long timeStamp) :
        SensorReading(error ? ReadState::READ_ERROR : ReadState::NOT_YET_READ, timeStamp),
        humidity(NAN),
        humidityAbsolute(NAN),
        temperatureCelsius(NAN),
        heatIndexCelsius(NAN) {
}

void TempReading::registerSensorValues(SensorReading** valueArray) {
    valueArray[WeatherStation::SensorValueId::DHT_HUMIDITY] = this;
    valueArray[WeatherStation::SensorValueId::DHT_TEMPERTAURE] = this;
    valueArray[WeatherStation::SensorValueId::DHT_TEMPERTAURE_REAL_FEEL] = this;
    valueArray[WeatherStation::SensorValueId::ABSOLUTE_HUMIDITY] = this;
}

uint8_t TempReading::printSensorName(Print & out) const
{
    return out.print(F("Thermometer"));
}

uint8_t TempReading::valuesCount() const {
    return TempHumiditySensorIdLocal::TempHumiditySensorIdLocalEnumSize;
}

void TempReading::printValue(uint8_t valueId, bool localId, Print& out,
                                    uint8_t maxLength) const {
    char buffer[maxLength + 1];
    buffer[0] = 0;

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_HUMIDITY,
            WeatherStation::SensorValueId::DHT_HUMIDITY,
            dtostrf(humidity, maxLength, 1, buffer));

    elseifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE,
            WeatherStation::SensorValueId::DHT_TEMPERTAURE,
            dtostrf(temperatureCelsius, maxLength, 2, buffer));

    elseifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL,
            WeatherStation::SensorValueId::DHT_TEMPERTAURE_REAL_FEEL,
            dtostrf(heatIndexCelsius, maxLength, 2, buffer));

    elseifIdMatchThenDo(TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY,
            WeatherStation::SensorValueId::ABSOLUTE_HUMIDITY,
            dtostrf(humidityAbsolute, maxLength, 1, buffer));

    out.print(buffer);

}

uint8_t TempReading::printValueName(uint8_t valueId, bool localId,
                                           Print& out) const {

    uint8_t length = 0;

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_HUMIDITY,
            WeatherStation::SensorValueId::DHT_HUMIDITY,
            length = out.print(F("Humidity")));

    elseifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE,
            WeatherStation::SensorValueId::DHT_TEMPERTAURE,
            length = out.print(F("Temp")));

    elseifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL,
            WeatherStation::SensorValueId::DHT_TEMPERTAURE_REAL_FEEL,
            length = out.print(F("Real feel")));

    elseifIdMatchThenDo(TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY,
            WeatherStation::SensorValueId::ABSOLUTE_HUMIDITY,
            length = out.print(F("Humidity abs")));

    return length;
}

WeatherStation::SensorValueUnit TempReading::valueUnit(
        uint8_t valueId, bool localId) const {

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_HUMIDITY,
            WeatherStation::SensorValueId::DHT_HUMIDITY,
            return WeatherStation::SensorValueUnit::PERCENT);

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE,
            WeatherStation::SensorValueId::DHT_TEMPERTAURE,
            return WeatherStation::SensorValueUnit::DEGREE_CELSIUS);

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL,
            WeatherStation::SensorValueId::DHT_TEMPERTAURE_REAL_FEEL,
            return WeatherStation::SensorValueUnit::DEGREE_CELSIUS);

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY,
            WeatherStation::SensorValueId::ABSOLUTE_HUMIDITY,
            return WeatherStation::SensorValueUnit::G_PER_CUBIC_METER);

    return WeatherStation::SensorValueUnit::N_A;
}
