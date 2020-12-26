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
	texture = LoadTexture::GetInstance()->GetTexture(UPGRADEMORNINGSTAR);
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
	Items::Update(dt, listObject);
}

Whip::~Whip()
{
}

/* Dagger*/
iDagger::iDagger(float X, float Y)
{
	texture = LoadTexture::GetInstance()->GetTexture(iDAGGER);
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

	Items::Update(dt, listObject); // Update dt, dx, dy

}

iDagger::~iDagger()
{
}

/* Money Bag*/
MoneyBag::MoneyBag(float X, float Y)
{
	texture = LoadTexture::GetInstance()->GetTexture(MONNEYBAG);
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
	Items::Update(dt, listObject);
}

/* Holy water */
iHolyWater::iHolyWater(float X, float Y)
{
	obj_type = def_ID::iHOLYWATER;
	texture = LoadTexture::GetInstance()->GetTexture(iHOLYWATER);
	sprite = new Load_resources(texture, 0);
	
	this->x = X;
	this->y = Y;
	vy = ITEMHOLYWATER_GRAVITY;
	TimeDisplayMax = ITEMHOLYWATER_TIMEDISPLAYMAX;
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = ITEMHOLYWATER_TIMEWAITMAX;
}

iHolyWater::~iHolyWater()
{
}

void iHolyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void iHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	Items::Update(dt, listObject);
}

//
PotRoast::PotRoast(float X, float Y)
{
	obj_type = def_ID::POTROAST;
	texture = LoadTexture::GetInstance()->GetTexture(def_ID::POTROAST);
	sprite = new Load_resources(texture, 100);

	x = X;
	y = Y;
	life = 1;

	vy = POTROAST_GRAVITY;
	TimeDisplayMax = POTROAST_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = POTROAST_TIMEWAITMAX;
}

PotRoast::~PotRoast()
{
}

void PotRoast::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void PotRoast::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	Items::Update(dt, listObject);
}

/* Axe */
iAxe::iAxe(float X, float Y)
{
	texture = LoadTexture::GetInstance()->GetTexture(def_ID::iAXE);
	sprite = new Load_resources(texture, 0);
	obj_type = def_ID::iAXE;

	this->x = X;
	this->y = Y;
	vy = ITEMTHROWINGAXE_GRAVITY;
	TimeDisplayMax = ITEMTHROWINGAXE_TIMEDISPLAYMAX;
	TimeDisplayed = 0;
	TimeWaited = 0;
	TimeWaitMax = ITEMTHROWINGAXE_TIMEWAITMAX;
}

void iAxe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void iAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	Items::Update(dt, listObject);
}

iAxe::~iAxe()
{
}

/* Magic Crystal */
MagicCrystal::MagicCrystal(int X, int Y)
{
	texture = LoadTexture::GetInstance()->GetTexture(def_ID::MAGICCRYSTAL);
	sprite = new Load_resources(texture, 100);

	x = X;
	y = Y;
	life = 1;
	obj_type = def_ID::MAGICCRYSTAL;

	vy = MAGICCRYSTAL_GRAVITY;
	TimeWaited = 0;
	TimeWaitMax = MAGICCRYSTAL_TIMEWAITMAX;

}

void MagicCrystal::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (isWaitingDisplay())
	{
		TimeWaited += dt;
		return;
	}

	CGameObject::Update(dt, listObject);

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

void MagicCrystal::Render(Camera * camera)
{
	if (isWaitingDisplay())
	{
		return;
	}

	D3DXVECTOR2 pos = camera->Translate(x, y);

	sprite->Draw((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

MagicCrystal::~MagicCrystal()
{
}

void MagicCrystal::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}