#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> // strcpy(des,src) src에서 des로 문자열을 복사하는 함수
#include <stdlib.h> // 표준 라이브러리함수. malloc 함수, free 함수


// int number; -> 4바이트 공간을 정수로 읽겠다. 시작하는 주소가 있어야 한다.
typedef struct
{
	int number;
	char* name;
	char* comment;
//	char name[100];
}Student;

// 어떤 Type을 선언할 때 그 데이터를 저장할 수 있는 주소가 만들어지는구나.

void SetStudentInfo(Student* student)
{
	// malloc(sizeof(자료형) * value) : 주소를 프로그래머가 직접 지정을 해주는 함수
	//            malloc함수를 반복해서 호출할 때 마다 메모리를 계속 할당한다. -> 메모리 공간을 계속 차지한다.
	// free(주소) : 동적할당 된 메모리를 해제한다.
	// malloc 함수를 쓰고 free함수를 반드시 사용할 것 -> 단 프로그램 실행중에 계속사용하는 데이터와 임시로 사용되는 데이터를 구분해야 함.
	printf("학생의 번호 : ");
	scanf("%d", &student->number);
	printf("학생의 이름 : ");
	char* temp = malloc(sizeof(char) * 100);  // temp에 메모리할당하여 초기화
	scanf("%s", temp);
	// student학생의 char주소에 이름을 저장하고 싶다.
	// student->name 주소는 지금 컴퓨터 메모리에 할당되지 않은 상태
	// 메모리 할당을 어떻게 할 수 있는가? malloc함수
	// 메모리 할당을 하면 어떤 일이 일어나는가?
	student->name = malloc(sizeof(char) * 100); // student.name에 메모리 할당하여 초기화
	strcpy(student->name, temp);
	free(temp);		// temp 의 동적할당 메모리 해제

	printf("학생에게 한마디 : ");
	char* temp2 = malloc(sizeof(char) * 100);
	scanf("%s", temp2);
	student->comment = malloc(sizeof(char) * 100);
	strcpy(student->comment, temp2);
	free(temp2);	// temp2의 동적할당 메모리 해제
	// student->name, comment의 경우 구조체에 저장하여 현재 함수 밖에서도 계속 사용할 데이터이므로 당장 메모리를 해제할 필요가 없다.
	// 프로그램이 종료될 때 메모리해제
}

void PrintStudentInfo(const Student* student)
{
	printf("학생의 번호 : %d, 학생의 이름 : %s\n", student->number, student->name);
	printf("학생에게 한마디 : %s\n", student->comment);
}

void Test()
{
	int a;
	printf("a의 주소 : %p\n", &a);
}

// 플레이어의 이동 구조체를 구현해서 함수로 설정할 수 있게 만들어보세요
// 텍스트도 포인터로 받아올 수 있게 되었다.
int main()
{
	Student s1;
	Student s2;
	SetStudentInfo(&s1);
	PrintStudentInfo(&s1);

	SetStudentInfo(&s2);
	PrintStudentInfo(&s2);

}

// 실습과제
// 구조체 Item Inventory 구조체를 만들어보자
// 몬스터를 처치했다. -> 인벤토리에 보상을 저장.
// Reward() << Inventory << Item
// 동적으로 변할 수 있도록 설정.
// 내 아이템의 크기를 변경해주는 함수. -> SetMyInventory()


// 둘의 차이점은?
// char A[100] -> 컴파일러가 주소를 직접 배정을 해준다. 프로그램이 실행되기 전인 링킹과정에서 컴파일러가 전체 코드를 인식하여 메모리를할당(정적할당)
// char* B = malloc(sizeof(char) * 100) -> 프로그램이 실행되는 중에 메모리를 할당한다.(동적할당)
// 동적할당은 왜 필요한가?
// 인벤토리. 몬스터의 보상을 저장을 한다.
// 프로그램 시작전에 정적할당으로 메모리를 할당하는 경우 인벤토리 공간을 얼마나 할당해야할까??
// 아이템 공간 확장 기능으로 인벤토리 공간을 확장.
// 전체 공간을 지정해놓고 일부를 닫아놓는 식으로도 구현 가능하나 메모리 할당에 비효율적
// char A[100] -> A라는 변수에 100개의 공간을가진 배열을 만듦
// char* B = malloc(sizeof(char) * 100) -> B라는 변수에 100개의 공간을 가진 메모리를 할당
// char* A[100] -> A라는 변수에 100개의 주소를 저장 가능한 공간을 생성

