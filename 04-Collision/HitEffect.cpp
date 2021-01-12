#include "HitEffect.h"



HitEffect::HitEffect()
{
	isFinish = 0;
}


HitEffect::~HitEffect()
{
	SAFE_DELETE(sprite);
}

void HitEffect::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Translate((float)x, (float)y);
	sprite->Draw((int)pos.x, (int)pos.y);

}

void HitEffect::Update(DWORD dt)
{
	sprite->Update(dt);
	if (sprite->GetIndex() == 4) // nếu là frame cuối thì xong, frame cuối trống
		isFinish = true;
}

bool HitEffect::GetFinish()
{
	return isFinish;
}

void HitEffect::SetFinish(int b)
{
	isFinish = b;
}

/* Hit*/
Hit::Hit(int X, int Y)
{
	this->x = X;
	this->y = Y;
	texture = LoadTexture::GetInstance()->GetTexture(HIT);
	sprite = new Load_resources(texture, 250);
}

Hit::~Hit()
{
}

void Hit::Update(DWORD dt)
{
	HitEffect::Update(dt);
	if (sprite->GetIndex() == 1) // nếu là frame cuối thì xong, frame cuối trống
		isFinish = true;
}

/* Effect */
Effect::Effect(int X, int Y, int _times)
{
	this->x = X;
	this->y = Y;
	texture = LoadTexture::GetInstance()->GetTexture(EFFECT);
	sprite = new Load_resources(texture, 150);
	times = _times;
}


Effect::~Effect()
{
}

void Effect::Update(DWORD dt)
{
	HitEffect::Update(dt);
	if (sprite->GetIndex() == 3) // nếu là frame cuối thì xong, frame cuối trống
	{
		times--;
		if (times == 0)
			isFinish = true;
		else sprite->timeLocal = sprite->timeAnimation;
	}
}

//
BrickSplash::BrickSplash(int X, int Y, int _direction)
{
	this->x = X;
	this->y = Y;
	dx = dy = vx = vy = 0;
	texture = LoadTexture::GetInstance()->GetTexture(def_ID::BRICKSPLASH);
	sprite = new Load_resources(texture, 200);
	direction = _direction;
	switch (direction)
	{
		case 1:
		{
			nx = -1;
			vx = nx * 0.15f;
			vy = -0.25f;
			break;
		}
		case 2:
		{
			nx = 1;
			vx = nx * 0.15f;
			vy = -0.2f;
			break;
		}
		case 3:
		{
			nx = -1;
			vx = nx * 0.07f;
			vy = -0.22f;
			break;
		}
		case 4:
		{
			nx = 1;
			vx = nx * 0.1f;
			vy = -0.3f;
			break;
		}
	}
}

void BrickSplash::Update(DWORD dt)
{
	this->dt = dt;
	this->dx = vx * dt;
	this->dy = vy * dt;

	vy += BRICKSPLASH_GRAVITY * dt;

	x += (int)dx;
	y += (int)dy;

	Effect::Update(dt);
	if (sprite->GetIndex() == sprite->lastFrame) // nếu là frame cuối thì xong,
		isFinish = true;
}


BrickSplash::~BrickSplash()
{
}

/* Water */
Water::Water(float X, float Y, int Model)
{
	texture = LoadTexture::GetInstance()->GetTexture(def_ID::WATER);
	sprite = new Load_resources(texture, 50);

	this->x = (int)X;
	this->y = (int)Y;
	dx = dy = vx = vy = 0;
	
	_model = Model;
	switch (_model)
	{
	case 1:
	{
		vy = -0.4f;
		vx = -0.04f;
		break;
	}
	case 2:
	{
		vy = -0.5f;
		vx = 0.0f;
		break;
	}
	case 3:
	{
		vy = -0.4f;
		vx = 0.1f;
		break;
	}
	}
}

Water::~Water()
{
}

void Water::Update(DWORD dt)
{
	this->dt = dt;
	this->dx = vx * dt;
	this->dy = vy * dt;

	vy += WATER_GRAVITY * dt;

	x += (int)dx;
	y += (int)dy;
}