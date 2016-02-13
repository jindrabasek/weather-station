/*
 * ProgramSettings.h
 *
 *  Created on: 22. 1. 2016
 *      Author: jindra
 */

#ifndef PROGRAMSETTINGS_H_
#define PROGRAMSETTINGS_H_

class ProgramSettings {
private:
	float altitude;

public:
	ProgramSettings();
	ProgramSettings(const ProgramSettings& that) = delete;
	void operator=(const ProgramSettings& that) = delete;

	float getAltitude() const {
		return altitude;
	}

};

#endif /* PROGRAMSETTINGS_H_ */
