#include "Struct.h"
#include "parson.h"
#include "ScoreSaveLoad.h"
#include "GlobalConst.h"

// 베스트 스코어 저장
void SaveScore(Player* p)
{
	JSON_Value* score_value = json_value_init_object();
	JSON_Object* score_object = json_value_get_object(score_value);

	json_object_set_number(score_object, "score", p->score.max);
	json_serialize_to_file_pretty(score_value, "score.json");
	json_value_free(score_value);
}

Player LoadScore()
{
	JSON_Value* score_value;
	JSON_Value* score_object;
	Player player;

	score_value = json_parse_file("score.json");
	score_object = json_value_get_object(score_value);
	player.score.max = json_object_get_number(score_object, "score");
	player.pos.x = 5; // 플레이어의 초기 X좌표(사실상 고정 된 값)
	player.pos.y = GROUND_Y; // 플레이어의 초기 Y좌표(지면에 서있음)
	player.score.current = 0; // 현재 점수 초기화
	player.is_jumping = 0; // 점프 상태 초기화(0 : 점프 x, 1 : 점프 o)
	player.gravity = 0; // 점프, 낙하 속도 초기화(점프하게되면 변경)
	player.base_y = GROUND_Y; // 지면의 좌표
	player.height = 2;
	player.width = 2; // 2x2 사이즈의 플레이어 생성

	return player;
}