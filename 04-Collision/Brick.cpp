#include "Brick.h"


Brick::Brick(int X, int Y, int W, int H, int updateBrick)
{

	switch (updateBrick)
	{
	case 1:
		texture = LoadTexture::GetInstance()->GetTexture(BRICK_TYPE_1);
		break;
	case 2:
		texture = LoadTexture::GetInstance()->GetTexture(BRICK_TYPE_2);
		break;
	case 3:
		texture = LoadTexture::GetInstance()->GetTexture(BRICK_TYPE_3);
		break;
	case 4:  
		texture = LoadTexture::GetInstance()->GetTexture(BRICK_TRANSPARENT);
		break;
	case 5:
		texture = LoadTexture::GetInstance()->GetTexture(BRICK_3X32);
		break;
	case 6:
		texture = LoadTexture::GetInstance()->GetTexture(BRICK_4X32);
	default:
		break;
	}
	
	sprite = new Load_resources(texture, 1000);
	this->x = (float)X;
	this->y = (float)Y;
	this->width = W;
	this->height = H;
	obj_type = def_ID::BRICK;
}

void Brick::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Translate(x, y);

	for (int i = 0; i < (int)ceil(width / texture->FrameWidth); i++)
		for (int j = 0; j < (int)ceil(height / texture->FrameHeight); j++)
		{
			if (GetObj_id() != 125)
			sprite->Draw((int)pos.x + i * texture->FrameWidth, (int)pos.y + j * texture->FrameHeight);
			
		}

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + (float)ceil(width / texture->FrameWidth)*texture->FrameWidth;
	b = y + (float)ceil(height / texture->FrameHeight)*texture->FrameHeight;
}