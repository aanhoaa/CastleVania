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
	D3DXVECTOR2 pos = camera->Translate(x, y);
	sprite->Draw(pos.x, pos.y);

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
	texture = new Load_img_file("Resources\\other\\0.png", 2, 1, 2, 0);
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
Effect::Effect(int X, int Y)
{
	this->x = X;
	this->y = Y;
	texture = new Load_img_file("Resources\\other\\1.png", 4, 1, 4, 0);
	sprite = new Load_resources(texture, 150);
}


Effect::~Effect()
{
}

void Effect::Update(DWORD dt)
{
	HitEffect::Update(dt);
	if (sprite->GetIndex() == 3) // nếu là frame cuối thì xong, frame cuối trống
		isFinish = true;
}