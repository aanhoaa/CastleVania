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


#define GAME_TIME_SCENE2 300


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
	CGameTime * gameTime;
public:
	Scene_2(Simon * _simon = NULL, CGameTime* _gameTime = NULL);
	~Scene_2();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();
	void Update(DWORD dt);
	void Render();

	void CheckCollision();
	void CheckCollisionWeapon();
	void CheckCollisionSimonWithItem();
	void CheckCollisionSimonWithHidenObject();

	void ResetResource(); // reset lai resource khi simon mất 1 mạng

	Items * GetNewItem(int Id, def_ID Type, float X, float Y);
};