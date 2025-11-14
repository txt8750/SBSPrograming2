#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> // strcpy 문자열 복사
#include <stdlib.h> // malloc, free 함수

// 정수/정수 -> 결과 값을 정수형으로 출력한다.
// 실수/정수 -> 결과 값을 실수로 출력(순서는 상관 없음, 실수/정수 정수/실수)
// 형변환(type casting) : int, char, unsigned char // int -> float . 정수를 실수로 바꾸겠다.

typedef enum {
	정수,
	실수,
	데이터
}CustomType;

typedef struct {
	int value;
	char text[100];
}Data;

typedef enum
{
	물,
	불,
	풀
}Monstertype; // 상성 시스템

typedef struct
{
	Monstertype monstertype;
	char* type;
	char* name;
}Monster;

void PrintMyType(void* monsterptr)
{
	((Monster*)monsterptr)->name = malloc(20);
	((Monster*)monsterptr)->type = malloc(20);

	if (((Monster*)monsterptr)->monstertype == 불) // 불타입 스타팅 포켓몬
	{
		strcpy(((Monster*)monsterptr)->name, "브케인");
		strcpy(((Monster*)monsterptr)->type, "불");
		printf("이름 : %s, 타입 : %s\n", ((Monster*)monsterptr)->name, ((Monster*)monsterptr)->type);

	}
	else if (((Monster*)monsterptr)->monstertype == 물) // 물타입 스타팅 포켓몬
	{
		strcpy(((Monster*)monsterptr)->name, "리아코");
		strcpy(((Monster*)monsterptr)->type, "물");
		printf("이름 : %s, 타입 : %s\n", ((Monster*)monsterptr)->name, ((Monster*)monsterptr)->type);
	}
	else if (((Monster*)monsterptr)->monstertype == 풀)  // 풀타입 스타팅 포켓몬
	{
		strcpy(((Monster*)monsterptr)->name, "치코리타");
		strcpy(((Monster*)monsterptr)->type, "풀");
		printf("이름 : %s, 타입 : %s\n", ((Monster*)monsterptr)->name, ((Monster*)monsterptr)->type);
	}
}

// 타입이 쎌때 같을때 클때 한번에 표현할 수 있는 함수, void*

void SelectNumberByType(void* selectedPtr, CustomType type)
{
	// 어떤 조건을 기준으로 : 실수 타입이면 실수로, 정수 타입이면 정수로 읽어라.
	
	if (type == 정수)
	{
		// 정수
		printf("%d\n", *(int*)selectedPtr);
	}
	else if (type == 실수)
	{
		// 실수
		// 정수 값을 저장을 해서. 실수로 변환한 다음에 출력
		printf("%f\n", *(float*)selectedPtr);
	}
	else if (type == 데이터)
	{
		// 데이터의 value와 text를 출력하는 코드
		printf("%d\n", ((Data*)selectedPtr)->value); // 포인터 매개변수를 구조체로 형변환을 할 때 (Data*)selectedPtr 보다 selectexPtr->value가 먼저 연산된다.
		                                             // 따라서 괄호를 추가하여 ((Data*)selectedPtr)->value 의 형식으로 만들어야 함.
		printf("%s\n", ((Data*)selectedPtr)->text);
	}
}

void PointerCastingTest()
{
	CustomType m_type = 정수;
	CustomType m_type2 = 실수;
	CustomType m_type3 = 데이터;
	int a = 10;
	float b = 0.5f;
	SelectNumberByType(&a, m_type);
	SelectNumberByType(&b, m_type2);

	Data data;
	data.value = 10;
	strcpy(data.text, "hello");
	SelectNumberByType(&data, m_type3);
}


int main()
{
	Monster f_monster;
	f_monster.monstertype = 불;
	PrintMyType(&f_monster);
	printf("이름 : %s, 타입 : %s\n", f_monster.name, f_monster.type);

	Monster w_monster;
	w_monster.monstertype = 물;
	PrintMyType(&w_monster);
	printf("이름 : %s, 타입 : %s\n", w_monster.name, w_monster.type);

	Monster g_monster;
	g_monster.monstertype = 풀;
	PrintMyType(&g_monster);
	printf("이름 : %s, 타입 : %s\n", g_monster.name, g_monster.type);



	/*
	// 최대 체력 - int
	// 현재 체력 - int
	// 현재 체력 비율 - double

	int MaxHP = 1000;
	int CurrentHP = 260;
	double HPpercent = (double)CurrentHP/MaxHP * 100;
	                         //실수     / 정수  * 정수 -> 실수 결과 출력

	printf("%d / %d (%.0llf%%)\n", CurrentHP, MaxHP, HPpercent);

	// 명시적 형변환 : (자료형)변수 . 형태로 작성하여 해당 변수의 자료형을 변경 할 수 있다.
	// 묵시적 형변환 : 자동으로 발생하는 형변환. 실수/정수 연산시 실수로 출력되는 것. 연산중에 자동으로 형변환이 발생한다.
	// case1. 실수, 정수 연산처리할 때 -> 실수로 변경된다.
	// case2. 데이터 크기가 작은 자료형은 큰쪽으로 맞춰야한다.
	// case2-2. 양수, 음수 구별하는 방법 : MSB 0, 1 음수
	// signed extension 부호 확장 방법. 음수의 경우 이 타입을 크기를 큰 타입으로 변환하면 새로 만들어진 공간에 1을 넣어라
	
	int a = 129;
	char b = a;

	printf("b의 값 : %d\n", b);
	
	// case3. 포인터를 형변환하면 어떤일이 일어날까?

	int* aptr = &a;
	// (리틀, 빅) 엔디안
	// 리틀 엔디안 : 주소를 뒤에서 부터 읽어온다. 작은 바이트 단위부터 읽는 방식
	// 빅 엔디안 : 주소를 앞에서 부터 읽어온다. 큰 바이트 단위부터 읽는 방식
	printf("aptr의 값 : %d\n", *(char*)aptr);
	// 포인터 주소인데, 포인터에 타입을 선언을 하고 *을 붙이는 이유가 뭘까
	// char* -> 시작 주소로 부터 몇개의 바이트를 어떻게 해석할건가.
	// int*

	// void* : 범용(generic) 포인터 - 일반적인 포인터 - 누구나 사용할 수 있다.
	// 타입이 선언되지 않은 주소를 만들 수 있으면 뭔가를 할 수 있겠다.

	void* generalPtr1 = &a;
	void* generalPtr2 = &b;   // void*로 선언은 되어있으나 자료형은 지정되지않은상태

	printf("generalPtr1의 값 : %d\n", *(int*)generalPtr1); // 해당 변수를 사용할때 자료형을 따로 지정해서 사용할 수 있다.
	printf("generalPtr2의 값 : %d\n", *(char*)generalPtr2);

	// 실수와 정수를 곱한다음에 소수점의 값이 0.5보다 작으면 버리고 0.5이상이면 올리는 반올림을 구현해보자
	// 조건문
	int num1 = 7;
	float num2 = 0.2f;

	float pivot = (num1 * num2) - (int)(num1 * num2);
	printf("피벗의 값 : %.1f\n", pivot);
	
	if (pivot < 0.5)
	{
		pivot = 0;
	}
	else {
		pivot = 1;
	}
	printf("반올림 값 : %d\n", (int)(num1 * num2) + (int)pivot);
	
	PointerCastingTest();
	*/
}