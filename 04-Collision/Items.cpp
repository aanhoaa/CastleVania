#include "Items.h"


Items::Items()
{
	TimeDisplayed = 0;
	TimeWaited = 0;
	isFinish = 0;
}

Items::~Items()
{
}

void Items::Update(DWORD dt, vector<CGameObject*> *listObject)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;

	if (TimeWaited < TIMEWAITMAX) // hết timewaitmax thì item mới dc update
	{
		TimeWaited += dt;
		return;
	}
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

bool Items::isWaitingDisplay()
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

/* Whip */
Whip::Whip(float X, float Y) 
{
	texture = new Load_img_file("Resources\\item\\3.png");
	sprite = new Load_resources(texture, 100);
	obj_type = def_ID::UPGRADEMORNINGSTAR;

	this->x = X;
	this->y = Y;
	vy = UPGRADEMORNINGSTAR_GRAVITY;
	TimeDisplayed = 0;
	TimeDisplayMax = UPGRADEMORNINGSTAR_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeWaited = 0;
	TimeWaitMax = UPGRADEMORNINGSTAR_TIMEWAITMAX;
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> * listObject)
{
	if (TimeWaited < TIMEWAITMAX)
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

	Items::Update(dt); // Update dt, dx, dy

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

Whip::~Whip()
{
}

/* Dagger*/
iDagger::iDagger(float X, float Y)
{
	texture = new Load_img_file("Resources\\item\\4.png");
	sprite = new Load_resources(texture, 0);
	obj_type = def_ID::iDAGGER;

	this->x = X;
	this->y = Y;
	vy = ITEMDAGGER_GRAVITY;
	TimeDisplayMax = ITEMDAGGER_TIMEDISPLAYMAX;
	/*TimeWaited = 0;
	TimeWaitMax = ITEMDAGGER_TIMEWAITMAX;*/
}

void iDagger::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight /*- 18*/;
}

void iDagger::Update(DWORD dt, vector<LPGAMEOBJECT> *listObject)
{
	if (TimeWaited < TIMEWAITMAX)
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

	Items::Update(dt); // Update dt, dx, dy

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < listObject->size(); i++)
		if (listObject->at(i)->GetType() == def_ID::BRICK)
			listObject_Brick.push_back(listObject->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm

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

iDagger::~iDagger()
{
}

/* Money Bag*/
MoneyBag::MoneyBag(float X, float Y)
{
	texture = new Load_img_file("Resources\\item\\2.png", 3, 1, 3, 0);
	sprite = new Load_resources(texture, 100);

	this->x = X;
	this->y = Y;
	obj_type = def_ID::MONNEYBAG;

	vx = 0;
	vy = 0;

	vy = MONEY_GRAVITY; // tam thoi

	TimeDisplayMax = MONEY_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
}

MoneyBag::~MoneyBag()
{
}

void MoneyBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;

}

void MoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (TimeWaited < TimeWaitMax)
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

	Items::Update(dt); // Update dt, dx, dy

	sprite->Update(dt);

					  // tam cho money roi xuong



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