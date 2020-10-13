#include "BigHeart.h"

BigHeart::BigHeart()
{
	texture = new Load_img_file("Resources\\item\\1.png");
	sprite = new Load_resources(texture, 100);
	obj_type = def_ID::BIGHEART;
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

void BigHeart::Update(DWORD dt, vector<LPGAMEOBJECT> * listObject)
{
	TimeDisplayed += dt;
	if (TimeDisplayed >= TimeDisplayMax)
	{
		isFinish = true;
		return;
	}

	dy = vy * dt;

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();

	for (int i = 0; i < listObject->size(); i++)
		if (listObject->at(i)->GetType() == def_ID::BRICK)
			listObject_Brick.push_back(listObject->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm

														  // No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.4f;

		if (ny != 0)
		{
			vy = 0;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void BigHeart::SetReward()
{
	Data::GetInstance()->HeartCollect += 5;
	DebugOut(L"[ITEM] +5 Heart. Tong = %d \n", Data::GetInstance()->HeartCollect);
}

BigHeart::~BigHeart()
{
}
