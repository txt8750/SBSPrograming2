#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "parson.h"

typedef struct Item
{
	char name[50];
	int price;
}Item;

typedef struct GameScore
{
	int score;
}Score;

typedef struct Player
{
	char name[100];
	int level;
	int stage;
}Player;

void SaveFruitData()
{
	// JSON value 초기화
	JSON_Value* root_value = json_value_init_object();
	JSON_Object* root_object = json_value_get_object(root_value);

	// root_object에 "name" : "apple" 추가
	json_object_set_string(root_object, "name", "apple");
	// root_object에 "price" : 10 추가
	json_object_set_number(root_object, "price", 10);

	// JSON 파일 생성
	json_serialize_to_file_pretty(root_value, "fruit.json");
	json_value_free(root_value);
}
void LoadFruitData()
{
	// Data Load
	JSON_Value* load_value = json_parse_file("fruit.json");
	JSON_Object* load_object = json_value_get_object(load_value);
	printf("%s : %.0lf골드\n", json_object_get_string(load_object, "name"), json_object_get_number(load_object, "price"));
}


void SavePlayerData(const Player* player)
{
	// JSON value 초기화
	JSON_Value* root_value = json_value_init_object();
	JSON_Object* root_object = json_value_get_object(root_value);

	// root_object에 "name" : "apple" 추가
	json_object_set_string(root_object, "name", player->name);
	// root_object에 "price" : 10 추가
	json_object_set_number(root_object, "level", player->level);
	json_object_set_number(root_object, "stage", player->stage);

	// JSON 파일 생성
	json_serialize_to_file_pretty(root_value, "playerdata.json");
	json_value_free(root_value);
}
Player LoadPlayerData()
{
	Player player;
	JSON_Value* load_value = json_parse_file("playerdata.json");
	JSON_Object* load_object = json_value_get_object(load_value);

	strcpy(player.name, json_object_get_string(load_object, "name"));
	player.level = json_object_get_number(load_object, "level");
	player.stage = json_object_get_number(load_object, "stage");

	json_value_free(load_value);
	return player;
}

void SaveScore(Score* score)
{
	JSON_Value* root_value = json_value_init_object();
	JSON_Object* root_object = json_value_get_object(root_value);

	json_object_set_number(root_object, "score", score->score);

	json_serialize_to_file_pretty(root_value, "score.json");
	json_value_free(root_value);
}
Score LoadScore()
{
	Score score;

	JSON_Value* load_value = json_parse_file("score.json");
	JSON_Object* load_object = json_value_get_object(load_value);
	score.score = json_object_get_number(load_object, "score");
	json_value_free(load_value);
	return score;
}
int main()
{
	printf("JSON 입력 예제 구현\n\n"); // Save 구현, [Player 데이터, BestScore]

	// 포인터 주소. 초기화. NULL


	LoadFruitData();
	SaveFruitData();
	printf("\n");
	

	// 플레이어 구조체를 저장 및 로드 하기 예제

	Player player;
	player.level = 15;
	strcpy(player.name, "Hero"); // 저장은 영어이름만 가능
	player.stage = 15;

	printf("저장하시겠습니까? [0] YES | [1] NO\n");
	int select = 0;
	scanf("%d", &select);
	if (select == 0)
	{
		SavePlayerData(&player);
	}
	player = LoadPlayerData();
	printf("%s : %dLv\n", player.name, player.level);
	printf("%d Stage\n", player.stage);
	printf("\n");



	Score score;
	score.score = 30;
	printf("저장하시겠습니까? [0] YES | [1] NO\n");
	scanf("%d", &select);
	if (select == 0)
	{
		SaveScore(&score);
	}
	score = LoadScore();
	printf("score : %d\n", score.score);





	



	
}