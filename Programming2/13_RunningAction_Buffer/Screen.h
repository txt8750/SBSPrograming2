#pragma once
#include <stdarg.h>

#define MAPHEIGHT 10

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenPrint(int x, int y, char* string);
void ScreenRelease();
void ScreenPrintf(int x, int y, const char* format, ...);