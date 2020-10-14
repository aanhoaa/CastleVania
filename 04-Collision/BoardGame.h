#pragma once
#include "Load_img_file.h"
#include "Load_resources.h"
#include "Camera.h"
#include "FontGame.h"
#include "define.h"

class BoardGame
{
private:
	Load_img_file * texture;
	Load_resources * sprite;

	int x, y;

	FontGame font;
	string information;

public:
	BoardGame(int X, int Y);
	void Render(Camera *camera);
	~BoardGame();
};
