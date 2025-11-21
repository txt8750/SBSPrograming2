#include "Console.h"
#include <Windows.h>


// Player좌표 구조체. x값과 y값을 수정할 수 있게 만들어보세요.
void GoToXY(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


