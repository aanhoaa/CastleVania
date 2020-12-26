#pragma once
#include "LoadTexture.h"
#include "Load_resources.h"
#include "BoardGame.h"
#include "Simon.h"
#include "Camera.h"
#include "Brick.h"
#include "ObjectIntro.h"

#include "Scene11.h"


#define INTRO_STATUS_PROCESS_MENU 0 
#define INTRO_STATUS_PROCESS_GO_SCENE1 1 


class GameIntro : public Scenes
{
private:
	Load_resources * Sprite_MainMenu;
	Load_resources* Sprite_IntroBatMenu;
	Load_resources* Sprite_IntroGoScene1;

	FontGame TextPressStart;
	FontGame TextInfor;

	/*Xử lí nhấn phím thì tiếp tục*/
	bool isPressStart;
	DWORD TimeWaited;

	/* Xử lí nhấp nháy TextPressStart */
	bool isDrawTextPressStart;
	DWORD TimeWaitedToChangeDisplayTextPressStart;

	int StatusProcess;

	Simon * simon;
	BoardGame * board;
	Camera * camera;
	vector<LPGAMEOBJECT> listBrick;

	HelicopterIntro * heliCopter;
	BatIntro * introBat1;
	BatIntro * introBat2;

public:
	GameIntro();
	virtual ~GameIntro();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();
	void Update(DWORD dt);
	void Render();
};