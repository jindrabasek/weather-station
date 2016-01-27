/*
 * temperatureMeasurement.cpp
 *
 *  Created on: 3. 1. 2016
 *      Author: jindra
 */

#include "TempReading.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>

#include "BaseFunctions.h"

//using namespace std;
// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.
//namespace std {
//ohserialstream cout(Serial);
//}


TempReading::TempReading(float humidity, float temperatureCelsius,
		float heatIndexCelsius) :
		humidity(humidity), temperatureCelsius(temperatureCelsius), heatIndexCelsius(
				heatIndexCelsius) {

	if (isnan(humidity) || isnan(temperatureCelsius)
			|| isnan(heatIndexCelsius)) {
		setMeasureState(MEASURE_ERROR);
	} else {
		setMeasureState(MEASURE_OK);
	}
}

TempReading::TempReading() :
		humidity(NAN), temperatureCelsius(NAN), heatIndexCelsius(
		NAN) {
}

void TempReading::printTo(Print & out, NewLiner & newLine) const {
	if (getMeasureState() == MEASURE_OK) {
		char buffer[13];
		newLine.newLine(1);
		out.print(F("Humidity:"));
		dtostrf(humidity, 9, 1, buffer);
		out.print(buffer);
		out.print(F(" %"));
		out.print(buffer);
		newLine.newLine(2);
		out.print(F("Temp:"));
		dtostrf(temperatureCelsius, 12, 2, buffer);
		out.print(buffer);
		out.print(F(" *C"));
		newLine.newLine(3);
		out.print(F("Heat index:"));
		dtostrf(heatIndexCelsius, 6, 2, buffer);
		out.print(buffer);
		out.print(F(" *C"));
	} else {
		for (byte i = 1; i < 4; i++) {
			newLine.newLine(i);
			out.print(F("                    "));
		}
		newLine.newLine(2);
		if (getMeasureState() == NOT_YET_MEASURED) {
			out.print(F("Temp not yet read."));

		} else {
			out.print(F("Error reading temp!"));
		}

	}
}



/*

 #include <iomanip>
 using namespace std;

 void TempMeasure::printToStream(ohserialstream & out) {
 if (measureOk) {
 out << F("Humidity: ") << setprecision(1) << humidity << F(" %");
 out << F(" \t | \t ");
 out << F("Temperature: ") << setprecision(2) << temperatureCelsius
 << F(" *C");
 out << F(" \t | \t ");
 out << F("Heat index: ") << setprecision(2) << heatIndexCelsius
 << F(" *C");
 out << endl;
 } else {
 out << F("Failed to read from temperature sensor!") << endl;
 }
 }*/

/*
 #include "TempMeasure.h"
 #include <avr/pgmspace.h>
 #include <iomanip>

 using namespace std;

 const char string_0[] PROGMEM = "Humidity: ";
 const char string_1[] PROGMEM = "Temp: ";
 const char string_2[] PROGMEM = "Heat index: ";
 const char string_3[] PROGMEM = " *C";
 const char string_4[] PROGMEM = " %";
 const char string_5[] PROGMEM = " \t | \t ";
 const char string_6[] PROGMEM = "Failed to read from temperature sensor!";

 const char* const string_table[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5, string_6};

 char * TempMeasure::inFlashMsg(int index){
 strcpy_P(buffer, (char*)pgm_read_word(&(string_table[index])));
 return buffer;
 }

 void TempMeasure::printToStream(ohserialstream & out) {
 if (measureOk) {
 out << inFlashMsg(0) << setprecision(1) << humidity << inFlashMsg(4);
 out << inFlashMsg(5);
 out << inFlashMsg(1) << setprecision(2) << temperatureCelsius
 << inFlashMsg(3);
 out << inFlashMsg(5);
 out << inFlashMsg(2) << setprecision(2) << heatIndexCelsius
 << inFlashMsg(3);
 out << endl;
 } else {
 out << inFlashMsg(6) << endl;
 }
 }

 void TempMeasure::printToDisplay(LiquidCrystal_I2C & out) {
 if (measureOk) {
 out.setCursor(0, 1);
 out.print(inFlashMsg(0));
 out.print(humidity, 1);
 out.print(inFlashMsg(4));
 out.setCursor(0, 2);
 out.print(inFlashMsg(1));
 out.print(temperatureCelsius, 2);
 out.print(inFlashMsg(3));
 out.setCursor(0, 3);
 out.print(inFlashMsg(2));
 out.print(heatIndexCelsius, 2);
 out.print(inFlashMsg(3));
 }
 }

 void TempReading::printTo(Print & out, NewLiner & newLine) const {
	if (measureState == MEASURE_OK) {
		newLine.newLine(1);
		out.print(F("Humidity: "));
		out.print(humidity, 1);
		out.print(F(" %"));
		newLine.newLine(2);
		out.print(F("Temp: "));
		out.print(temperatureCelsius, 2);
		out.print(F(" *C"));
		newLine.newLine(3);
		out.print(F("Heat index: "));
		out.print(heatIndexCelsius, 2);
		out.print(F(" *C"));
	} else {
		for (byte i = 1; i < 4; i++) {
			newLine.newLine(i);
		}
		newLine.newLine(2);
		if (measureState == NOT_YET_MEASURED) {
			out.print(F("Temp not yet read."));

		} else {
			out.print(F("Error reading temp!"));
		}

	}
}

 */

