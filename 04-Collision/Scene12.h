#pragma once
#include "Scenes.h"
#include "Load_resources.h"

#include "Brick.h"
#include "Simon.h" 
#include "Map.h"
#include "Camera.h"
#include "Grid.h"
#include "Items.h" 
#include "BoardGame.h"
#include "Dagger.h"
#include "HitEffect.h"
#include "GameTime.h"
#include "Sound.h"
#include "Data.h"
#include "Enemy.h"
#include "HolyWater.h"
#include "Axe.h"
#include "GameEnd.h"
#include "Scene11.h"

#define GAME_TIME_SCENE2 300

#define TIME_BETWEEN_GHOSTS_CREATE 1000 // 1 giây - khoảng thời gian phải chờ giữa ghost đầu và ghost sẽ được tạo tiếp theo
#define TIME_GHOST_REBORN 3000 // 3 giây sẽ tạo lại turn ghost mới

#define CAMERA_AUTOGOX_BEFORE_DOOR_1 2809.0f
#define CAMERA_AUTOGOX_AFTER_DOOR_1 3073.0f

#define REGION_CREATE_GHOST_LEFT_1 0
#define REGION_CREATE_GHOST_RIGHT_1 825.0f
#define REGION_CREATE_GHOST_LEFT_2 2220.0f
#define REGION_CREATE_GHOST_RIGHT_2 2775.0f
#define REGION_CREATE_GHOST_LEFT_3 4233.0f // biên trái vùng hoạt động
#define REGION_CREATE_GHOST_RIGHT_3 4993.0f// biên phải vùng hoạt động
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

class Scene_2 : public Scenes
{
private:

	Simon * simon;
	Map * TileMap;
	Camera *camera;
	Grid * gridGame;
	BoardGame * board;
	Sound * sound;

	vector<LPGAMEOBJECT> listObj;

	vector <Items*> listItem;
	vector <HitEffect*> listEffect;
	vector <CGameObject*> listEnemy;
	vector <Weapons*> listWeaponOfEnemy; // list chứa các viên đạn của enemy

	CGameTime * gameTime;

	int stateGame;

	bool gameOver;
	FontGame option;
	Load_resources * optionHeart;
	int optionSelect;

	int CountEnemyGhost; // số lượng ghost hiện tại
	DWORD TimeCreateGhost; // thời điểm bắt đầu tạo ghost
	DWORD TimeWaitProcessCreateGhost; // Thời điểm bắt đầu chờ xử lí việc tạo ghost
	bool isGenerateGhost; // kiểm tra có đang tạo ghost k
	bool isExistGhost; // kiểm tra ghost còn tồn tại k
	int countGhostBorn = 0; // đếm không giảm ghost

	/*Xử lí liên quan đi qua cửa*/
	bool isProcessingGoThroughTheDoor1;
	bool isDoneSimonGoThroughTheDoor1;
	bool isDoneCameraGoThroughTheDoor1;

	/*Xử lí liên quan đi qua cửa 2*/
	bool isProcessingGoThroughTheDoor2;
	bool isDoneSimonGoThroughTheDoor2;

	/*Xử lí liên quan tạo Panther*/
	bool isGeneratePanther;
	int CountEnemyPanther;

	/*Bat*/
	DWORD TimeCreateBat; // thời điểm đã tạo Bat
	DWORD TimeWaitProcessCreateBat; // thời gian phải chờ để tạo bat
	bool isGenerateBat; // cho phép tạo Bat
	int CountEnemyBat;

	/*Xử lí liên quan tạo Fishmen*/
	bool isAllowCreateFishmen;
	int CountEnemyFishmen;
	DWORD TimeCreateFishmen;
	DWORD TimeWaitCreateFishmen;

	int CountBoss;

	/* Xử lí liên quan Clear State 3 */
	bool isAllowProcessClearState3;
	int StatusProcessClearState3;
	DWORD TimeWaited_ClearState3;
	DWORD LimitTimeWait_ClearState3;

	bool testa;
	bool isProcessingGoThroughTheDoorBoss;

	DWORD magicTime;
	bool magicDown;

public:
	Scene_2(Simon * _simon = NULL, CGameTime* _gameTime = NULL);
	~Scene_2();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();
	void Update(DWORD dt);
	void Render();

	void GenerateGhost();
	void GeneratePanther();
	void GenerateBat();
	void GenerateFishmen();
	void GenerateBoss();

	void ProcessingPassDoorState();
	void ProcessingDoneStateBoss(DWORD dt);

	void CheckCollision();
	void CheckCollisionWeapon(vector<LPGAMEOBJECT> listObj);
	void CheckCollisionSimonWithItem();
	void CheckCollisionSimonWithHidenObject();
	void CheckCollisionWithEnemy();
	void CheckCollisionSimonWithEnemy();
	void CheckCollisionSimonWithGate();

	void ResetResource(); // reset lai resource khi simon mất 1 mạng

	Items * GetNewItem(int Id, def_ID Type, float X, float Y);
};