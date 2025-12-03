#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "console_color.h"
#include <string.h>
#include "console_monster.h"
#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>


#pragma comment(lib, "winmm.lib")

#define BGM "bgm.wav"
#define BGM2 "bgm2.wav"

// 제목 색, 문자 색깔, 오브젝트 색깔, 배경 색깔
// 배경색이 항상 검정이다.

int main()
{
	PlaySound(TEXT(BGM), 0, SND_ASYNC);
	PlaySound(TEXT(BGM2), NULL, SND_FILENAME | SND_ASYNC);
	// PlaySound 함수 호출
	// 첫 번째 인자: 파일 이름
	// 두 번째 인자: NULL or 0(리소스로부터 불러오는 것이 아니므로)
	// 세 번째 인자: 옵션 플래그
	//   - SND_FILENAME: 첫 번째 인자가 파일 이름임을 명시
	//   - SND_SYNC: 사운드가 끝날 때까지 프로그램 실행을 대기
	//   - SND_ASYNC: 사운드를 백그라운드에서 재생하고 다음 코드를 즉시 실행
	Monster mo1;
	mo1.mon_color = BLUE;
	mo1.bg_color = BLACK;
	strcpy(mo1.shape, "$$");
	
	Monster mo2;
	mo2.mon_color = BLACK;
	mo2.bg_color = RED;
	strcpy(mo2.shape, "▣");

	RenderMonster(&mo1);
	RenderMonster(&mo2);

	printf("사운드 재생\n");
	_getch();
	
}