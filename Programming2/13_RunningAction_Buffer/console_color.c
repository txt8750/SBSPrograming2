#include <Windows.h>
#include "console_color.h"

void SetColor(HANDLE hConsole, COLOR text_color, COLOR bg_color)
{
	SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

void ResetColor(HANDLE hConsole)
{
	SetColor(hConsole, WHITE, BLACK);
}