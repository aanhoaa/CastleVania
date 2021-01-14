#include "Items.h"


Items::Items(def_ID item, float X, float Y)
{
	texture = LoadTexture::GetInstance()->GetTexture(item);
	sprite = new Load_resources(texture, 100);
	obj_type = item;

	this->x = x_before = X;
	this->y = Y;

	if (item == def_ID::SMALLHEART)
	{
		vx = 0.05f;
		vy = 0.04f;
	}
	else vy = ITEM_GRAVITY;

	TimeDisplayed = 0;
	TimeWaited = 0;
	isFinish = 0;
	TimeDisplayed = 0;
	TimeDisplayMax = ITEM_TIMEDISPLAYMAX;
}

Items::~Items()
{
}

void Items::Update(DWORD dt, vector<LPGAMEOBJECT> *listObject)
{
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

	if (GetType() == def_ID::SMALLHEART)
	{
		if (x - x_before >= 25)
		{
			vx = -0.05f;
		}
		else
		{
			if (x - x_before <= -25)
			{
				vx = 0.05f;
			}
		}
	}

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();

	for (UINT i = 0; i < listObject->size(); i++)
		if (listObject->at(i)->GetType() == def_ID::BRICK)
			listObject_Brick.push_back(listObject->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&listObject_Brick, coEvents); 

	if (coEvents.size() == 0)
	{
		y += dy;

		if (GetType() == def_ID::SMALLHEART)
			x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.4f;

		if (ny != 0)
		{
			vy = 0;
			vx = 0;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Items::Render(Camera * camera)
{
	if (TimeWaited < TIMEWAITMAX) // hết timewaitmax thì mới cho item render
		return;

	D3DXVECTOR2 pos = camera->Translate(x, y);

	sprite->Draw((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

bool Items::isWaiting()
{
	return TimeWaited < TIMEWAITMAX;
}

bool Items::GetFinish()
{
	return isFinish;
}

void Items::SetFinish(bool _isFinish)
{
	isFinish = _isFinish;
}

void Items::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}
