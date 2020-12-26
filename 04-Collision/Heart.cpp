#include "Heart.h"

BigHeart::BigHeart(float X, float Y)
{
	texture = LoadTexture::GetInstance()->GetTexture(BIGHEART);
	sprite = new Load_resources(texture, 100);
	obj_type = def_ID::BIGHEART;

	this->x = X;
	this->y = Y;
	vy = LARGEHEART_GRAVITY;
	TimeDisplayed = 0;
	TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	
	//TimeWaited = 0;
	//TimeWaitMax = LARGEHEART_TIMEWAITMAX; // set time chờ hit effect mới được collect
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
	Items::Update(dt, listObject);
}

BigHeart::~BigHeart()
{
}

/* small heart*/
SmallHeart::SmallHeart(float X, float Y)
{
	texture = LoadTexture::GetInstance()->GetTexture(SMALLHEART);
	sprite = new Load_resources(texture, 100);
	obj_type = def_ID::SMALLHEART;

	this->x = X;
	this->y = Y;
	this->rootX = X;

	TimeDisplayMax = SMALLHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

	vy = SMALLHEART_GRAVITY;
	vx = SMALLHEART_SPEED_X;
}

void SmallHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	//Items::Update(dt, listObject); // Update dt, dx, dy
	CGameObject::Update(dt, listObject);

	if (TimeWaited < TIMEWAITMAX) // hết timewaitmax thì item mới dc update
	{
		TimeWaited += dt;
		return;
	}

	TimeDisplayed += dt;
	if (TimeDisplayed >= TimeDisplayMax)
	{
		isFinish = true;
		return;
	}

	// vượt quá biên độ trục x cho phép thì đổi chiều vx
	if (x - rootX >= DeltaX)
	{
		vx = -SMALLHEART_SPEED_X;
	}
	else
		if (x - rootX <= -DeltaX)
		{
			vx = SMALLHEART_SPEED_X;
		}

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < listObject->size(); i++)
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
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.4f;

		if (ny != 0) // nếu chạm đất
		{
			vy = 0;
			vx = 0; 
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

SmallHeart::~SmallHeart()
{
}