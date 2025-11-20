#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parson.h"
/*
typedef struct Monster
{
	char* name[100];
	char* dialogue[3][100];

}Monster;
*/

int main()
{
	/*
	FILE* fp = fopen("myjson.txt", "w"); // "example.txt"이라는 파일에 쓰기 권한 부여
	  // 만약 해당 파일이 없으면 생성 할 것. 근데 어느 경로에 생성이 되는가? -> 해당 프로젝트 내부에 생성이 됨.
	  // 파일을 여는 명령, OS가 해당 파일을 열고있다고 인식, 다른곳에서 사용하려면 못함
	  // FILE* 변수 = fopen("파일명", "권한");

	fprintf(fp, "{");
	fprintf(fp, "\"%s\" : \"%s\"", "name", "HelloWorld!"); // example.txt 파일에 Hello World! 구문을 작성
	fprintf(fp, "}");
	  // 구문이 추가된 상태에서 동일 명령을 한번 더 실행했더니 덮어쓰기가 됨.(추가의 개념이 아님)
	  // fprintf(권한이부여된 파일, "서식 지정자", "구문");

	fclose(fp); // 열었던 파일을 닫는 구문, 파일을 닫아서 다른 곳에서 사용할 수 있게 해줌

	Monster goblin;
	int count = 0;
	FILE* fp2 = fopen("example.txt", "r"); // example.txt 파일에 읽기 권한 부여
	
	char text[100]; //text 배열 생성
	fscanf(fp2, "%s %s %s %s %d", goblin.name, goblin.dialogue[0], goblin.dialogue[1], goblin.dialogue[2], &count); // text라는 배열에 fp2로부터 읽어온 서식 지정자(%s, 문자)를 저장하라
	// 정수를 가져오는 경우 주소형태로 가져와야함
	//서식 지정자를 여러개 사용하면 제일 처음부터 쭉 가져옴
	// 가져오는데 공백은 제외하고 가져온다?? -> 기본적으로 공백문자를 기준으로 구분(구분자 : 공백문자)

	fclose(fp2);  // 열었던 파일 닫음

	printf("%s %s %s %s %d\n", goblin.name, goblin.dialogue[0], goblin.dialogue[1], goblin.dialogue[2], count); // text에 저장된 문자열 출력

	// 파일을 입력하고 쓰는 방법을 예제를 구현했다.
	// 메모장에 있는 파일에 권한을 부여해줘야 하는구나.
	*/



	// Monster데이터의 name에다가 json파일에 name을 찾아서 가져와라
	// Monster데이터의 name을 json으로 저장해라.
	// JSON -> Java script object notation, 자바스크립트의 오브젝트 표현 방식

	// JSON 사용해서 몬스터 데이터를 저장해보자.
	// 만들어진 소스코드를 가져오자.

	//Monster rabbit;
	/*
	JSON_Value* rootValue; // 파일 이름을 불러와서 저장한다.(파일 오픈)
	JSON_Object* rootObject; // 파일 안에 저장되어있는 실제 데이터

	rootValue = json_parse_file("data.json");  // 기존 .json파일을 파싱하여 불러온다. 불러와서 rootValue에 저장
	rootObject = json_value_get_object(rootValue); // 불러온 파일의 오브젝트를 rootObject에 저장, 해당 파일안의 데이터

	const char* tempName = json_object_get_string(rootObject, "name"); // rootObject의 데이터 중 키가 name인 항목의 값을 tempNmae에 저장

	printf("name : %s\n", json_object_get_string(rootObject, "name")); // rootObject의 데이터 중 키가 name인 항목의 값을 출력

	JSON_Array* array = json_object_get_array(rootObject, "dialogue"); // rootObject의 데이터 중 키가 dialogue인 항목의 배열을 array 저장

	for (int i = 0; i < json_array_get_count(array); i++) // json_array_get_count -> 배열의 개수
	{
		printf("[%s] : %s\n", tempName, json_array_get_string(array,i)); // 배열의 문자열을 가져옴
	}

	json_value_free(rootValue); // 열고있던 파일 닫음
	*/
	
	JSON_Value* chain_Value;
	JSON_Object* chain_Object;

	chain_Value = json_parse_file("chainsawman.json");
	chain_Object = json_value_get_object(chain_Value);

	JSON_Array* GenreArray = json_object_get_array(chain_Object, "Genre");

	printf("Genre : ");
	for (int i = 0; i < json_array_get_count(GenreArray); i++)
	{
		if (i == json_array_get_count(GenreArray) - 1)
		{
			printf("%s\n", json_array_get_string(GenreArray, i));
		}
		else
		{
			printf("%s, ", json_array_get_string(GenreArray, i));
		}
	}
	printf("Director : %s\n", json_object_get_string(chain_Object, "Director"));
	printf("Sub Director : %s\n", json_object_get_string(chain_Object, "Sub Director"));
	printf("Senario : %s\n", json_object_get_string(chain_Object, "Senario"));
	printf("Original : %s\n", json_object_get_string(chain_Object, "Original"));

	json_value_free(chain_Value);
	
}