#include "Dagger.h"

Dagger::Dagger()
{
	texture = new Load_img_file("Resources\\weapon\\1.png");
	sprite = new Load_resources(texture, 0);
	obj_type = def_ID::DAGGER;
}


Dagger::~Dagger()
{
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;

	x += dx;

	// xử lí ra khỏi cam thì xóa
}

void Dagger::Create(float simonX, float simonY, int simonTrend)
{
	Weapons::Create(simonX, simonY + 10, simonTrend);
	vx = DAGGER_SPEED * nx;
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

	return isCollitionAll(obj);
}

void Dagger::RenderItem(int X, int Y)
{
	sprite->DrawFlipX(X, Y);
}

void Dagger::Render(Camera * camera)
{
	// ra khỏi cam coi như kết thúc
	// lẽ ra viết trong hàm update, nhưng ko có camera nên viết tạm ở đây
	if (x - camera->GetX_cam() + sprite->_texture->FrameWidth < 0 || x - camera->GetX_cam() > camera->GetWidth())
	{
		isFinish = true;
		return;
	}

	Weapons::Render(camera);
}