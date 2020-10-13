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


//void Weapons::RenderBoundingBox(Camera * camera)
//{
//	RECT rect;
//
//	float l, t, r, b;
//
//	GetBoundingBox(l, t, r, b);
//	rect.left = 0;
//	rect.top = 0;
//	rect.right = (int)r - (int)l;
//	rect.bottom = (int)b - (int)t;
//
//	D3DXVECTOR2 pos = camera->Translate(l, t);
//
//	LPDIRECT3DTEXTURE9  _Texture = BBox::GetInstance()->GetTexture();
//
//	CGame::GetInstance()->Draw(pos.x, pos.y, _Texture, rect.left, rect.top, rect.right, rect.bottom, 100);
//}