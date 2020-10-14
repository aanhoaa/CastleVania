#pragma once
#include "Load_img_file.h"
#include "Load_resources.h"
#include "Camera.h"
#include "FontGame.h"
#include "define.h"
#include "Simon.h"
#include "HeartPoint.h"

class BoardGame
{
private:
	Load_img_file * texture;
	Load_resources * sprite;

	int x, y;

	FontGame font;
	HeartPoint heartPoint;
public:
	BoardGame(int X, int Y);
	void Render(Camera *camera, Simon *simon);
	~BoardGame();
};
