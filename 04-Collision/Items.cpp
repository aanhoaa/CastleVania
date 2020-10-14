#include "Items.h"


Items::Items()
{
	TimeDisplayed = 0;
	isFinish = 0;
}

Items::~Items()
{
}

void Items::Update(DWORD dt, vector<CGameObject*> *listObject)
{
}

void Items::Render(Camera * camera)
{
	if (isFinish == true)
		return;

	D3DXVECTOR2 pos = camera->Translate(x, y);

	sprite->Draw(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

bool Items::GetFinish()
{
	return isFinish;
}

void Items::SetFinish(bool _isFinish)
{
	isFinish = _isFinish;
}

Whip::Whip()
{
	texture = new Load_img_file("Resources\\item\\3.png");
	sprite = new Load_resources(texture, 100);
	obj_type = def_ID::UPGRADEMORNINGSTAR;
}

Whip::Whip(float X, float Y) : Whip()
{
	this->x = X;
	this->y = Y;
	vy = UPGRADEMORNINGSTAR_GRAVITY;
	TimeDisplayMax = UPGRADEMORNINGSTAR_TIMEDISPLAYMAX; // set time hiển thị tối đa

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

void Whip::SetReward()
{
	//chua viet
}


Whip::~Whip()
{
}