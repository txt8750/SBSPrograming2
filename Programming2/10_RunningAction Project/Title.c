#include "Title.h"
#include "Screen.h"
#include "Console.h"
#include <conio.h>
#include <stdio.h>
#include "GlobalConst.h"

void GameTitle(int* TitleCursor)
{
	int input = 0;

	// 입력했을 때 Y 좌표가 변경 되어야 한다.
	while (1)
	{
		gotoxy(18, *TitleCursor);
		TitleRender(TitleCursor);
		int temp = SetDataYPosInput(TitleCursor, 9, 13, 2);
		if (temp == 1)
		{
			break;
		}
	}
}

void TitleRender(int* titleCursor)
{

	ScreenClear();

	ScreenPrint(15, 1, " ____  _   _ _   _ _   _ ___ _   _  ____ _");
	ScreenPrint(15, 2, "|  _ \\| | | | \\ | | \\ | |_ _| \\ | |/ ___| |");
	ScreenPrint(15, 3, "| |_) | | | |  \\| |  \\| || ||  \\| | |  _| |");
	ScreenPrint(15, 4, "|  _ <| |_| | |\\  | |\\  || || |\\  | |_| |_|");
	ScreenPrint(15, 5, "|_| \\_\\\\___/|_| \\_|_| \\_|___|_| \\_|\\____(_)");
	ScreenPrint(21, 9, "Start");
	ScreenPrint(21, 11, "Score");
	ScreenPrint(21, 13, "Quit");
	ScreenPrint(18, *titleCursor, ">>");

	ScreenFlipping();

}


int SetDataYPosInput(int* y, int MINHEIGHT, int MAXHEIGHT, int interval)
{
	unsigned char input = 0; // 

	if (_kbhit()) // 키보드를 입력하면 True
	{
		input = _getch();

		if (input == 224 || input == 0)
		{
			input = _getch(); // 두 번째 문자 읽기
			switch (input)
			{
			case 72: // ↑
				// 플레이어의 현재 좌표를 -interval 해주세요
				*y -= interval;

				if (*y < MINHEIGHT)
				{
					*y = MAXHEIGHT;
				}
				break;
			case 80: // ↓
				// 플레이어의 현재 좌표를 +interval 해주세요
				*y += interval;

				if (*y > MAXHEIGHT)
				{
					*y = MINHEIGHT;
				}
				break;
			}
		}
		if (input == 13)
		{
				return 1;
		}
	}
}