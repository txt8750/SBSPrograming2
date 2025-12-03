#include "console_color.h"
#include "console_monster.h"
#include <stdio.h>



void RenderMonster(const Monster* monster)
{
	SetColor(monster->mon_color, monster->bg_color);
	// 좌표 이동하는 코드
	printf("%s\n", monster->shape);
	ResetColor();
}