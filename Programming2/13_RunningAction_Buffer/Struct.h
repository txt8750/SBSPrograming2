#include <Windows.h>
#pragma once

#ifndef STRUCT_H

#define STRUCT_H
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
    int behavior;       // 0 : 기본, 1 : 슬라이드
} Player;

typedef struct ObstaclePos { // 장애물의 위치
    int x;
    int y;
    int height;
} O_Pos;

typedef struct Obstacle {
    O_Pos pos;          // 오브젝트 위치
    int is_active;      // 활성화 여부
    //char shape[10][10];
} Obstacle;

#endif