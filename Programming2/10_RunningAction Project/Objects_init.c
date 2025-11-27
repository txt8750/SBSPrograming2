#include "Struct.h"
#include "GlobalConst.h"
#include "parson.h"

extern Obstacle obstacles[];
extern Jelly jellies[];
extern JSON_Value* score_Value;
extern JSON_Object* score_Object;

// 플레이어 정보 초기화
// pos x, pos y, max score, current score
// is_jumping. 점프 여부
// gravity. 점프, 낙하 속도
// base_y. 지면의 좌표
// height. 플레이어의 높이(키, 충돌판정)
// width. 플레이어의 X좌표 크기(충돌 판정)

void Player_init(Player* player)
{
	score_Value = json_parse_file("Score.json");
	score_Object = json_value_get_object(score_Value);
	player->pos.x = 5; // 플레이어의 초기 X좌표(사실상 고정 된 값)
	player->pos.y = GROUND_Y; // 플레이어의 초기 Y좌표(지면에 서있음)
	player->score.max = json_object_get_number(score_Object, "BEST Score"); // 최고 점수 초기화
	player->score.current = 0; // 현재 점수 초기화
	player->is_jumping = 0; // 점프 상태 초기화(0 : 점프 x, 1 : 점프 o)
	player->gravity = 0; // 점프, 낙하 속도 초기화(점프하게되면 변경)
	player->base_y = GROUND_Y; // 지면의 좌표
	player->height = 2;
	player->width = 2; // 2x2 사이즈의 플레이어 생성
}

// 장애물 정보 초기화
void Obstacle_init() // 장애물은 배열의 형태로 위에서 선언 했으므로 구조체를 인수로 받지 않음
{                    // 각 배열의 구조체에 for문을 사용하여 초기화
	// 장애물의 pos는 장애물이 활성화 되었을 때 설정을해야하므로 활성화 여부 값만 초기화
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		obstacles[i].is_active = 0;
	}
}


// 젤리 정보 초기화
void Jelly_init()
{
	// 젤리도 장애물과 같이 초기화 하되 형상과 점수는 같이 초기화한다.
	// 장애물이 활성화 되었을 때 바뀌는 값이 아니기 때문
	for (int i = 0; i < MAX_JELLY; i++)
	{
		jellies[i].is_active = 0;
		jellies[i].jelly_char = '@'; //젤리 형상
		jellies[i].point = 20; // 젤리 한개 당 점수
	}
}