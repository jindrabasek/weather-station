/*
 * PeripheryReading.h
 *
 *  Created on: 25. 1. 2016
 *      Author: jindra
 */

#ifndef PERIPHERYREADING_H_
#define PERIPHERYREADING_H_

enum ReadState {
	NOT_YET_READ, READ_OK, READ_ERROR
};

class PeripheryReading {
private:
	ReadState readState;

public:
	PeripheryReading(ReadState readState) : readState(readState){}
	virtual ~PeripheryReading(){}

	ReadState getReadState() const {
		return readState;
	}
};

#endif /* PERIPHERYREADING_H_ */
