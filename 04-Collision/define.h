#ifndef _DEFINE_H__
#define _DEFINE_H__

#define _USE_MATH_DEFINES

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "debug.h"
#include <vector>
#include <Windows.h> 
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 448
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480

#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 


#define SHOWBOX_PINK 0

#define IS_DEBUG_RENDER_BBOX 1

/*simon*/
#define SIMON_POSITION_DEFAULT  50.0f, 100.0f

#define SIMON_BBOX_WIDTH 60
#define SIMON_BBOX_HEIGHT 66
#define SIMON_BBOX_SITTING_HEIGHT 48

#define SIMON_GRAVITY 0.005f
#define SIMON_VJUMP 0.34f

#define SIMON_WALKING_SPEED_SCENE_1 0.09f 
#define SIMON_WALKING_SPEED 0.15f 

#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1

#define SIMON_ANI_WALKING_BEGIN 1
#define SIMON_ANI_WALKING_END 3

#define SIMON_ANI_STANDING_ATTACKING_BEGIN 5
#define SIMON_ANI_STANDING_ATTACKING_END 7

#define SiMON_ANI_IDLE 0
#define SIMON_ANI_JUMPING 4
#define SIMON_ANI_SITTING 4

#define SIMON_ANI_SITTING_ATTACKING_BEGIN 15
#define SIMON_ANI_SITTING_ATTACKING_END 17

#define SIMON_ANI_STAIR_GO_UP_BEGIN 12
#define SIMON_ANI_STAIR_GO_UP_END 13

#define SIMON_ANI_STAIR_GO_DOWN_BEGIN 10
#define SIMON_ANI_STAIR_GO_DOWN_END 11

#define SIMON_ANI_STAIR_UP_ATTACKING_BEGIN 21
#define SIMON_ANI_STAIR_UP_ATTACKING_END 23

#define SIMON_ANI_STAIR_DOWN_ATTACKING_BEGIN 18
#define SIMON_ANI_STAIR_DOWN_ATTACKING_END 20

#define SIMON_ANI_ENEMY_HIT 8

#define SIMON_SPEED_ONSTAIR 0.07f
#define SIMON_VJUMP_ENEMY_HIT 0.5f

#define SIMON_ANI_STAIR_STANDING_UP 12
#define SIMON_ANI_STAIR_STANDING_DOWN 10

#define SIMON_STAIR_PROCESSING 8.0f
#define SIMON_STAIR_PROCESSING_DONE 16.0f

#define SIMON_UNTOUCHABLE_TIME 2000 

#define TIME_FREEZE_MAX 500

#define SIMON_GRAVITY_JUMPING 0.001f//0.005f
#define SIMON_BBOX_JUMPING_HEIGHT 45

/*item*/
#define TIMEWAITMAX 400
#define ITEM_GRAVITY 0.25f
#define ITEM_TIMEDISPLAYMAX 3000
#define ITEM_TIMEWAITMAX 300

//scene
#define GAME_TIME_SCENE1 300
#define GAME_TIME_SCENE2 300

#define TIME_BETWEEN_GHOSTS_CREATE 1000 
#define TIME_GHOST_REBORN 3000 

#define CAMERA_AUTOGOX_BEFORE_DOOR_1 2809.0f
#define CAMERA_AUTOGOX_AFTER_DOOR_1 3073.0f

#define REGION_CREATE_GHOST_LEFT_1 0
#define REGION_CREATE_GHOST_RIGHT_1 825.0f
#define REGION_CREATE_GHOST_LEFT_2 2220.0f
#define REGION_CREATE_GHOST_RIGHT_2 2775.0f
#define REGION_CREATE_GHOST_LEFT_3 4233.0f 
#define REGION_CREATE_GHOST_RIGHT_3 4993.0f
#define REGION_CREATE_GHOST_TOP 4412.0f 
#define REGION_CREATE_GHOST_BOTTOM 4590.0f

#define REGION_CREATE_PANTHER_LEFT 1100.0f
#define REGION_CREATE_PANTHER_RIGHT 2220.0f

#define BOUNDARY_BEFORE_THROW_GATE_1 2580.0f

#define FISHMEN_ZONE_1_LEFT 3065.0f
#define FISHMEN_ZONE_1_RIGHT 3193.0f 
#define FISHMEN_POS_1 3121.0f 

