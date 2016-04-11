/*
 * MenuButtonsCache.h
 *
 *  Created on: 4. 2. 2016
 *      Author: jindra
 */

#ifndef MENUBUTTONSCACHE_H_
#define MENUBUTTONSCACHE_H_

#include <OMMenuMgr.h>
#include <stdbool.h>
#include <stdint.h>

class MenuButtonsCache {
private:
    static const uint8_t MENU_KEY_STROKES_CACHE_SIZE = 10;

    volatile Button buttonsCache[MENU_KEY_STROKES_CACHE_SIZE];
    volatile uint8_t size;
    volatile uint8_t start;
    volatile uint8_t end;
public:
    MenuButtonsCache();

    void putPress(Button button);
    Button getPress();
    bool isEmpty();
    void clear();
};

#endif /* MENUBUTTONSCACHE_H_ */
