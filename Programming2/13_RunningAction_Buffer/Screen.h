#pragma once
#include <stdarg.h>
#include "console_color.h"

#define MAPHEIGHT 10

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenPrint(int x, int y, COLOR text_color, COLOR bg_color, char* string);
void ScreenRelease();
void ScreenPrintf(int x, int y, COLOR text_color, COLOR bg_color, const char* format, ...);