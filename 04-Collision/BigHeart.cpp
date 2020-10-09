#include "BigHeart.h"

BigHeart::BigHeart()
{
	texture = new Load_img_file("Resources\\item\\1.png");
	sprite = new Load_resources(texture, 100);
}

BigHeart::BigHeart(float X, float Y) : BigHeart()
{
	this->x = X;
	this->y = Y;
	vy = LARGEHEART_GRAVITY;
	TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
}

void BigHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void BigHeart::Update(DWORD dt, CGameObject * listObject)
{
}

void BigHeart::Render(Camera * camera)
{
}

BigHeart::~BigHeart()
{
}
