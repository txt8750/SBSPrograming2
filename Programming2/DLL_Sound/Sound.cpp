#include "pch.h"
#include "Sound.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#define BGM "bgm.wav"

SOUND_API void PlayBGM()
{
    PlaySound(TEXT(BGM), 0, SND_ASYNC);
    printf("사운드 재생\n");
    _getch();
}
