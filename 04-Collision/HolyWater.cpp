#include "HolyWater.h"



HolyWater::HolyWater()
{
	obj_type = def_ID::HOLYWATER;
	texture = LoadTexture::GetInstance()->GetTexture(HOLYWATER);
	sprite = new Load_resources(texture, 70);
	
	texture_item = LoadTexture::GetInstance()->GetTexture(iHOLYWATER);
	sprite_item = new Load_resources(texture_item, 200);

	isCollisionBrick = false;
	isFinish = true;
}

HolyWater::~HolyWater()
{

}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish)
		return;

	if (sprite->GetIndex() == 3) 
	{
		countSprite++;
		if (countSprite == 2)
			isFinish = true;
		else
		{
			sprite->SelectIndex(1);
		}
	}

	Weapons::Update(dt); //update dt dx d
	if (!isCollisionBrick)
		vy += HOLYWATER_GRAVITY * dt;

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == def_ID::BRICK)
			listObject_Brick.push_back(coObjects->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm 
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0)
		{
			vy = 0;
			vx = 0;
			isCollisionBrick = true;
		}

		if (ny != 0)
		{
			vy = 0;
			vx = 0;
			isCollisionBrick = true;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void HolyWater::Create(float simon_X, float simon_Y, int simon_nx)
{
	if (!isFinish)
		return;

	Weapons::Create(simon_X, simon_Y, simon_nx);

	UpdatePositionFitSimon();

	vx = HOLLYWATER_SPEED_X * simon_nx;
	vy = -HOLLYWATER_SPEED_Y;
	isCollisionBrick = false;
	sprite->SelectIndex(0);
	countSprite = 0;

	Sound::GetInstance()->Play(eSound::sHollyWater);
}

void HolyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - 5;
	top = y;
	right = x + texture->FrameWidth + 5;
	bottom = y + texture->FrameHeight;

	if (sprite->GetIndex() == 0) // frame đầu
	{
		left += 5;
		top += 5;
		right -= 5;
		bottom -= 0;
	}
}

void HolyWater::UpdatePositionFitSimon()
{
	y += 20;
}

void HolyWater::RenderItem(int X, int Y)
{
	sprite_item->Draw(X, Y);
}

bool HolyWater::isCollision(CGameObject * obj)
{
	if (isFinish)
		return false;
	// dt, dx, dy đã update
	CGameObject *gameObj = dynamic_cast<CGameObject*>(obj);
	if (gameObj->GetLife() <= 0) // vật này die rồi thì ko va chạm
		return false;

	return isCollitionAll(obj);
}

void HolyWater::Render(Camera * camera)
{
	if (!camera->isObjectInCamera(x, y, (float)texture->FrameWidth, (float)texture->FrameHeight))
		isFinish = true;

	if (isFinish)
		return;

	if (isCollisionBrick) // chạm đất r thì mới update ani
		sprite->Update(dt);

	D3DXVECTOR2 pos = camera->Translate(x, y);

	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
	{
		RenderBoundingBox(camera);
	}
}