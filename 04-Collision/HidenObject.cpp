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

/* Gate*/
Gate::Gate(int X, int Y)
{
	obj_type = def_ID::GATE;
	texture = LoadTexture::GetInstance()->GetTexture(GATE);
	sprite = new Load_resources(texture, 200);
	hp = 1;
	isOpen = 0;
	x = (float)X;
	y = (float)Y;
}

Gate::~Gate()
{
}

void Gate::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - 10;
	top = y;
	right = x;
	bottom = y + texture->FrameHeight;
}

void Gate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt); // update dt
}

void Gate::Render(Camera * camera)
{
	if (isOpen != 0)
	{
		int index = sprite->GetIndex();
		switch (isOpen)
		{
		case 1:
		{
			sprite->_timeLocal += dt;
			if (sprite->_timeLocal >= 800)
			{
				sprite->_timeLocal = 0;
				sprite->Next();
				isOpen++;
			}
			break;
		}
		case 2:
		{
			sprite->_timeLocal += dt;
			if (sprite->_timeLocal >= 200)
			{
				sprite->_timeLocal = 0;
				sprite->Next();
				isOpen++;
			}
			Sound::GetInstance()->Play(eSound::sOpenDoor);
			break;
		}
		case 3:
		{
			Data::GetInstance()->passGate = 1;

			sprite->_timeLocal += dt;
			if (sprite->_timeLocal >= 500)
			{
				sprite->_timeLocal = 0;
				sprite->SelectIndex(0);
				isOpen++;
			}
			break;
		}
		default:
			break;
		}
	}

	D3DXVECTOR2 pos = camera->Translate(x, y);
	sprite->Draw((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void Gate::Open()
{
	isOpen = 1;
}

int Gate::GetStart()
{
	return isOpen;
}