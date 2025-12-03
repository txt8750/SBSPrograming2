#include "Title.h"
#include "Screen.h"
#include "Console.h"
#include <conio.h>
#include <stdio.h>
#include "GlobalConst.h"
#include <stdbool.h>

void GameTitle(int* TitleCursor)
{
	int input = 0;

	// 입력했을 때 Y 좌표가 변경 되어야 한다.
	while (1)
	{
		int temp = SetDataYPosInput(TitleCursor, 9, 13, 2);
		TitleRender(TitleCursor);
		if (temp == 1)
		{
			break;
		}
	}
}

void TitleRender(int* TitleCursor)
{
	ScreenClear();
	//clear_area(0,0, SCREEN_WIDTH, SCREEN_WIDTH);
	//SetColor(1, 0);
	ScreenPrint(SCREEN_WIDTH / 2 - 10, 1, YELLOW, BLACK, "Let's");
	ScreenPrint(8, 2, SKYBLUE, BLACK, " ____  _   _ _   _ _   _ ___ _   _  ____ _");
	ScreenPrint(8, 3, SKYBLUE, BLACK, "|  _ \\| | | | \\ | | \\ | |_ _| \\ | |/ ___| |");
	ScreenPrint(8, 4, SKYBLUE, BLACK, "| |_) | | | |  \\| |  \\| || ||  \\| | |  _| |");
	ScreenPrint(8, 5, SKYBLUE, BLACK, "|  _ <| |_| | |\\  | |\\  || || |\\  | |_| |_|");
	ScreenPrint(8, 6, SKYBLUE, BLACK, "|_| \\_\\\\___/|_| \\_|_| \\_|___|_| \\_|\\____(_)");
	if (*TitleCursor == 9)
	{
		ScreenPrint(SCREEN_WIDTH /2 - 10, 9, RED, BLACK, "Start");
	}
	else
	{
		ScreenPrint(SCREEN_WIDTH / 2 - 10, 9, WHITE, BLACK, "Start");
	}

	if (*TitleCursor == 11)
	{
		ScreenPrint(SCREEN_WIDTH / 2 - 10, 11, RED, BLACK, "Score");
	}
	else
	{
		ScreenPrint(SCREEN_WIDTH / 2 - 10, 11, WHITE, BLACK, "Score");
	}

	if (*TitleCursor == 13)
	{
		ScreenPrint(SCREEN_WIDTH / 2 - 10, 13, RED, BLACK, "Quit");
	}
	else
	{
		ScreenPrint(SCREEN_WIDTH / 2 - 10, 13, WHITE, BLACK, "Quit");
	}
	ScreenPrint(SCREEN_WIDTH / 2 - 12, *TitleCursor, RED, BLACK, ">>");
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