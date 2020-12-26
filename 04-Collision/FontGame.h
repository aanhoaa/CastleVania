#pragma once

#include "Load_img_file.h"
#include "Load_resources.h"
#include "define.h"
#include "LoadTexture.h"

class FontGame
{
private:
	Load_img_file * texture;
	Load_resources * sprite;

public:
	FontGame();
	~FontGame();
	void Draw(int x, int y, string s);
};