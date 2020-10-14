#pragma once

#include "Load_img_file.h"
#include "Load_resources.h"
#include "define.h"


class FontGame
{
private:
	Load_img_file * texture;
	Load_resources * sprite;

public:
	FontGame();
	~FontGame();
	void Draw(float x, float y, string s);
};