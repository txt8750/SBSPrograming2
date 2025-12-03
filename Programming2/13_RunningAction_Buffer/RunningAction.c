#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 scanf 등의 사용 경고를 무시하기 위해 필요

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // 콘솔 제어 및 Sleep 함수 사용
#include <conio.h>
#include "Console.h" // 콘솔 제어 함수 생성
#include "Screen.h"
#include "Struct.h" // 구조체 생성
#include "Objects_init.h"
#include "GlobalConst.h"
#include "Title.h"
#include "ScoreSaveLoad.h"
#include <stdbool.h>

Obstacle obstacles[MAX_OBSTACLE]; // 장애물 최대 개수. 배열
Jelly jellies[MAX_JELLY]; // 젤리 최대개수. 배열

int obstacle_tick = 0;
int jelly_tick = 0;
int game_speed = 1; // X축 이동속도(점수에 따라 증가)
int game_delay_ms = 50; // 프레임 딜레이(ms)

// 플레이어 업데이트 함수(점프 및 중력)
void Player_update(Player* player)
{
	if (player->is_jumping) // 플레이어가 점프를 한 경우
	{
		// 플레이어가 점프하면 플레이어의 Y포지션을 플레이어의 점프 속도만큼 변경
		player->pos.y -= player->gravity;
		player->gravity--; // 중력 가속도 적용
		if (player->pos.y >= player->base_y) //플레이거의 Y축 위치가 지면보다 높은 경우
		{
			player->pos.y = player->base_y; // 플레이어를 지면에 착지하게 만든다.
			player->is_jumping = 0; // 점프하지 않은 상태로 만듦
			player->gravity = 0; // 중력 초기화
		}
	}
}

// 새 장애물 생성
void Obstacle_spawn()
{
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (obstacles[i].is_active == 0)
		{
			obstacles[i].pos.x = SCREEN_WIDTH - 1;
			obstacles[i].is_active = 1;
		}

		obstacles[i].pos.y = GROUND_Y;
		obstacles[i].pos.height = rand() % 2 + 1;
		break;
	}
}

// 새 젤리 생성
void Jelly_spawn()
{
	for (int i = 0; i < MAX_JELLY; i++)
	{
		if (jellies[i].is_active == 0)
		{
			jellies[i].pos.x = SCREEN_WIDTH - 1;
			jellies[i].pos.y = GROUND_Y - (rand() % 2); // 젤리의 Y축 설정(랜덤). 지면이나 공중
			jellies[i].is_active = 1;
			break;
		}
	}
}


// 장애물, 젤리 업데이트
void Objects_update()
{
	for (int i = 0; i < MAX_OBSTACLE; i++) // 오브젝트 최대 개수 까지 반복한다.
	{
		if (obstacles[i].is_active) // 장애물이 활성화 되어있는 상태
		{
			obstacles[i].pos.x -= game_speed; // 장애물의 x축 위치를 왼쪽으로 옮김(game speed 만큼)
			if (obstacles[i].pos.x < 0) // 장애물의 x축 좌표가 0미만(스크린 왼쪽 바깥으로 나가면)이면
			{
				obstacles[i].is_active = 0; // 장애물을 비활성화 한다.
			}
		}
	}

	for (int i = 0; i < MAX_JELLY; i++) // 장애물 업데이트와 동일한 내용
	{
		if (jellies[i].is_active)
		{
			jellies[i].pos.x -= game_speed;
			if (jellies[i].pos.x < 0)
			{
				jellies[i].is_active = 0;
			}
		}
	}

	// 장애물/젤리 생성 타이머
	obstacle_tick++;
	jelly_tick++;

	// 장애물 생성 주기
	if (obstacle_tick > (30 / game_speed))
	{
		Obstacle_spawn();
		obstacle_tick = 0;
	}
	// 젤리 생성 주기
	if (jelly_tick > (15 / game_speed))
	{
		Jelly_spawn();
		jelly_tick = 0;
	}
}

