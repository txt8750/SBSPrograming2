#define _CRT_SECURE_NO_WARNINGS
#include "Title.h"
#include "Console.h"
#include "Screen.h"
#include <stdio.h>
#include <Windows.h>



// 게임 시작 - 게임 종료 - 최고점수
void GameTitle()
{	
	int TitleCursor = 9;

	// 입력했을 때 Y 좌표가 변경 되어야 한다.
	while (1)
	{
		GoToXY(18, TitleCursor);
		SetDataYPosInput(&TitleCursor, 9, 13, 2);
		TitleRender(&TitleCursor);

	}

	

	// 텍스트 입력으로 진행하는 구조 (1)
	//printf("0 : 시작, 1 : 점수 확인, 2 : 게임 종료\n");
	//int a = 0;
	//scanf("%d", &a);
	// 숫자 0 1 2

	// 입력으로 이동하는 구조.
	

	_getch();
}

void TitleRender(int* y)
{

	ScreenClear();
	
	ScreenPrint(15, 1, " _____ _____ ____ _____  ____    _    __  __ _____ _");
	ScreenPrint(15, 2, "|_   _| ____/ ___|_   _|/ ___|  / \  |  \/  | ____| |");
	ScreenPrint(15, 3, "  | | |  _| \___ \ | | | |  _  / _ \ | |\/| |  _| | |");
	ScreenPrint(15, 4, "  | | | |___ ___) || | | |_| |/ ___ \| |  | | |___|_|");
	ScreenPrint(15, 5, "  |_| |_____|____/ |_|  \____/_/   \_\_|  | |_____(_)");
	ScreenPrint(21, 9, "Start");
	ScreenPrint(21, 11, "Score");
	ScreenPrint(21, 13, "Quit");
	ScreenPrint(18, *y, ">>");

	ScreenFlipping();

}


void SetDataYPosInput(int* y, int MINHEIGHT, int MAXHEIGHT, int interval)
{
	unsigned char input = 0; // 

	if (_kbhit()) // 키보드를 입력하면 True
	{
		input = _getch();

		if (input == 224 || input == 0)
		{
			input = _getch(); // 두 번째 문자 읽기
			switch (input) {
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
	}
}
