// 1. 어떤 게임? 쿠키런과 같은 러닝액션게임
// 2. 게임의 요소를 데이터로 표현.(주인공, 플레이어블 캐릭터, 조작하는 대상)
//    구조체로 만들어라

// 키보드 입력을 받을건가? 화면의 이동을 구현할 것인가?
// 컨트롤 할 대상의 구조체
// 플레이어의 좌표(점프, 구멍에 빠짐, 슬라이드(나중에추가))
// 플레이어의 점수 현재점수(최고점수)

// 게임 목표 : 최대한 많은 점수를 얻어라.
// 목표를 방해하는 요인 : 장애물, 구멍

// 게임 설계 : Data Init() 1번만 - GameLoop() 계속 - GameEnd()

#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 scanf 등의 사용 경고를 무시하기 위해 필요

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // 콘솔 제어 및 Sleep 함수 사용
#include "Console.h"

// --- 구조체 정의 ---

typedef struct PlayerPos { // 플레이어의 좌표
    int x;
    int y;
} P_Pos;

typedef struct Score { // 플레이어의 최고 점수, 현재 점수
    int current;
    int max;
} Score;

typedef struct Jelly { // 점수를 획득하는 젤리 점수 및 젤리 형상 
    int point;          // 젤리 점수
    char jelly_char;    // 젤리 형상
    int is_active;      // 활성화 여부
    P_Pos pos;          // 젤리의 위치 추가
} Jelly;

typedef struct Player {
    P_Pos pos;
    Score score;
    int is_jumping;     // 점프 중인지 (0: No, 1: Yes), 점프여부
    int gravity;        // 점프/낙하 속도
    int base_y;         // 지면의 y 좌표
    int height;         // 플레이어의 높이 (충돌 판정용)
    int width;          // 플레이어의 너비 (충돌 판정용)
} Player;

typedef struct ObstaclePos { // 장애물의 위치
    int x;
    int y;
    int height;
} O_Pos;

typedef struct Obstacle {
    O_Pos pos;          // 오브젝트 위치
    int is_active;      // 활성화 여부
    int type;           // 0: 일반 장애물, 1: 구멍 (hole)
} Obstacle;

// --- 상수 및 전역 변수 설정 ---
#define SCREEN_WIDTH 70 // 스크린 크기
#define GROUND_Y 15     // 지면의 Y 좌표
#define MAX_OBJECTS 5   // 장애물, 젤리 최대 개수
#define JELLY_POINT 10  // 젤리한개의 포인트

Obstacle obstacles[MAX_OBJECTS]; // 장애물 최대 5개
Jelly jellies[MAX_OBJECTS];      // 젤리 최대 5개
int obstacle_tick = 0;
int jelly_tick = 0;
int game_speed = 1;     // X축 이동 속도 (점수에 따라 증가)
int game_delay_ms = 80; // 프레임 딜레이 (ms)



// --- 게임 초기화 및 객체 관리 함수 ---

void init_player(Player* p) {
    p->pos.x = 5;         // 플레이어의 X 좌표
    p->pos.y = GROUND_Y;  // 플레이어의 Y 좌표
    p->base_y = GROUND_Y; // 지면의 Y 좌표
    p->height = 2; // 플레이어의 콘솔 표현 높이 (점프 판정에 사용), 플레이어 캐릭터의 높이
    p->width = 2;  // 플레이어의 콘솔 표현 너비 (충돌 판정용), 플레이어 캐릭터의 넓이
    p->is_jumping = 0; // 점프중인지 아닌지 확인 0 : No 기본적으로 점프 안함
    p->gravity = 0;    // 점프, 낙하 속도. 점프중이 아니므로 0
    p->score.current = 0; // 초기 스코어 0
    p->score.max = 0; // 최고 점수는 파일 입출력을 통해 저장되어야 하지만, 여기서는 0으로 초기화
}

void init_objects() {
    int i;
    for (i = 0; i < MAX_OBJECTS; i++) {
        obstacles[i].is_active = 0;     // 장애물 활성화 여부 (초기 값이므로 0)
        jellies[i].is_active = 0;       // 젤리 활성화 여부 (초기 값이므로 0)
        jellies[i].point = JELLY_POINT; // 젤리 점수
        jellies[i].jelly_char = '@';    // 젤리가 어떻게 생겼는지 선언
    }
}

