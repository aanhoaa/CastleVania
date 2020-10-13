#include "Items.h"


Items::Items()
{
	TimeDisplayed = 0;
	isFinish = 0;
}

Items::~Items()
{
}

void Items::Update(DWORD dt, vector<CGameObject*> *listObject)
{
}

void Items::Render(Camera * camera)
{
	if (isFinish == true)
		return;

	D3DXVECTOR2 pos = camera->Translate(x, y);

	sprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

bool Items::GetFinish()
{
	return isFinish;
}

void Items::SetFinish(bool _isFinish)
{
	isFinish = _isFinish;
}