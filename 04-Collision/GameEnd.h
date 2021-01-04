#pragma once
#include "BoardGame.h"
#include "LoadTexture.h"
#include "Load_resources.h"
#include "ObjectEnd.h"
#include "Camera.h"

class GameEnd : public Scenes
{
	Load_resources * Sprite_Castle;

	CastleTop * castle;
	Camera * camera;
	FontGame TextInfor;
	Simon * simon;

public:
	GameEnd();
	virtual ~GameEnd();
	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();
	void Update(DWORD dt);
	void Render();
};

