#pragma once
#include "define.h"
#include "Load_img_file.h"

class BBox
{
private:
	Load_img_file * texture_BBox;
public:
	static BBox * __instance;
	static BBox * GetInstance();
	BBox();
	~BBox();
	LPDIRECT3DTEXTURE9 GetTexture();
};

