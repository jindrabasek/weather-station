/*
 * ButtonsCache.h
 *
 *  Created on: 13. 2. 2016
 *      Author: jindra
 */

#ifndef BUTTONSBACKUP_H_
#define BUTTONSBACKUP_H_

#include <ButtonHandler.h>

class ButtonsBackup {
private:
	ButtonHandler * volatile leftButtonPrev;
	ButtonHandler * volatile rightButtonPrev;
	ButtonHandler * volatile upButtonPrev;
	ButtonHandler * volatile downButtonPrev;
	ButtonHandler * volatile enterButtonPrev;
	ButtonHandler * volatile escButtonPrev;
public:
	ButtonsBackup();
	void backupHandlers();
	void restoreHandlers();
};

#endif /* BUTTONSBACKUP_H_ */
