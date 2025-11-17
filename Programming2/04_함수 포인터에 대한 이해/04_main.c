#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 함수 포인터
// 함수   : 입력값을 전달하면 출력을 반환한다. 
// 포인터 : 가리키다. 주소(0x). 
// 주소에서 데이터를 읽으려면 어떻게 해야하나요? = 데이터가 어떤 형태인지 정의(자료형)
// void 포인터 : 어떤 형태로든 바뀔 수 있는 주소 (형변환과 함께 사용하면 모든 포인터가 될 수 있다)
// 포인터를 사용하는 이유.
// 1. 주소로 저장되어있는 값에 접근할 수 있다. 범위가 다른 영역에서 주소에 저장된 값을 변경할 수 있다.
// 2. 주소의 크기 : 사용자 정의 자료형(구조체)의 크기가 클 때 주소를 사용하여 함수에 전달하게되면 메모리 사용을 감소시킬 수 있다.
// 3. 포인터 변수 : 주소는 가리키는 대상이 바뀔 수 있다.
// 4. 함수 포인터 : 함수도 주소인가? 주소를 호출하면 함수포인터로 함수를 호출할 수 있는가?

typedef struct
{
	int atk;
	int movespeed;
	int def;
	const char* name;
	void (*action)(this); // this. 자기자신, 자기자신의 주소를 넘겨주겠다는 뜻
	// 현재 구조체 MonsterAction의 주소를 넘겨준다는 뜻이다.
	// 함수포인터 안에 함수포인터는 문법적으로 안된다.
}MonsterAction;

int Plus(int num1, int num2)
{
	int temp;
	temp = num1 + num2;

	
}

int Minus(int num1, int num2)
{
	int temp;
	temp = num1 - num2;
	return temp;
}

void MonsterEncounter(const char* monsterName)
{
	const char* countMonster = monsterName;
	printf("몬스터의 이름 : %s\n", monsterName);
}

void Test(const char* a1)
{
	printf("%s\n", a1);
}

void M_Move(const MonsterAction* monster)
{
	printf("%s이(가) (%d)속도로 이동합니다.\n", monster->name, monster->movespeed);

}

void M_Attack(const MonsterAction* monster)
{
	printf("%s이(가) (%d)공격력으로 공격합니다.\n", monster->name, monster->atk);

}

void M_Defend(const MonsterAction* monster)
{
	printf("%s이(가) (%d)방여력으로 방어합니다.\n", monster->name, monster->def);

}

void Sample(void (*cbfp)())
{
	printf("Sample입니다\n");
	cbfp();
}

void Callback()
{
	printf("콜백 함수 실행!\n");
}

/*
void M_behavior(MonsterAction behavior)
{
	if (behavior.action == M_Move)
	{
		behavior.action = M_Defend;
		behavior.action();
	}
	else if (behavior.action == M_Avoid)
	{
		behavior.action = M_Attack;
		behavior.action();
	}
	else if (behavior.action == M_Defend)
	{
		behavior.action = M_Avoid;
		behavior.action();
	}
	else if (behavior.action == M_Attack)
	{
		behavior.action = M_Move;
		behavior.action();
	}
}
*/

int main()
{
	int a = 10;
	int b = 20;
	int* ptr = &b;
	printf("ptr에 저장된 값 : %d\n", *ptr);
	ptr = &a;
	printf("ptr에 저장된 값 : %d\n", *ptr);

	// a,b,ptr 이름을 게임에 등장하는 요소로 바꾸어 보자
	const char* a1 = "고블린";
	const char* a2 = "슬라임";
	MonsterEncounter(a1);
	MonsterEncounter(a2);

	// 전투를 담당하는 기능을 구현
	printf("\n함수 포인터의 이해\n");
	// 함수도 주소인가?
	printf("함수 이름 : %p\n", MonsterEncounter); // -> 함수 이름이 주소로 출력된다?!

	(*MonsterEncounter)("오크");   // 함수 포인터 : 함수의 주소를 가리킨다.
	                               // 포인터의 본문은 함수에 생성되어있는 본문을 말한다.
								   // (*함수이름)(매개변수) 형태로도 함수 실행 가능

	void (*fp)(const char*) = MonsterEncounter; // 함수포인터를 사용한 함수선언?
												// void (*변수명)(매개변수타입) = 기존함수명
	fp("오우거");								// 해당 구문 사용시 일반 함수 호출하는 것과 똑같이 사용가능

	fp = Test;									// 함수에 다른 함수를 넣어서 변경 가능.
	fp("Hello world!");
	
	// 타입이 int 인자를 int,int 함수를 저장하는 포인터를 생성하고 연결해보자 (사칙연산)
	
	printf("%d\n", Plus(1,2));		// Plus 함수 실행 및 출력

	int (*calPtr)(int, int) = Plus; // 함수 포인터 선언
	printf("%d\n", calPtr(3,4));    // 함수 포인터 실행 및 출력
	
	calPtr = Minus;					// 함수 포인터 변경
	calPtr(2, 1);					// 함수 포인터 실행
	int result = calPtr(2, 1);		// 함수 포인터 반환값 저장
	printf("%d\n", result);			// 함수 포인터 실행 값 출력

	// 함수 포인터를 사용하는 예제(2개)
	// 1. 구조체안에 함수 포인터를 저장하게 만들어보자
	// 몬스터 구조체 생성. 어떤 행동을 할 것인지 저장하는 함수 포인터를 선언
	MonsterAction goblin;
	goblin.name = malloc(sizeof(char) * 20);
	strcpy(goblin.name,"고블린");
	goblin.movespeed = 2;
	goblin.atk = 10;
	goblin.def = 8;
	goblin.action = M_Move;
	goblin.action(&goblin);
	// 2. 함수를 실행시킬 수 있는 주소. 함수 안에 함수를 만들 수 있다.
	// 특정 기능이 끝났을 때 호출되는 함수를 구현해본다. (Call back 함수)
	//M_behavior(M_action);
	void (*fp2)(const MonsterAction*) = M_Attack;
	fp2(&goblin);
	

	Sample(Callback); // 함수가 함수를 인자로 받는 코드
}

