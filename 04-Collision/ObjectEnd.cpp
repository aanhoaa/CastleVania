#include "ObjectEnd.h"

CastleTop::CastleTop(float X, float Y)
{
	obj_type = def_ID::TOPCASTLE;
	texture = LoadTexture::GetInstance()->GetTexture(TOPCASTLE);
	sprite = new Load_resources(texture, 50);

	this->x = X;
	this->y = Y;
	this->nx = 1;
	this->life = 1;
	isActive = 0;
	time = 0;
	isDown = 0;
	endGame = 0;
}

CastleTop::~CastleTop()
{
}

void CastleTop::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (life < 1)
		return;

	CGameObject::Update(dt); // Update dt, dx, dy
	y += dy;
	x += dx;

	sprite->Update(dt);

	if (isActive)
	{
		if (isDown)
		{
			sprite->Reset();
			isDown = 0;
		}

		vy = 0.02f;
		sprite->Update(dt);
		if (sprite->GetIndex() == 1)
			sprite->SelectIndex(2);
	}
	else
	{
		if (sprite->GetIndex() > 1)
		sprite->SelectIndex(0);
		isDown = 1;
	}
}

void CastleTop::Render(Camera * camera)
{
	if (life < 1)
		return;
	camera->SetPosition(0, 0);
	D3DXVECTOR2 pos = camera->Translate(x, y);

	if (isActive)
	{
		if ((int)y + texture->FrameHeight - 213 < texture->FrameHeight)
		{
			sprite->DrawS((int)pos.x, (int)pos.y, (int)abs(y + texture->FrameHeight - 213), 2);
		}
		else
		{
			endGame = 1;
		}
	}
	else
	{
			sprite->DrawS((int)pos.x, (int)pos.y, 0, 2);
	}

	/*if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);*/
}

void CastleTop::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

bool CastleTop::GetActive()
{
	return isActive;
}

void CastleTop::SetActive(bool _isActive)
{
	isActive = _isActive;
}

bool CastleTop::GetEndGame()
{
	return endGame;
}