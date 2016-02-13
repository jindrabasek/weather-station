/*
 * MenuButtonsCache.cpp
 *
 *  Created on: 4. 2. 2016
 *      Author: jindra
 */

#include "MenuButtonsCache.h"

MenuButtonsCache::MenuButtonsCache() :
	size(0),
	start(0),
	end(0){
}

void MenuButtonsCache::putPress(Button button){
	if (size < MENU_KEY_STROKES_CACHE_SIZE) {
		buttonsCache[end];
		size++;
		end = (end + 1) % MENU_KEY_STROKES_CACHE_SIZE;
	}
}

Button MenuButtonsCache::getPress(){
	if (size == 0) {
		return Button::BUTTON_NONE;
	}

	Button result = buttonsCache[start];
	size--;
	start = (start + 1) % MENU_KEY_STROKES_CACHE_SIZE;
	return result;
}

bool MenuButtonsCache::isEmpty() {
	return size > 0;
}

void MenuButtonsCache::clear() {
	size = 0;
	start = 0;
	end = 0;
}
