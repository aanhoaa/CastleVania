#pragma once
#include "Load_img_file.h"
#include "Load_resources.h"
#include "define.h"
#include "LoadTexture.h"

#define BOARDHEALTH_MAX_CELL 16

#define BOARDHEALTH_FRAME_PLAYER 0
#define BOARDHEALTH_FRAME_NONE 1
#define BOARDHEALTH_FRAME_ENEMY 2

class HeartPoint
{
private:
	Load_img_file * texture;
	Load_resources * sprite;

public:
	HeartPoint();
	~HeartPoint();
	void Draw(int x, int y, int HealthPlayer, int HealthEnemy);
};

