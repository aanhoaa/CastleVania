#include "EnemyBullet.h"



EnemyBullet::EnemyBullet()
{
	obj_type = def_ID::ENEMYBULLET;
	texture = LoadTexture::GetInstance()->GetTexture(def_ID::ENEMYBULLET);
	sprite = new Load_resources(texture, 0);

	isFinish = true;
}


EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update(DWORD dt, Simon *simon)
{
	if (isFinish)
		return;

	Weapons::Update(dt); // update dt,dx,dy 

	x += dx;
	y += dy;

	CheckCollision(simon);
}

void EnemyBullet::Create(float X, float Y, int _nx)
{
	Weapons::Create(X, Y, _nx);
	vx = EnemyBullet_SPEED * nx;
}

void EnemyBullet::CustomCreate(float X, float Y, int _nx, float _vx, float _vy)
{
	Weapons::Create(X, Y, _nx);
	vx = _vx;
	vy = _vy;
}

void EnemyBullet::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void EnemyBullet::RenderItem(int X, int Y)
{
}

bool EnemyBullet::isCollision(CGameObject * obj)
{
	// dt, dx, dy đã update
	CGameObject *gameObj = dynamic_cast<CGameObject*>(obj);
	if (gameObj->GetLife() <= 0) // vật này die rồi thì ko va chạm
		return false;

	return isCollitionAll(obj);
}

void EnemyBullet::Render(Camera * camera)
{
	if (isFinish)
		return;

	if (x + sprite->_texture->FrameWidth < camera->GetX_cam() ||
		x > camera->GetX_cam() + camera->GetWidth() ||

		y + sprite->_texture->FrameHeight < camera->GetY_cam() ||
		y > camera->GetY_cam() + camera->GetHeight()

		)
	{
		isFinish = true;
		return;
	}

	Weapons::Render(camera);
}

void EnemyBullet::CheckCollision(Simon * simon)
{
	if (this != NULL && !this->GetFinish())
	{
		if (isCollitionAll(simon))
		{
			LPCOLLISIONEVENT e = isCollitionAllReturnE(simon);
			simon->SetEnemyHit(e);
			this->SetFinish(true);
			return;
		}
	}
}