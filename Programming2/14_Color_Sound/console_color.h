#pragma once

#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H

typedef enum ColorType {
	BLACK,  		//0
	DARKBLUE,		//1
	DARKGREEN,		//2
	DARKSKYBLUE,    //3
	DARKRED,  		//4
	DARKPUPLE,		//5
	DARKYELLOW,		//6
	GRAY,			//7
	DARKGRAY,		//8
	BLUE,			//9
	GREEN,			//10
	SKYBLUE,		//11
	RED,			//12
	PURPLE,			//13
	YELLOW,			//14
	WHITE			//15
} COLOR;

void SetColor(int text_color, int bg_color);
void ResetColor();

#endif