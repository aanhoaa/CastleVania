#include "Candle.h"
#include "debug.h"

Candle::Candle(int X, int Y)
{
	int candle = Data::GetInstance()->scene;

	if (candle == 1)
	{
		texture = LoadTexture::GetInstance()->GetTexture(BIGCANDLE);
		sprite = new Load_resources(texture, 100);
		this->x = (float)X;
		this->y = (float)Y;
		obj_type = def_ID::BIGCANDLE;
		life = 1;
	}
	else
	{
		texture = LoadTexture::GetInstance()->GetTexture(SMALLCANDLE);
		sprite = new Load_resources(texture, 100);
		this->x = (float)X;
		this->y = (float)Y;
		obj_type = def_ID::SMALLCANDLE;
		life = 1;
	}
}

Candle::~Candle()
{
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	sprite->Update(dt); // update animation
}

void Candle::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Translate(x, y);
	sprite->Draw((int)pos.x, (int)pos.y);
}