#define FISHMEN_ZONE_2_LEFT 3193.0f
#define FISHMEN_ZONE_2_RIGHT 3326.0f
#define FISHMEN_POS_2 3254.0f 

#define FISHMEN_ZONE_3_LEFT 3326.0f
#define FISHMEN_ZONE_3_RIGHT 3458.0f
#define FISHMEN_POS_3 3382.0f 

#define FISHMEN_ZONE_4_LEFT 3458.0f
#define FISHMEN_ZONE_4_RIGHT 3571.0f
#define FISHMEN_POS_4 3505.0f 

#define FISHMEN_ZONE_5_LEFT 3571.0f
#define FISHMEN_ZONE_5_RIGHT 3707.0f
#define FISHMEN_POS_5 3636.0f 

#define FISHMEN_ZONE_6_LEFT 3707.0f
#define FISHMEN_ZONE_6_RIGHT 3829.0f
#define FISHMEN_POS_6 3760.0f 

#define FISHMEN_ZONE_7_LEFT 3829.0f
#define FISHMEN_ZONE_7_RIGHT 3956.0f
#define FISHMEN_POS_7 3881.0f 


#define FISHMEN_ZONE_8_LEFT 3956.0f
#define FISHMEN_ZONE_8_RIGHT 4095.0f
#define FISHMEN_POS_8 4017.0f 

#define CAMERA_BOUNDARY_LAKE_LEFT 3075.0f
#define CAMERA_BOUNDARY_LAKE_RIGHT 4111.0f-Window_Width

#define CAMERA_POSITION_Y_LAKE 374.0f

#define GATE2_POSITION_CAM_BEFORE_GO 3840.0f
#define GATE2_POSITION_CAM_AFTER_GO 4095.0f

#define DISTANCE_AUTO_WALK_AFTER_GATE 80.0f // simon phải tự đi 80px sau khi chạm vào cửa
#define CAMERA_BOUNDARY_BOSS_RIGHT 5648.0f - Window_Width

#define CLEARSTATE3_PROCESS_HEALTH 0 // xử lí làm đầy máu
#define CLEARSTATE3_PROCESS_GETSCORE_TIME 1 // xử lí quy đổi thời gian dư ra điểm
#define CLEARSTATE3_PROCESS_GETSCORE_HEART 2 // xử lí quy đổi thời gian dư ra điểm
#define CLEARSTATE3_PROCESS_DONE 3 // xử lí xong

#define CLEARSTATE3_LIMITTIMEWAIT_PROCESS_HEALTH 200 // thời gian chờ tăng mỗi đơn vị máu
#define CLEARSTATE3_LIMITTIMEWAIT_PROCESS_GETSCORE_TIME 10 // thời gian chờ tăng mỗi đơn vị point
#define CLEARSTATE3_LIMITTIMEWAIT_PROCESS_GETSCORE_HEART 200 // thời gian chờ tăng mỗi đơn vị point

#define OPTION_SELECT_CONTINUE 1
#define OPTION_SELECT_END 2

// enemy
#define GHOST_SPEED 0.08f

#define PANTHER_ANI_SITTING 0
#define PANTHER_ANI_RUNNING_BEGIN 1
#define PANTHER_ANI_RUNNING_END 3
#define PANTHER_SPEED_RUNNING 0.20f
#define PANTHER_VYJUMP 0.5f
#define PANTHER_VXJUMP 0.5f

#define BAT_SPEED 0.08f
#define BAT_VY 0.08f
#define GHOST_GRAVITY 0.005f

#define FISHMEN_SPEED_Y_UP 0.6f
#define FISHMEN_SPEED_Y_DOWN 0.3f

#define FISHMEN_DY_JUMP 350 // nhảy lên khoảng 330px thì rớt xuống

#define FISHMEN_ANI_JUMP 2 // nhảy lên khoảng 330px thì rớt xuống
#define FISHMEN_GRAVITY_JUMPING 0.0083f

#define FISHMEN_DX_LIMIT 140 // đi được khoảng 140px thì đổi hướng
#define FISHMEN_DX_ATTACK_LIMIT 130 // đi được khoảng 140px thì đổi hướng