// 화면 출력 함수
void Show_Game(Player* player)
{
	//clear_area(0,0, SCREEN_WIDTH, SCREEN_WIDTH);
	ScreenClear();
	// 상태 정보 출력 (상단 Y축 0,1 라인)
	ScreenPrintf(0,0, YELLOW, BLACK, "SCORE : %d / MAX SCORE : %d / SPEED : %d\n", player->score.current, player->score.max, game_speed);
	ScreenPrintf(0,1, YELLOW, BLACK, "======================================================================\n");

	// 플레이어 출력
	//gotoxy(player->pos.x, player->pos.y - 1);
	ScreenPrint(player->pos.x, player->pos.y - 1, BLUE, BLACK, "@@");
	//gotoxy(player->pos.x, player->pos.y);
	ScreenPrint(player->pos.x, player->pos.y, BLUE, BLACK, "PP");;

	// 지면 출력
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		ScreenPrint(i, GROUND_Y + 1, YELLOW, BLACK, "-");
	}

	// 장애물 출력
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (obstacles[i].is_active && obstacles[i].pos.x < SCREEN_WIDTH)
		{
			for (int j = 0; j < obstacles[i].pos.height; j++)
			{
				//gotoxy(obstacles[i].pos.x, obstacles[i].pos.y - j);
				ScreenPrint(obstacles[i].pos.x, obstacles[i].pos.y - j, RED, BLACK, "##");
			}
		}
	}

	//젤리 출력
	for (int i = 0; i < MAX_JELLY; i++)
	{
		if (jellies[i].is_active && jellies[i].pos.x < SCREEN_WIDTH)
		{
			//gotoxy(jellies[i].pos.x, jellies[i].pos.y);
			ScreenPrintf(jellies[i].pos.x, jellies[i].pos.y, DARKYELLOW, BLACK, "%c", jellies[i].jelly_char);
		}
			
	}
	ScreenFlipping();
}

// 플레이어 충돌 판정
int Check_Collision(Player* player)
{
	int p_left = player->pos.x; // 플레이어의 왼쪽 충돌 범위
	int p_right = player->pos.x + player->width - 1; // 플레이어의 오른쪽 충돌 범위
	int p_bottom = player->pos.y;  // 플레이어의 아래쪽 충돌 범위
	int p_top = player->pos.y - player->height + 1; // 플레이어의 위쪽 충돌 범위

	// 장애물 충돌 판정
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (obstacles[i].is_active)
		{
			int o_left = obstacles[i].pos.x;
			int o_right = obstacles[i].pos.x; // 장애물의 넓이는 한칸으로 고정
			int o_bottom = obstacles[i].pos.y;
			int o_top = obstacles[i].pos.y - obstacles[i].pos.height + 1;

			// --- [수정] 스윕 테스트 (Sweep Test) 적용 ---
			// 장애물의 이전 프레임 위치를 계산하여 충돌 경로를 확장합니다.
			// 현재 장애물은 왼쪽으로 이동하므로 이전 위치는 현재 X좌표 + game_speed 입니다.
			int o_prev_right = obstacles[i].pos.x + game_speed;


			// X축 충돌 판정
			if (p_right >= o_left && p_left <= o_prev_right)
			{
				if (p_bottom >= o_top && p_top <= o_bottom)
				{
					return 1; // 충돌발생
				}
			}
		}
	}
	// 젤리 획득 판정
	for (int i = 0; i < MAX_JELLY; i++)
	{
		if (jellies[i].is_active == 1)
		{
			int j_x = jellies[i].pos.x;
			int j_y = jellies[i].pos.y;

			// --- [수정] 스윕 테스트 (Sweep Test) 적용 ---
			// 젤리의 이전 프레임 위치를 계산하여 획득 경로를 확장합니다.
			int j_prev_x = jellies[i].pos.x + game_speed;

			if (p_right >= j_x && p_left <= j_prev_x)
			{
				if (p_bottom >= j_y && p_top <= j_y)
				{
					player->score.current += jellies[i].point;
					jellies[i].is_active = 0;
					if (player->score.current > 0 && player->score.current % 100 == 0)
					{
						if (game_speed < 5) game_speed++;  //게임의 최대속도는 5
						if (game_delay_ms > 20) game_delay_ms -= 10; // 속도가 증가할때마다 딜레이를 줄인다. 최소 20
					}
				}
			}
		}
	}
	return 0; // 충돌 없음
}

