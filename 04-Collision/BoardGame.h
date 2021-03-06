#pragma once
#include "Load_img_file.h"
#include "Load_resources.h"
#include "Camera.h"
#include "FontGame.h"
#include "define.h"
#include "Simon.h"
#include "HeartPoint.h"
#include "Dagger.h"
#include "LoadTexture.h"
#include "Enemy.h"

class BoardGame
{
private:
	Load_img_file * texture;
	Load_resources * sprite;

	int x, y;

	FontGame font;
	HeartPoint heartPoint;
	string Show(string s, UINT MaxNumber);
public:
	BoardGame(int X, int Y);
	void Render(Simon *simon, int  _hpBoss, int TimeRemaining, Weapons *weap, int stage);
	~BoardGame();
};
