#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define 몬스터대사의최대수 3

// 구조체 선언
typedef struct Pos
{
	int x;
	int y;
}Pos;

typedef struct Monster
{
	char* name[100];		// 몬스터의 이름
	char* dialogue[몬스터대사의최대수][100];  // 몬스터가 말하는 대사. 첫 조우 대사 -> 대사를 번호에다가 저장 1번 대사, 2번 대사, 3번 대사 ...
	Pos pos;
}Monster;

typedef enum Location
{
	강,숲,산,동굴,사막,눈,들판
}Location;
// 배열

// 포인터

// 모든 몬스터가 같이 사용하는 함수, 몬스터 정보, 장소

// MonsterEncount 실행시
// 몬스터의 이름, 장소, 대사가 나와야 함.
void LocMatch(Location loc, char* Loctemp)
{
	switch (loc)
	{
	case 강:
		strcpy(Loctemp, "강");
		break;
	case 숲:
		strcpy(Loctemp, "숲");
		break;
	case 산:
		strcpy(Loctemp, "산");
		break;
	case 동굴:
		strcpy(Loctemp, "동굴");
		break;
	case 사막:
		strcpy(Loctemp, "사막");
		break;
	case 눈:
		strcpy(Loctemp, "눈");
		break;
	case 들판:
		strcpy(Loctemp, "들판");
		break;
	default:
		printf("지정되지 않은 지역입니다.");
		return;

	}
}

void MonsterTalking(Monster* mon1, Monster* mon2)
{
	for (int index = 0; index < 몬스터대사의최대수; index++)
	{
		printf("%s : %s\n", mon1->name, mon1->dialogue[index]);
		Sleep(1000);
		printf("%s : %s\n", mon2->name, mon2->dialogue[index]);
		printf("\n");
		Sleep(1000);
	}
}

void MonsterEncount(Monster* monster, Monster* other, Location loc)
{
	if (monster->pos.x != other->pos.y && monster->pos.x != other->pos.y) // 몬스터가 누군가와 조우했을 때만 실행해야 한다.
	{
		return;
	}
	char Loctemp[100];
	LocMatch(loc, Loctemp);
	if (loc > 들판)
	{
		return;
	}

	//srand(time(NULL));
	//int index = (rand() % 몬스터대사의최대수);
	//
	//if (index >= 몬스터대사의최대수)
	//{
	//	printf("[error] 몬스터를 저장할 수 있는 최대 수 보다 큰 인덱스에 접근하고 있습니다.\n");
	//}

	printf("%s에서 %s(이)가 나타났다.\n", &Loctemp, monster->name);
	MonsterTalking(monster, other);
	//printf("%s : %s\n", monster->name, monster->dialogue[index]);

}


int main()
{
	Monster goblin;
	Location currentlocation = 숲;
	goblin.pos.x = 10;
	goblin.pos.y = 10;
	strcpy(goblin.name , "고블린");
	strcpy(goblin.dialogue[0], "켁케르 케르");
	strcpy(goblin.dialogue[1], "케르르르...");
	strcpy(goblin.dialogue[2], "케에엑 케에에");

	Monster orc;
	orc.pos.x = 10;
	orc.pos.y = 5;
	strcpy(orc.name , "오크");
	strcpy(orc.dialogue[0], "뀌익 뀌이익");
	strcpy(orc.dialogue[1], "죽인다 뀌익");
	strcpy(orc.dialogue[2], "꿰에에엑");
	//MonsterEncount(&orc, currentlocation);
	//printf("\n");

	MonsterEncount(&goblin, &orc, currentlocation);


	Monster oger;
	oger.pos.x = 10;
	oger.pos.y = 10;
	strcpy(oger.name, "오우거");
	strcpy(oger.dialogue[0], "크오오");
	strcpy(oger.dialogue[1], "크와아앙");
	strcpy(oger.dialogue[2], "크워어어어어어");

	MonsterEncount(&oger, &goblin, currentlocation);
}