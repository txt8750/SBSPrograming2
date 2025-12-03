#pragma once

#ifndef CONSOLE_MONSTER_H
#define CONSOLE_MONSTER_H

typedef struct Monster
{
	COLOR mon_color;
	COLOR bg_color;
	char shape[10];
}Monster;

void RenderMonster(const Monster* monster);

#endif