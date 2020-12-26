#ifndef __SCENE_1_H__
#define __SCENE_1_H__

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
#include "Scene12.h"
#include "Data.h"

#define GAME_TIME_SCENE1 300

class Scene_1 : public Scenes
{
	bool isPassScene;
public:
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
	Scene_1();
	~Scene_1();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();

	void ResetResource(); // reset lai resource khi simon mất 1 mạng

	void CheckCollision();
	void CheckCollisionWeapon();
	void CheckCollisionSimonWithItem();
	void CheckCollisionSimonWithHidenObject();

	Items * GetNewItem(int Id, def_ID Type, float X, float Y);
};

#endif