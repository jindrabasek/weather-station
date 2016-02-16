/*
 * ProgramMenu.cpp
 *
 *  Created on: 3. 2. 2016
 *      Author: jindra
 */

#include "ProgramMenu.h"


byte foo = 0;
byte sel = 0;
unsigned int bar = 1;
long baz  = 0;
float bak = 0.0;

  // Create a list of states and values for a select input
MENU_SELECT_ITEM  sel_ign = { 2, {"Ignore"} };
MENU_SELECT_ITEM  sel_on  = { 1, {"On"} };
MENU_SELECT_ITEM  sel_off = { 0, {"Off"} };

MENU_SELECT_LIST  state_list[] = { &sel_ign, &sel_on, &sel_off };

  // the special target for our state input

                             // TARGET VAR   LENGTH                          TARGET SELECT LIST
MENU_SELECT state_select = { &sel,           MENU_SELECT_SIZE(state_list),   MENU_TARGET(&state_list) };

  // values to use

                    //    TYPE            MAX    MIN    TARGET
MENU_VALUE foo_value = { TYPE_BYTE,       100,   0,     MENU_TARGET(&foo), 0 };
MENU_VALUE bar_value = { TYPE_UINT,       10000, 100,   MENU_TARGET(&bar), 0 };
MENU_VALUE baz_value = { TYPE_LONG,       10000, 1,     MENU_TARGET(&baz), 0 };
MENU_VALUE bak_value = { TYPE_FLOAT_1000, 0,     0,     MENU_TARGET(&bak), 0 };
MENU_VALUE sel_value = { TYPE_SELECT,     0,     0,     MENU_TARGET(&state_select), 0 };

                    //        LABEL           TYPE        LENGTH    TARGET
MENU_ITEM item_checkme  = { {"Byte Edit"},    ITEM_VALUE,  0,        MENU_TARGET(&foo_value) };
MENU_ITEM item_barme    = { {"UInt Edit"},    ITEM_VALUE,  0,        MENU_TARGET(&bar_value) };
MENU_ITEM item_bazme    = { {"Long Edit"},    ITEM_VALUE,  0,        MENU_TARGET(&baz_value) };
MENU_ITEM item_bakme    = { {"Float Edit"},   ITEM_VALUE,  0,        MENU_TARGET(&bak_value) };
MENU_ITEM item_state    = { {"Select Input"}, ITEM_VALUE,  0,        MENU_TARGET(&sel_value) };

                   //        List of items in menu level
MENU_LIST root_list[]   = { &item_checkme, &item_barme, &item_bazme, &item_bakme, &item_state };

                  // Root item is always created last, so we can add all other items to it
MENU_ITEM menu_root     = { {"Root"},        ITEM_MENU,   MENU_SIZE(root_list),    MENU_TARGET(&root_list) };

ProgramMenu::ProgramMenu(LCD & lcd) :
	lcd (lcd),
	menuScreen(buttonsCache, menu),
	enterMenuHandler(buttonsCache, menuScreen, buttonsBackup),
	menuDraw(lcd),
	menuExit(lcd, enterMenuHandler, buttonsBackup),
	menu(&menu_root){

}
