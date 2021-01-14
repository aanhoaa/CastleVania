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

class Scene_2 : public Scenes
{
private:

	Simon * simon;
	Map * TileMap;
	Camera *camera;
	Grid * gridGame;
	BoardGame * board;
	Sound * sound;

	vector<LPGAMEOBJECT> listAllObj;
	vector<LPGAMEOBJECT> listObj;

	vector <Items*> listItem;
	HitEffect * addHitEffect;
	vector <HitEffect*> listEffect;
	vector <CGameObject*> listEnemy;
	vector <Weapons*> listWeaponOfEnemy; // list chứa các viên đạn của enemy

	CGameTime * gameTime;

	int stateGame;

	bool gameOver;
	FontGame option;
	Load_resources * optionHeart;
	int optionSelect;

	DWORD FirstTimeGenGhost;
	bool isFirstGhost;
	int CountEnemyGhost; 
	DWORD TimeCreateGhost; 
	DWORD TimeWaitProcessCreateGhost; 
	bool isGenerateGhost; 
	bool isExistGhost; 
	int countGhostBorn = 0; 

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
	bool isDone;

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
	void CheckCollisionSimonWithHidenObject();
	void CheckCollisionSimonWithGate();

	void DropItem();

	void ResetResource(); // reset lai resource khi simon mất 1 mạng

	Items * GetRandomItem(int Id, def_ID Type, float X, float Y);
};