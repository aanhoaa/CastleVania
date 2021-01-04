#include "Weapons.h"


Weapons::Weapons()
{
	isFinish = 1;
	isSend = 0;
}

Weapons::~Weapons()
{
}

void Weapons::Create(float X, float Y, int _nx)
{
	this->x = X;
	this->y = Y;
	this->nx = _nx;
	isFinish = 0;
	isSend = 0;
}

void Weapons::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	//dy = vy * dt;
}

void Weapons::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
	
	//DebugOut(L"Weapons: index = %d \n", sprite->GetIndex());
	D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);
}

void Weapons::SetPosition(float X, float Y)
{
	this->x = X;
	this->y = Y;
}

void Weapons::UpdatePositionFitSimon()
{
}

bool Weapons::GetFinish()
{
	return isFinish;
}

void Weapons::SetFinish(bool _isFinish)
{
	isFinish = _isFinish;
}

bool Weapons::GetSend()
{
	return isSend;
}

void Weapons::SetSend(bool _isSend)
{
	isSend = _isSend;
}
