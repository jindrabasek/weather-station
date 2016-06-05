/*
 * temperatureMeasurement.cpp
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#include <DHT.h>
#include <math.h>
#include <Print.h>
#include <sensors/SensorReading.h>
#include <sensors/SensorValueUnits.h>
#include <sensors/TempReading.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SensorIds.h>
#include <WString.h>
#include <defines.h>

TempReading::TempReading(WeatherStation::SensorValueId firstGlobalSensorId,
                         float humidity, float temperatureCelsius,
                         unsigned long timeStamp) :
        SensorReading(ReadState::READ_OK, timeStamp),
        firstGlobalSensorId((uint8_t)firstGlobalSensorId),
        humidity(humidity),
        humidityAbsolute(NAN),
        temperatureCelsius(temperatureCelsius),
        heatIndexCelsius(NAN) {

    if (!isnan(humidity) && !isnan(temperatureCelsius)) {
#ifdef DHT_HUMIDITY_CORRECTION
        this->humidity += (DHT_HUMIDITY_CORRECTION);
#endif
#ifdef DHT_TEMPERATURE_CORRECTION
        this->temperatureCelsius += (DHT_TEMPERATURE_CORRECTION);
#endif
        heatIndexCelsius = DHT::computeHeatIndex(this->temperatureCelsius, this->humidity);
        humidityAbsolute = DHT::computeAbsoluteHumidity(this->temperatureCelsius, this->humidity);
    }
}

TempReading::TempReading(WeatherStation::SensorValueId firstGlobalSensorId,
                         bool error, unsigned long timeStamp) :
        SensorReading(error ? ReadState::READ_ERROR : ReadState::NOT_YET_READ, timeStamp),
        firstGlobalSensorId((uint8_t)firstGlobalSensorId),
        humidity(NAN),
        humidityAbsolute(NAN),
        temperatureCelsius(NAN),
        heatIndexCelsius(NAN) {
}

void TempReading::registerSensorValues(SensorReading** valueArray) {
    valueArray[firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_HUMIDITY] = this;
    valueArray[firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE] = this;
    valueArray[firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL] = this;
    valueArray[firstGlobalSensorId + TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY] = this;
}

uint8_t TempReading::printSensorName(Print & out) const
{
    return out.print(F("Thermo ")) + out.print(firstGlobalSensorId);
}

uint8_t TempReading::valuesCount() const {
    return TempHumiditySensorIdLocal::TempHumiditySensorIdLocalEnumSize;
}

void TempReading::printValue(uint8_t valueId, bool localId, Print& out,
                                    uint8_t maxLength) const {
    char buffer[maxLength + 1];
    buffer[0] = 0;

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_HUMIDITY,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_HUMIDITY,
            dtostrf(humidity, maxLength, 1, buffer))

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE,
            dtostrf(temperatureCelsius, maxLength, 2, buffer));

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL,
            dtostrf(heatIndexCelsius, maxLength, 2, buffer));

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY,
            dtostrf(humidityAbsolute, maxLength, 1, buffer));

    out.print(buffer);

}

uint8_t TempReading::printValueName(uint8_t valueId, bool localId,
                                           Print& out) const {

    uint8_t length = 0;

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_HUMIDITY,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_HUMIDITY,
            length = out.print(F("Humidity")));

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE,
            length = out.print(F("Temp")));

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL,
            length = out.print(F("Real feel")));

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY,
            length = out.print(F("Humidity abs")));

    return length;
}

WeatherStation::SensorValueUnit TempReading::valueUnit(
        uint8_t valueId, bool localId) const {

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_HUMIDITY,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_HUMIDITY,
            return WeatherStation::SensorValueUnit::PERCENT);

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE,
            return WeatherStation::SensorValueUnit::DEGREE_CELSIUS);

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_DHT_TEMPERTAURE_REAL_FEEL,
            return WeatherStation::SensorValueUnit::DEGREE_CELSIUS);

    ifIdMatchThenDo(TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY,
            firstGlobalSensorId + TempHumiditySensorIdLocal::L_ABSOLUTE_HUMIDITY,
            return WeatherStation::SensorValueUnit::G_PER_CUBIC_METER);

    return WeatherStation::SensorValueUnit::N_A;
}
