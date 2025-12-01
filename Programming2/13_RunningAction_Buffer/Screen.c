#include "Screen.h"
#include <stdio.h>
#include <Windows.h>
#include "GlobalConst.h"
#include <stdarg.h>

#define BUFFER_SIZE 512

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

void ScreenInit()
{
    CONSOLE_CURSOR_INFO cci;

    //화면 버퍼 2개를 만든다.
    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
        0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
        0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    //커서 숨기기
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping()
{
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear()
{
    COORD Coor = { 0,0 };
    DWORD dw;
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', SCREEN_WIDTH * SCREEN_WIDTH, Coor, &dw);
}

void ScreenRelease()
{
    CloseHandle(g_hScreen[0]);
    CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, char* string)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
    WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

void ScreenPrintf(int x, int y, const char* format, ...)
{
    char temp_buffer[BUFFER_SIZE]; // 서식이 적용된 문자열을 저장할 임시 버퍼
    va_list args;                  // 가변 인자 목록을 위한 변수
    int len;                       // 서식 적용 후 문자열의 길이

    // 1. 가변 인자 목록 초기화
    va_start(args, format);

    // 2. 가변 인자를 사용하여 서식에 맞는 문자열을 임시 버퍼에 저장
    // snprintf는 버퍼 오버플로우를 방지하는 안전한 함수입니다.
    len = vsnprintf(temp_buffer, BUFFER_SIZE, format, args);

    // 3. 가변 인자 목록 정리
    va_end(args);

    // 4. 기존 ScreenPrint의 로직을 사용하여 버퍼에 출력

    // 현재 작업 중인 버퍼 인덱스 확인
    HANDLE hScreen = g_hScreen[g_nScreenIndex];

    COORD CursorPosition = { x, y };

    // 버퍼의 커서 위치 설정
    SetConsoleCursorPosition(hScreen, CursorPosition);

    // 서식이 적용된 문자열을 콘솔 버퍼에 쓰기
    DWORD dw;
    // len이 BUFFER_SIZE를 초과하지 않도록 min(len, BUFFER_SIZE - 1) 등을 사용할 수도 있지만, 
    // vsnprintf가 이미 안전하게 처리했으므로 len을 사용합니다.
    WriteFile(hScreen, temp_buffer, len, &dw, NULL);
}