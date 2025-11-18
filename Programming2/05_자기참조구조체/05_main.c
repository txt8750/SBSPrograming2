#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 자기 참조 구조체 Self Reference struct.

typedef void (*CallBack)(int a, int b);

void Sample(void (*CBack)(int, int), int x, int y)
{
	printf("Hello wolrd\n");
	CBack(x,y);
}

void Plus(int a, int b)
{
	printf("두 수를 더한 값 : %d\n", a + b);
}

typedef struct Data{
	int value;
	struct Data* next;  // 자기참조구조체 사용시 주소의 형태로 전달해야함. *(포인터)사용
	                     // 자기참조구조체 사용시 시그니처(Data)가 아닌 struct (구조체명)으로 선언 필요.
	void (*fp)(CallBack cb, int a, int b);
}Data;

typedef struct DataManager
{
	Data* head;
}DataManager;

typedef struct Test
{
	char c1;
	int d1;
}Test; // 여기 마우스 올리면 크기 8byte, 맞춤 4byte라고 나옴. 4byte기준으로 맞춰서 최종크기가 결정됨
       // char 1byte, int 4byte로 실제 5byte를 차지해야할 것 같지만 위의 이유 때문에 최종크기는 8byte가 된다.

typedef struct Stat
{
	char name[100];
	double value;
}Stat;

typedef struct Item
{
	char* namePtr;
	char name[1];
	Stat stat;
	int price;
}Item;

// 또 다른 Monster를 참조할 수 있게 만들어 보자.
// 형제를 가지는 몬스터다. -> this는 가지면 안된다.
// 몬스터가 짝을 이루는 몬스터, 짝이 특정 상황이되면 특수한 행동
// 몬스터의 스탯

typedef struct MonsterStat
{
	int atk;
	int hp;
	int def;
	int atkspeed;
}MonsterStat;

typedef struct Monster
{
	struct Monster* brother;
	MonsterStat stat;
	char* name;
	void (*action1)(this);
	void (*action2)(this);
	void (*action3)(this);
}Monster;

void MonsterRage(Monster* brother)
{

}

void Monsterinvincibility(Monster* brother)
{

}

void ActionWithBrother(Monster* brother)
{
	printf("동료와 함께하는기술\n");
}

int main()
{

	Monster goblin;
	goblin.name = malloc(sizeof("고블린1"));
	goblin.name = "고블린1";
	goblin.stat.hp = 10;
	goblin.stat.atk = 1;
	goblin.stat.def = 1;
	goblin.stat.atkspeed = 1;
	goblin.action1 = ActionWithBrother;
	goblin.action2 = ActionWithBrother;
	goblin.action3 = ActionWithBrother;

	Monster goblin2;
	goblin.name = malloc(sizeof("고블린2"));
	goblin.name = "고블린2";
	goblin2.stat.hp = 10;
	goblin2.stat.atk = 1;
	goblin2.stat.def = 1;
	goblin2.stat.atkspeed = 1;
	goblin2.action1 = ActionWithBrother;
	goblin2.action2 = ActionWithBrother;
	goblin2.action3 = ActionWithBrother;

	goblin.brother = &goblin2;
	goblin2.brother = &goblin;


	Item item;
	item.namePtr = malloc(sizeof("빛나는 티끌"));
	item.namePtr = "빛나는 티끌";
	strcpy(item.name, "빛나는 티끌");
	printf("item의 배열 이름 : %s\n", item.name);
	printf("item의 포인터 이름 : %s\n", item.namePtr);

	printf("item의 크기 : %d\n", sizeof(Item));
	printf("item.name의 크기 : %d\n", sizeof(item.name));
	printf("item.namePtr의 크기 : %d\n", sizeof(item.namePtr));
	printf("item.stat의 크기 : %d\n", sizeof(item.stat));
	printf("item.price의 크기 : %d\n", sizeof(item.price));

	
	Data d1;
	printf("Data구조체의 크기 : %d\n", sizeof(d1.fp));
	printf("Data구조체의 크기 : %d\n", sizeof(d1.next));
	printf("Data구조체의 크기 : %d\n", sizeof(d1.value));
	printf("Data구조체의 크기 : %d\n", sizeof(d1));

	d1.value = 1;
	d1.fp = Sample;
	d1.fp(Plus, 2, 4);

	Data d2;
	d1.next = &d2;  // d1.other은 주소의 형태로 전달을 받기때문에 d2의 주소를 전달
	d2.value = 10;

	Data d3;
	d2.next = &d3;
	d3.value = 20;


	printf("d1이 가리키고 있는 d2의 값 : %d\n", (d1.next)->value);

	DataManager dm;
	dm.head = &d1;

	printf("dm의 첫번째 데이터 값 : %d\n", dm.head->value);
	printf("dm의 두번째 데이터 값 : %d\n", dm.head->next->value);
	printf("dm의 세번째 데이터 값 : %d\n", dm.head->next->next->value);

	// head n번째 떨어져있는 value를 출력하시오.
	int n = 2;

	// 반복문으로 표현
	Data* temp = dm.head;

	for (int i = 0; i < n; i++)
	{
		temp = temp->next;
	}
	printf("head에서 %d번째 떨어져 있는 값 : %d\n", n, temp->value);

	// 몬스터들을 저장하는 Manager 타입을 만들었다.
	// Manager에 n번째 저장된 데이터를 접근할 수 있게 되었다.
	// n번째에 들어있는 타입의 아무거나 사용할 수 있다.
}