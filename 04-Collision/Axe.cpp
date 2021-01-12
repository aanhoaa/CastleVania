#include "Axe.h"

Axe::Axe(Camera * _camera)
{
	obj_type = def_ID::AXE;
	texture = LoadTexture::GetInstance()->GetTexture(def_ID::AXE);
	sprite = new Load_resources(texture, 70);

	texture_item = LoadTexture::GetInstance()->GetTexture(iAXE);
	sprite_item = new Load_resources(texture_item, 200);

	isFinish = true;
	this->camera = _camera;
}


Axe::~Axe()
{
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!camera->isObjectInCamera(x, y, (float)GetWidth(), (float)GetHeight())) // xử lí ra khỏi cam thì kết thúc
	{
		isFinish = true;
		return;
	}

	Weapons::Update(dt); //update dt dx d 
	dy = vy * dt;
	vy += AXE_GRAVITY * dt;

	y += dy;
	x += dx;

	sprite->Update(dt);

	Weapons::CheckCollision(coObjects);
}

void Axe::Create(float simon_X, float simon_Y, int simon_nx)
{
	if (isFinish == false)
		return;
	Weapons::Create(simon_X, simon_Y, simon_nx);
	UpdatePositionFitSimon();
	vx = AXE_SPEED_X * simon_nx;
	vy = -AXE_SPEED_Y;

	//Sound::GetInstance()->Play(eSound::soundAxe, true);
}

void Axe::RenderItem(int X, int Y)
{
	sprite_item->Draw(X, Y);
}

void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
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

void Axe::UpdatePositionFitSimon()
{
	y += 20;
}

bool Axe::isCollision(CGameObject * obj)
{
	return Weapons::isCollision(obj);
}

void Axe::Render(Camera * camera)
{
	if (!camera->isObjectInCamera(x, y, (float)texture->FrameWidth, (float)texture->FrameHeight))
		isFinish = true;

	if (isFinish)
		return;

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