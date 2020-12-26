#pragma once
#define HOLLYWATER_SPEED_X 0.24f
#define HOLLYWATER_SPEED_Y 0.25f
#define HOLYWATER_GRAVITY 0.0015f
#include "Weapons.h"

class HolyWater : public Weapons
{
private:
	Load_img_file * texture_item;
	Load_resources * sprite_item;
	bool isCollisionBrick;
	int countSprite = 0;
public:
	HolyWater();
	virtual ~HolyWater();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float simon_X, float simon_Y, int simon_nx);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdatePositionFitSimon();

	void RenderItem(int X, int Y);
	bool isCollision(CGameObject* obj);
	void Render(Camera *camera);

};

