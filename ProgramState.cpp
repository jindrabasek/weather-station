/*
 * ProgramState.cpp
 *
 *  Created on: 30. 1. 2016
 *      Author: jindra
 */

#include "ProgramState.h"


ProgramState& ProgramState::instance() {
	static ProgramState state;
	return state;
}
