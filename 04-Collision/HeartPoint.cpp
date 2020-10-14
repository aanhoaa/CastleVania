#include "HeartPoint.h"



HeartPoint::HeartPoint()
{
	texture = new Load_img_file("Resources\\heal.png", 3, 1, 3);
	sprite = new Load_resources(texture, 0);
}


HeartPoint::~HeartPoint()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(sprite);
}

void HeartPoint::Draw(int x, int y, int HealthPlayer, int HealthEnemy)
{
	int i, j;
	sprite->SelectIndex(BOARDHEALTH_FRAME_PLAYER);
	for (i = 0; i < HealthPlayer; i++)
		sprite->Draw(x + i * texture->FrameWidth, y);

	sprite->SelectIndex(BOARDHEALTH_FRAME_NONE);
	for (j = i; j<BOARDHEALTH_MAX_CELL; j++)
	{
		sprite->Draw(x + j * texture->FrameWidth, y);
	}

	sprite->SelectIndex(BOARDHEALTH_FRAME_ENEMY);
	for (i = 0; i < HealthEnemy; i++)
		sprite->Draw(x + i * texture->FrameWidth, y + 18);

	sprite->SelectIndex(BOARDHEALTH_FRAME_NONE);
	for (j = i; j < BOARDHEALTH_MAX_CELL; j++)
	{
		sprite->Draw(x + j * texture->FrameWidth, y + 18);
	}

}
