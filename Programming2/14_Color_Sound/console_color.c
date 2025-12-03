#include <Windows.h>
#include "console_color.h"

void SetColor(COLOR text_color, COLOR bg_color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

void ResetColor()
{
	SetColor(WHITE, BLACK);
}