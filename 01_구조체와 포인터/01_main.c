#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// 자료형(data type) 선언. 정수(int), 실수(float)
// data - value
// 데이터가 저장되는 시작 주소를 퐁니터로 표현할 수 있다.
// int* a; -> 포인터 변수 선언
// &a; -> 변수의 주소
// *a; -> 역참조 연산자


typedef struct
{
	int hp;
	int atk;
	const char* name;
	int def;
}Monster;

void PrintMonsterInfo(const Monster* monster)
{
	printf("이름 : %s, 체력 : %d, 공격력 : %d, 방어력 : %d\n", monster->name, monster->hp, monster->atk, monster->def);
}

// 구조체의 주소로 부터 값을 가져온다. (*구조체포인터).변수
// (*구조체포인터).변수
// 구조체포인터 -> 변수
// 둘은 같은 표현이다.

void SetMonsterData(Monster* monster)
{
	//printf("몬스터의 이름 : ");
	//char temp[20];
	//scanf("%s", temp);
	
	//strcpy(monster->name, temp);

	printf("몬스터의 체력 : ");
	scanf("%d", &(monster->hp));
	printf("몬스터의 공력력 : ");
	scanf("%d", &(monster->atk));
	printf("몬스터의 방어력 : ");
	scanf("%d", &(monster->def));
}

int main()
{
	// 몬스터의 데이터 입력(초기화)
	Monster goblin = {0};
	SetMonsterData(&goblin);
	//goblin_a.name = "고블린";
	PrintMonsterInfo(&goblin);
	printf("\n");
	
	// 오크 체력 15, 공격력 2
	Monster Orc = {0};
	SetMonsterData(&Orc);
	PrintMonsterInfo(&Orc);
}