#define FISHMEN_TIME_LIMIT_WAIT_AFTER_ATTACK 700 // thời gian fishmen phải đứng lại chờ trước khi đi tiếp, sau khi attack

#define BOSS_PROCESS_SLEEP 0

#define BOSS_PROCESS_START_1 1 // lúc bắt đầu, Bat di chuyển xuống
#define BOSS_PROCESS_START_2 2 // lúc bắt đầu, Bat di chuyển đến cửa sổ (nửa vòng cung)

#define BOSS_PROCESS_CURVES 3 // lúc di chuyển theo vòng cung

#define BOSS_PROCESS_STRAIGHT_1 4 // xử lí di chuyển thẳng lần 1
#define BOSS_PROCESS_STRAIGHT_2 5 // xử lí di chuyển thẳng lần 2

#define BOSS_PROCESS_ATTACK 6 // xử lí tấn công




extern int Window_Width;
extern int Window_Height;

extern int MapWidth;
extern int MapHeight;

extern int ScreenColumn;
extern int ScreenRow;

extern int rdb;
 
// ID của Sprite, object
enum def_ID
{
	SIMON = 01,
	HIT = 02,
	EFFECT = 03,
	FONTGAME = 04,
	BLACKBOARD = 05,
	RENDERBOX = 06,
	BRICK_TYPE_1 = 07,
	BRICK_TYPE_2 = 8,
	BRICK_TYPE_3 = 9,
	BRICK_TRANSPARENT = 10,
	HEARTPOINT = 11,
	WATER = 12,
	BRICKSPLASH = 20,
	BRICK = 21,
	BRICK_3X32 = 22,
	BRICK_4X32 = 23,
	TEX_BRICK_TRANSPARENT = 25,
	GATE = 26,
	BIGCANDLE = 41,
	HIDDENOBJECT = 42,
	SMALLCANDLE = 43,

	STAIR = 44,
	BOTTOMSTAIR = 47,
	TOPSTAIR = 48,

	//simon death
	SIMONDEATH = 49,
	
	//weapon
	MORNINGSTAR = 61,
	DAGGER = 62,
	HOLYWATER = 63,
	ENEMYBULLET = 65,
	AXE = 66,

	//item
	BIGHEART = 81,
	UPGRADEMORNINGSTAR = 82,
	iDAGGER = 83,
	MONNEYBAG = 84,
	SMALLHEART = 85,
	iHOLYWATER = 86,
	POTROAST = 87,
	iAXE = 88,
	MAGICCRYSTAL = 89,

	//enemy
	GHOST = 141,
	PANTHER = 142,
	BAT = 143,
	FISHMEN = 144,
	BOSS = 161,

	//intro
	MAINMENU = 181,
	INTRO_GO_SCENE1 = 182,
	INTRO_BAT_MENU = 183, // bat ở menu
	HELICOPTER = 184,
	INTRO_BAT = 185, // ở intro

	//end
	CASTLE = 186,
	TOPCASTLE = 187

};

enum eDirection
{
	NONE = 0,
	TOP = (1 << 0),
	LEFT = (1 << 1),
	RIGHT = (1 << 2),
	BOTTOM = (1 << 3)
};

enum eHidden
{
	PROCESSINGSCENE1 = 7,
	PASSINGSCENE2 = 8,
	WATERDOWNLEFT = 41,
	WATERUPLEFT = 45,
	BONUS = 65,
	WATERFISHMEN = 66,
	PASSINGDOOR1 = 67,
	WATERDOWNRIGHT = 81,
	PASSINGDOOR2 = 94,
	BOSSAPPEAR = 124,
	WATERUPRIGHT = 125
};

enum eSound
{
	sMorningStar = 1,
	sHit = 2,
	sCollectItem = 3,
	sCollectWeapon = 4,
	sStopTimer = 5,
	sDagger = 6,
	sMonneyBag = 7,
	sWasEnemyHit = 8,
	sHollyWater = 9,

	smusicStage1 = 51,
	smusicLose = 52,
	sOpenDoor = 53
};

enum eMap
{
	mMap1 = 104,
	mMap2 = 106
};

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)


#ifndef SAFE_DELETE

#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif // !SAFE_DELETE

#endif // !_DEFINE_H__
