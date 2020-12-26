#include "Dagger.h"

Dagger::Dagger()
{
	obj_type = def_ID::DAGGER;
	texture = LoadTexture::GetInstance()->GetTexture(DAGGER);
	sprite = new Load_resources(texture, 0);
}


Dagger::~Dagger()
{
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Weapons::Update(dt); // update dt,dx,dy

	x += dx;
}

void Dagger::Create(float simonX, float simonY, int simonTrend)
{
	Weapons::Create(simonX, simonY + 10, simonTrend);
	vx = DAGGER_SPEED * nx;
	Sound::GetInstance()->Play(eSound::sDagger);
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

bool Dagger::isCollision(CGameObject * obj)
{
	// dt, dx, dy đã update
	CGameObject *gameObj = dynamic_cast<CGameObject*>(obj);
	if (gameObj->GetLife() <= 0) 
		return false;

	return isCollitionAll(obj);
}

void Dagger::RenderItem(int X, int Y)
{
	sprite->DrawFlipX(X, Y);
}

void Dagger::Render(Camera * camera)
{
	if (isFinish)
		return;

	if (x - camera->GetX_cam() + sprite->_texture->FrameWidth < 0 || 
		x - camera->GetX_cam() > camera->GetWidth())
	{
		isFinish = true;
		return;
	}

	Weapons::Render(camera);
}