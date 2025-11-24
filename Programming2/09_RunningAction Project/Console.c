#include <Windows.h>
#include <stdio.h>

// --- Windows API 콘솔 함수 ---

// 커서 이동 함수
void gotoxy(int x, int y) {
    COORD Pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 커서 숨기기
void hide_cursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 0, };
    cursor_info.dwSize = 1;
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 화면 지우기 함수 (재빠른 화면 갱신을 위해 특정 영역에 공백을 덮어쓰는 방식을 사용)
// 콘솔 깜빡임을 최소화하기 위해 'system("cls")' 대신 'gotoxy'를 활용합니다.
void clear_area(int x1, int y1, int x2, int y2) {
    int x, y;
    for (y = y1; y <= y2; y++) {
        gotoxy(x1, y);
        for (x = x1; x <= x2; x++) {
            printf(" ");
        }
    }
}