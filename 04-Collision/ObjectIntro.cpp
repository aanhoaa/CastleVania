#include "ObjectIntro.h"

/* Bat intro*/
BatIntro::BatIntro(float X, float Y, float VX, float VY, int _typeBat)
{
	obj_type = def_ID::INTRO_BAT;
	texture = LoadTexture::GetInstance()->GetTexture(INTRO_BAT);
	sprite = new Load_resources(texture, 70);

	typeBat = _typeBat;
	this->x = X;
	this->y = Y;
	this->nx = -1;
	this->life = 1;

	vy = VY;
	vx = VX;
}

BatIntro::~BatIntro()
{
}

void BatIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (life < 1)
		return;

	CGameObject::Update(dt); // Update dt, dx, dy
	y += dy;
	x += dx;

	sprite->Update(dt);

	if (typeBat == 2)
	{
		if (x <= 233)
		{
			vx = 0;
			vy = -0.0134f;
		}
	}
}

void BatIntro::Render(Camera * camera)
{
	if (life < 1)
		return;

	D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void BatIntro::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

/* HelicopterIntro intro*/
HelicopterIntro::HelicopterIntro(float X, float Y)
{
	obj_type = def_ID::HELICOPTER;
	texture = LoadTexture::GetInstance()->GetTexture(HELICOPTER);
	sprite = new Load_resources(texture, 70);

	this->x = X;
	this->y = Y;
 	this->nx = -1;
	this->life = 1;

	vy = -HELICOPTER_SPEED_Y;
	vx = HELICOPTER_SPEED_X * nx;
}

HelicopterIntro::~HelicopterIntro()
{
}

void HelicopterIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (life < 1)
		return;

	CGameObject::Update(dt); // Update dt, dx, dy

	y += dy;
	x += dx;
}

void HelicopterIntro::Render(Camera * camera)
{
	if (life < 1)
		return;

	D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void HelicopterIntro::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}