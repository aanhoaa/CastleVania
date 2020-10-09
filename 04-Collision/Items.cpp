#include "Items.h"


Items::Items()
{
	vx = 0;
	vy = 0;
	TimeDisplayed = 0;
}

Items::~Items()
{
	SAFE_DELETE(sprite);
	SAFE_DELETE(texture);

}

void Items::Update(DWORD dt, vector<CGameObject*> *listObject)
{
}

void Items::Render(Camera * camera)
{

	D3DXVECTOR2 pos = camera->Translate(x, y);

	sprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void Items::SetPosition(float X, float Y)
{
	this->x = X;
	this->y = Y;
}

def_ID Items::GetType()
{
	return type;
}

void Items::RenderBoundingBox(Camera * camera)
{
	RECT rect;
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;
	D3DXVECTOR2 pos = camera->Translate(l, t);
	LPDIRECT3DTEXTURE9  _Texture = BBox::GetInstance()->GetTexture();
	CGame::GetInstance()->Draw(pos.x, pos.y, _Texture, rect.left, rect.top, rect.right, rect.bottom, 100);

}

bool Items::GetFinish()
{
	return isFinish;
}