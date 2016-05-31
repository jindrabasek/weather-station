/*
 * BaseFunctions.cpp
 *
 *  Created on: 28. 12. 2015
 *      Author: jindra
 */

#include "BaseFunctions.h"
//#include <stdio.h>
//#include <stdarg.h>

int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

/*void pntf(char * buf, int size, const __FlashStringHelper *fmt, ... ){
  va_list args;
  va_start (args, fmt);
#ifdef __AVR__
  vsnprintf_P(buf, size, (const char *)fmt, args); // progmem for AVR
#else
  vsnprintf(buf, size, (const char *)fmt, args); // for the rest of the world
#endif
  va_end(args);
}*/
