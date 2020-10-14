#include "Weapons.h"


Weapons::Weapons()
{
	isFinish = 1;
}

Weapons::~Weapons()
{
}

//int Weapons::GetDirect()
//{
//	return nx;
//}
//
//void Weapons::SetDirect(int nx)
//{
//	this->nx = nx;
//}

void Weapons::Create(float simon_X, float simon_Y, int simon_nx)
{
	this->x = simon_X;
	this->y = simon_Y;
	this->nx = simon_nx;
	isFinish = 0;
}

void Weapons::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	sprite->Update(dt);
}

void Weapons::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
	
	//DebugOut(L"Weapons: index = %d \n", sprite->GetIndex());
	D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
}

void Weapons::SetPosition(float X, float Y)
{
	this->x = X;
	this->y = Y;
}

void Weapons::UpdatePositionFitSimon()
{
}

int Weapons::GetFinish()
{
	return isFinish;
}

void Weapons::SetFinish(bool _isFinish)
{
	isFinish = _isFinish;
}

Items * Weapons::GetItem(int Id, def_ID Type, float X, float Y)
{
	if (Type == def_ID::CANDLE)
	{
		if (Id == 1 || Id == 4)
			return new BigHeart(X, Y);
		if (Id == 2 || Id == 3)
			return new Whip(X, Y);
		return new BigHeart(X, Y);
	}
}