// 게임 종료 시 출력 함수
void GameOver(const Player* player)
{
	while (1)
	{
	// 게임 종료 처리
		ScreenClear(); // 화면 지우기
		//gotoxy(SCREEN_WIDTH / 2 - 8, GROUND_Y / 2);
		ScreenPrint(SCREEN_WIDTH / 2 - 8, GROUND_Y / 2, RED, BLACK, "G A M E  O V E R\n");
		//gotoxy(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 2);
		ScreenPrintf(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 2, WHITE, BLACK, "CURRENT SCORE : ", player->score.current);
		ScreenPrintf(SCREEN_WIDTH / 2 + 6, GROUND_Y / 2 + 2, SKYBLUE, BLACK, "%d", player->score.current);
		//gotoxy(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 4);
		ScreenPrintf(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 4, WHITE, BLACK, "BEST SCORE : ", player->score.max);
		ScreenPrintf(SCREEN_WIDTH / 2 + 3, GROUND_Y / 2 + 4, SKYBLUE, BLACK, "%d", player->score.max);
		//gotoxy(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 6);
		ScreenPrint(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 6, WHITE, BLACK, "Press");
		ScreenPrint(SCREEN_WIDTH / 2 - 4, GROUND_Y / 2 + 6, YELLOW, BLACK, "Enter");
		ScreenPrint(SCREEN_WIDTH / 2 + 2, GROUND_Y / 2 + 6, WHITE, BLACK, "key to exit...");
		ScreenFlipping();
		if (_kbhit())
		{
			char key = _getch(); // 입력을 받겠다.
			if (key == 13)
			{
				break;
			}
		}
	}
}

// 게임 실행 함수
void GameLoop(Player* player)
{
	int is_running = 1;
	while (is_running)
	{
		// 화면 출력
		Show_Game(player);

		int game_over = 0;
		if (_kbhit())
		{
			char key = _getch(); // 입력을 받겠다.
			if (key == 32 && player->is_jumping == 0)
			{
				player->is_jumping = 1;
				player->gravity = 3; // 초기 점프속도 설정(점프 높이)
			}
			if (key == 'Q' || key == 'q')
			{
				// current score가 max score보다 높은 경우 파일에 max score 갱신
				if (player->score.max < player->score.current)
				{
					player->score.max = player->score.current;
					SaveScore(player);
				}
				GameOver(player);
				break;
			}
		}

		// 게임 로직 업데이트		Player_update(player);
		Player_update(player);
		Objects_update();
		game_over = Check_Collision(player);

		// 화면 출력
		//Show_Game(player);

		// 프레임 딜레이
		Sleep(game_delay_ms);

		if (game_over)
		{
			if (player->score.max < player->score.current)
			{
				player->score.max = player->score.current;
				SaveScore(player);
			}
			GameOver(player);
			break;
		}
	}
}

// 스코어 확인 페이지 함수
void GameScore(const Player* player)
{
		ScreenClear();
		//gotoxy(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 4);
		ScreenPrintf(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 4, WHITE, BLACK, "BEST SCORE : \n", player->score.max);
		ScreenPrintf(SCREEN_WIDTH / 2 + 3, GROUND_Y / 2 + 4, SKYBLUE, BLACK, "%d", player->score.max);
		//gotoxy(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 6);
		ScreenPrint(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 6, WHITE, BLACK, "Press Q key to exit...");
		ScreenPrint(SCREEN_WIDTH / 2 - 4, GROUND_Y / 2 + 6, YELLOW, BLACK, "Q key to exit...");
		ScreenPrint(SCREEN_WIDTH / 2 - 2, GROUND_Y / 2 + 6, WHITE, BLACK, "key to exit...");
		ScreenFlipping();
		char key = _getch(); // 입력을 받겠다.
		if (key == 'Q' || key == 'q')
		{
			return;
		}
}



int main()
{
	Player player;
	// 초기화
	
	ScreenInit();
	player = Player_init(); // 플레이어 정보 초기화 (세이브 정보 로드)
	hide_cursor();


	int TitleCursor = 9;

	while (1)
	{
		Obstacle_init(); // 장애물 정보 초기화
		Jelly_init(); // 젤리 정보 초기화
		srand((unsigned int)time(NULL)); // 랜덤함수 초기화
		GameTitle(&TitleCursor);
		if (TitleCursor == 9)
		{
			game_speed = 1;
			player.score.current = 0;
			GameLoop(&player);
		}
		else if (TitleCursor == 11)
		{
			GameScore(&player);
		}
		else if (TitleCursor == 13)
		{
			break;
		}
		
	}
	return 0;
}
