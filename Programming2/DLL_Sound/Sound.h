#pragma once

#ifndef SOUND
#define SOUND_API __declspec(dllexport)
#else
#define SOUND_API __declspec(dllexport)
#endif

extern "C" SOUND_API void PlayBGM();