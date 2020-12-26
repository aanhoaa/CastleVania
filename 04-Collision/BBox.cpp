#include "BBox.h"

BBox * BBox::__instance = NULL;

BBox * BBox::GetInstance()
{
	if (__instance == NULL)
		__instance = new BBox();
	return __instance;
}

BBox::BBox()
{
	texture_BBox = LoadTexture::GetInstance()->GetTexture(RENDERBOX);
}


BBox::~BBox()
{
	SAFE_DELETE(__instance);

}

LPDIRECT3DTEXTURE9 BBox::GetTexture()
{
	return texture_BBox->Texture;
}