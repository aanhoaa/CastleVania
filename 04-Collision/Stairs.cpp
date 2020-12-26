#include "Stairs.h"



Stairs::Stairs(int X, int Y, int _stairType)
{
	stairType = _stairType;

	switch (stairType)
	{
		case BOTTOM_STAIR:
		{
			obj_type = def_ID::BOTTOMSTAIR;
			width = 50;
			height = 2;

			break;
		}
		case TOP_STAIR:
		{
			obj_type = def_ID::TOPSTAIR;
			width = 25;
			height = 10;
			
			break;
		}
	}

	x = (float)(X - 25);
	y = (float)(Y - height);
}

Stairs::~Stairs()
{
}

void Stairs::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + width;
	top = y;
	bottom = y + height;
}

void Stairs::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Stairs::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
