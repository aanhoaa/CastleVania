#include "HidenObject.h"



HidenObject::HidenObject(int X, int Y, int _width, int _height)
{
	x = (float)X;
	y = (float)Y;
	width = _width;
	height = _height;
	obj_type = def_ID::HIDDENOBJECT;
	id = 0; // set sau
	hp = 1;
}

HidenObject::~HidenObject()
{
}

void HidenObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void HidenObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void HidenObject::Render(Camera * camera)
{

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}