// 포인터 공부 어떻게 하면 되나요?
// 1. 정의 -> 무엇인가? 왜 써야하는가?
// 2. & , int*,  *변수이름    각 연산자가 어떻게 쓰는가? 
// 3. 포인터와 배열의 관계
// 4. 포인터를 매개변수로 사용하는 함수를 만들어보세요.

// 배열구현까지 완료가 되셨다면. 같은 몬스터 N개 구현이 가능해졌다. -> 별피하기
// 별이 떨어지는데, 별마다 특징을 다르게 하고 싶다. -> 객체. 다른 특징을 보유하게 하고 싶다.?

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>
#include "Screen.h"
#include "Title.h"  // 11월 21일 타이틀 구현.
#include "Console.h"

typedef struct PlayerPos
{
	int x;
	int y;
}PlayerPos;

PlayerPos playerPos = { 0,0 }; // 전역변수의 플레이어의 위치를 공통으로 사용하겠다.

PlayerPos ePos = { 5,5 };	 // 구조체의 이름을 COORD 공용적인 이름으로 바꾸면 좋다.
PlayerPos ePos2 = { 5,10 };
void GoToXY(int x, int y);

bool IsGameOver;

void CollisionCheck(PlayerPos player, PlayerPos enemy)
{
	if (player.x == enemy.x && player.y == enemy.y)
	{
		IsGameOver = true;
		//_getch();
	}
}

// 외부에서 받아오는 코드 : 

void PlayerControl()
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
				// 플레이어의 현재 좌표를 -1 해주세요
				playerPos.y -= 1;
				break;
			case 80: // ↓
				// 플레이어의 현재 좌표를 +1 해주세요
				playerPos.y += 1;

				if (playerPos.y >= MAPHEIGHT)
				{
					playerPos.y = MAPHEIGHT;
				}

				break;
			case 75: // ←
				// 플레이어의 현재 좌표를 x-1 해주세요
				playerPos.x -= 1;
				break;
			case 77: // →
				// 플레이어의 현재 좌표를 x+1 해주세요
				playerPos.x += 1;
				break;
			}
		}
	}
}
void Update()
{
	// 플레이어 이외에 이동하는 코드
	ePos.x++;	 // 화면 밖으로 이동하면 문제가 발생한다. 데이터 로직상으로 막아보세요. 조건문
	ePos2.x++;
	if (ePos.x >= 30)
	{
		ePos.x = 0;
	}
	if (ePos2.x >= 30)
	{
		ePos2.x = 0;
	}
	//ePos.y

	// enemy와 플레이어가 충돌했는가?

	CollisionCheck(playerPos, ePos);
	CollisionCheck(playerPos, ePos2);

	Sleep(50);  
}

void Render()
{
	//system("cls");
	//GoToXY(playerPos.x, playerPos.y);
	//printf("@");
	ScreenClear();
	ScreenPrint(playerPos.x, playerPos.y, "@");
	ScreenPrint(ePos.x, ePos.y, "#");
	ScreenPrint(ePos2.x, ePos2.y, "#");
	ScreenFlipping();

}

bool Quit()
{
	// 게임이 종료될 조건을 Bool 반환하는 함수로 만들어서
	int input = 0;
	//scanf("%d", &input);
	if (IsGameOver)	 // 조건이 만족하면 종료하라.
	{		
		printf("  ____    _    __  __ _____    _____     _______ ____  \n");
		printf(" / ___|  / \\  |  \\/  | ____|  / _ \\ \\   / / ____|  _ \\ \n");
		printf("| |  _  / _ \\ | |\\/| |  _|   | | | \\ \\ / /|  _| | |_) |\n");
		printf("| |_| |/ ___ \\| |  | | |___  | |_| |\\ V / | |___|  _ < \n");
		printf(" \\____/_/   \\_\\_|  |_|_____|  \\___/  \\_/  |_____|_| \\_\\\n");


		return true;
	}
	else {
		return false;
	}
}

void Game()
{
	
}

// 1- 이동, 몬스터 이동, 화면 렌더링 + Screen Buffer
// 2- 타이틀 -> 타이틀 화면은 반복문 밖에
// 3- 상호작용(Interact)


int main()
{
	// 화면을 2개 만들어 주세요

	GameTitle();
	ScreenInit();


	while (1) // 게임 루프
	{
		// 로직
		//조작하는 함수 playerhandle playercontrol
		//Update (갱신하다)
		//렌더 (데이터 변경되면 그 것을 실행하라)	
		// 플레이어의 이동.	
		// 키보드 화살표 방향키로 이동하기.

		// 화살표 225  
		// PlayerControl 함수로 이동할 예정
		PlayerControl();
		Update();
		Render();
		if (Quit())
		{
			break;
		}
	}
}

// 개발 노트

// 플레이어의 조작을 해서 화면에 움직이게 구현함  (데이터) - (화면 출력)
// 버그 	   -> 플레이어가 이전에 있었던 위치가 계속해서 남아 있다. 
// 해야할일 -> 각 기능을 함수에 넣기
// system("cls") 화면을 없애도록 수정 -> 화면이 깜빡거리는 문제가 발생
// '화면버퍼' -  화면0 <-,  화면1<-  