// 새 장애물 생성
void spawn_obstacle() {
    int i;
    for (i = 0; i < MAX_OBJECTS; i++) {
        if (obstacles[i].is_active == 0) {         // 장애물이 활성화 되어있지 않을 때
            obstacles[i].pos.x = SCREEN_WIDTH - 1; // 화면 오른쪽 끝
            obstacles[i].is_active = 1;            // 장애물 활성화

            // 40% 확률로 구멍, 60% 확률로 일반 장애물
            int type = rand() % 10;             // 0~9까지 정수 중에 무작위로 하나의 값을 선택
            if (type < 4) { // 구멍 (40%)   0~3은 구멍 생성
                obstacles[i].type = 1;         // 구멍의 type : 1
                obstacles[i].pos.y = GROUND_Y + 1; // 구멍이 있는 지면 아래로 설정
                obstacles[i].pos.height = 1; // 구멍의 깊이
            }
            else { // 일반 장애물 (60%)    4~9까지 일반 장애물 생성
                obstacles[i].type = 0;    // 장애물의 type : 0
                obstacles[i].pos.y = GROUND_Y; // 장애물의 Y 좌표는 지면으로 설정
                // 높이가 1 또는 2인 장애물
                obstacles[i].pos.height = rand() % 2 + 1; // 장애물의 높이 설정(1 or 2)
            }
            break;
        }
    }
}

// 새 젤리 생성
void spawn_jelly() {
    int i;
    for (i = 0; i < MAX_OBJECTS; i++) {
        if (jellies[i].is_active == 0) {
            jellies[i].pos.x = SCREEN_WIDTH - 1;
            // 젤리 높이는 지면(GROUND_Y)이나 공중(GROUND_Y - 1) 중 랜덤 설정
            jellies[i].pos.y = GROUND_Y - (rand() % 2);
            jellies[i].is_active = 1;
            break;
        }
    }
}

// --- 게임 로직 및 업데이트 함수 ---

// 플레이어 업데이트 (점프 및 중력)
void update_player(Player* p) {
    if (p->is_jumping) {
        p->pos.y -= p->gravity; // 중력만큼 y좌표 변경
        p->gravity--;          // 중력 가속도 적용

        if (p->pos.y >= p->base_y) {
            p->pos.y = p->base_y; // 지면에 착지
            p->is_jumping = 0;    // 점프 종료
            p->gravity = 0;       // 중력 초기화
        }
    }
}

// 객체 업데이트 (스크롤)
void update_objects() {
    int i;

    // 장애물 스크롤
    for (i = 0; i < MAX_OBJECTS; i++) {
        if (obstacles[i].is_active) {
            obstacles[i].pos.x -= game_speed;
            if (obstacles[i].pos.x < 0) {
                obstacles[i].is_active = 0;
            }
        }
    }

    // 젤리 스크롤
    for (i = 0; i < MAX_OBJECTS; i++) {
        if (jellies[i].is_active) {
            jellies[i].pos.x -= game_speed;
            if (jellies[i].pos.x < 0) {
                jellies[i].is_active = 0;
            }
        }
    }

    // 장애물/젤리 생성 타이머
    obstacle_tick++;
    jelly_tick++;

    // 장애물 생성 주기 (속도에 반비례)
    if (obstacle_tick > (30 / game_speed)) {
        spawn_obstacle();
        obstacle_tick = 0;
    }

    // 젤리 생성 주기 (속도에 반비례)
    if (jelly_tick > (15 / game_speed)) {
        spawn_jelly();
        jelly_tick = 0;
    }
}

// AABB 충돌 판정 (반환: 1 = 충돌/낙하, 0 = 안전)
int check_collision(Player* p) {
    int i;
    int p_left = p->pos.x;
    int p_right = p->pos.x + p->width - 1;
    int p_top = p->pos.y - p->height + 1;
    int p_bottom = p->pos.y;

    // 1. 장애물 충돌 및 구멍 낙하 판정
    for (i = 0; i < MAX_OBJECTS; i++) {
        if (obstacles[i].is_active) {
            int o_left = obstacles[i].pos.x;
            int o_right = obstacles[i].pos.x; // 장애물은 보통 1칸 너비
            int o_top = obstacles[i].pos.y - obstacles[i].pos.height + 1;
            int o_bottom = obstacles[i].pos.y;

            // X축 충돌
            if (p_right >= o_left && p_left <= o_right) {
                if (obstacles[i].type == 0) { // 일반 장애물 충돌
                    // Y축 충돌
                    if (p_bottom >= o_top && p_top <= o_bottom) {
                        return 1; // 충돌 발생
                    }
                }
                else if (obstacles[i].type == 1) { // 구멍 낙하 판정
                    // 플레이어의 바닥(p_bottom)이 지면(GROUND_Y)에 닿았는데 
                    // 장애물(구멍)의 위치(o_bottom)가 플레이어의 바닥과 같을 때 (즉, 구멍 위에 서 있을 때)
                    if (p_bottom == GROUND_Y && o_bottom == GROUND_Y + 1) {
                        // 구멍 영역에 플레이어의 발이 닿았다면 낙하로 간주
                        return 1;
                    }
                }
            }
        }
    }

    // 2. 젤리 획득 판정
    for (i = 0; i < MAX_OBJECTS; i++) {
        if (jellies[i].is_active) {
            // 젤리 위치
            int j_x = jellies[i].pos.x;
            int j_y = jellies[i].pos.y;

            // 젤리가 플레이어 범위 내에 있을 때 획득
            if (p_right >= j_x && p_left <= j_x) {
                if (p_bottom >= j_y && p_top <= j_y) {
                    p->score.current += jellies[i].point;
                    jellies[i].is_active = 0; // 젤리 획득 후 제거

                    // 점수 기반 속도 증가 체크 (100점마다)
                    if (p->score.current > 0 && p->score.current % 100 == 0) {
                        if (game_speed < 5) game_speed++;
                        if (game_delay_ms > 20) game_delay_ms -= 10;
                    }
                }
            }
        }
    }

    return 0; // 충돌 없음
}

