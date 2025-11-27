#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "parson.h"

typedef struct Item
{
	char name[50];
	int price;
}Item;

// JSON 파일 열기
// json_parse_file("파일이름")

// JSON Value로 부터 Object 가져오기
// json_value_get_object(Value)

// JSON 숫자 오브젝트 가져오기
// json_object_get_number(오브젝트, 키)

// JSON 문자열 오브젝트 가져오기
// json_object_get_string(오브젝트, 키)
// (한글 출력시 ANSI 확은 코드페이지 949로 .json파일 인코딩)

// JSON 오브젝트로부터 배열 가져오기
// json_object_get_array(오브젝트, 키)
 
// JSON 배열 개수 가져오기
// json_array_get_count(배열)
 
// JSON 배열에서 숫자 오브젝트 가져오기 
// json_array_get_number(배열, 인덱스)    (1차원 배열)
// json_array_dotget_number(배열, 인덱스) (2차원 배열)
 
// JSON 배열에서 문자 오브젝트 가져오기
// json_array_get_string(배열, 인덱스)    (1차원 배열)
// json_array_dotget_string(배열, 인덱스) (2차원 배열)

// JSON 배열의 오브젝트 가져오기(2차원 배열)
// json_array_get_object(배열, 인덱스)

// 열어놓은 JSON 파일 닫기
// json_value_free(Value)

int main()
{
	printf("JSON 파일 활용하기 예제\n");
	Item itemStruct[4]; // 아이템 배열 생성

	JSON_Value* item_DB_Value;
	JSON_Array* items;
	JSON_Object* item_DB_Object;

	// JSON 파일 열기
	item_DB_Value = json_parse_file("itemDB.json");

	// 열어놓은 파일에서 오브젝트를 가져오겠다.
	item_DB_Object = json_value_get_object(item_DB_Value);

	// 오브젝트에서 배열을 가져오겠다.
	items = json_object_get_array(item_DB_Object, "items"); 

	// 배열에서 n번째 원소를 가져와서 출력하겠다.


	for (int i = 0; i < json_array_get_count(items); i++)
	{
		JSON_Object* array_object; // 임시 오브젝트 생성
		array_object = json_array_get_object(items, i); // 배열에서 가져온 오브젝트를 임시 오브젝트에 저장

		strcpy(itemStruct[i].name, json_object_dotget_string(array_object, "name"));
		itemStruct[i].price = json_object_dotget_number(array_object, "price");

		//printf("이름 : %s | 가격 : %d\n", itemStruct[i].name, itemStruct[i].price);
	}

	for (int i = 0; i < 4; i++)
	{
		printf("이름 : %s | 가격 : %d\n", itemStruct[i].name, itemStruct[i].price);
	}
	
}