// --- 화면 출력 함수 ---

void draw_game(Player* p) {
    int i, j;

    // 이전에 플레이어와 객체들이 있었던 위치를 지웁니다.
    // 이전 위치를 추적하여 지우는 것이 가장 좋으나, 간단하게 전체 맵 영역을 지웁니다.
    clear_area(0, 2, SCREEN_WIDTH, GROUND_Y);

    // 1. 상태 정보 출력 (상단 0, 1 라인)
    gotoxy(0, 0);
    printf("SCORE: %d | MAX SCORE: %d | SPEED: %d\n", p->score.current, p->score.max, game_speed);
    printf("----------------------------------------------------------------------\n");

    // 2. 플레이어 출력
    // 플레이어는 2칸 높이로 표현 (y, y-1)
    gotoxy(p->pos.x, p->pos.y);
    printf("PP"); // 플레이어의 하단
    gotoxy(p->pos.x, p->pos.y - 1);
    printf("@@"); // 플레이어의 상단

    // 3. 지면 출력 (GROUND_Y + 1 라인)
    gotoxy(0, GROUND_Y + 1);
    for (i = 0; i < SCREEN_WIDTH; i++) {
        printf("="); // 지면 라인
    }

    // 4. 장애물 및 구멍 출력
    for (i = 0; i < MAX_OBJECTS; i++) {
        if (obstacles[i].is_active && obstacles[i].pos.x < SCREEN_WIDTH) {
            if (obstacles[i].type == 0) { // 일반 장애물
                for (j = 0; j < obstacles[i].pos.height; j++) {
                    gotoxy(obstacles[i].pos.x, obstacles[i].pos.y - j);
                    printf("##"); // 장애물
                }
            }
            else if (obstacles[i].type == 1) { // 구멍
                // 구멍이 생성된 위치의 지면 "="을 지워서 구멍처럼 보이게 합니다.
                gotoxy(obstacles[i].pos.x, GROUND_Y + 1);
                printf("  ");
            }
        }
    }

    // 5. 젤리 출력
    for (i = 0; i < MAX_OBJECTS; i++) {
        if (jellies[i].is_active && jellies[i].pos.x < SCREEN_WIDTH) {
            gotoxy(jellies[i].pos.x, jellies[i].pos.y);
            printf("%c", jellies[i].jelly_char); // 젤리 캐릭터 (@)
        }
    }
}

// --- 메인 게임 루프 ---

void game_loop() {
    Player player;
    int is_running = 1;

    // 초기화
    init_player(&player);
    init_objects();
    hide_cursor();
    srand((unsigned int)time(NULL));

    // 게임 시작
    while (is_running) {

        // 1. 입력 처리 (논블로킹 입력)
        if (_kbhit()) {
            char key = _getch();
            // 스페이스바 (32) 또는 'w'를 누르면 점프
            if ((key == 32 || key == 'w' || key == 'W') && player.is_jumping == 0) {
                player.is_jumping = 1;
                player.gravity = 4; // 초기 점프 속도 설정
            }
        }

        // 2. 게임 로직 업데이트
        update_player(&player);
        update_objects();

        // 3. 충돌 및 점수 체크
        if (check_collision(&player) == 1) {
            is_running = 0; // 충돌 발생 시 게임 종료
        }

        // 4. 화면 출력
        draw_game(&player);

        // 5. 프레임 딜레이
        Sleep(game_delay_ms);
    }

    // 게임 종료 처리
    // 최고 점수 갱신
    if (player.score.current > player.score.max) {
        player.score.max = player.score.current;
    }

    // 게임 종료 화면 출력
    system("cls"); // 화면을 깨끗하게 지웁니다.
    gotoxy(SCREEN_WIDTH / 2 - 8, GROUND_Y / 2);
    printf("!!! G A M E   O V E R !!!\n");
    gotoxy(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 2);
    printf("CURRENT SCORE: %d\n", player.score.current);
    gotoxy(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 3);
    printf("BEST SCORE: %d\n", player.score.max);
    gotoxy(SCREEN_WIDTH / 2 - 10, GROUND_Y / 2 + 5);
    printf("Press any key to exit...");

    _getch(); // 종료 대기
}

int main() {
    game_loop();
    return 0;
}