#pragma once
#include "Weapons.h"

#define AXE_SPEED_X 0.2f
#define AXE_SPEED_Y 0.55f
#define AXE_GRAVITY 0.0015f

class Axe :public Weapons
{
private:
	Load_img_file * texture_item;
	Load_resources * sprite_item;
	Camera * camera;

public:

	Axe(Camera * camera);
	virtual ~Axe();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float simon_X, float simon_Y, int simon_nx);
	virtual void RenderItem(int X, int Y);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdatePositionFitSimon();
	bool isCollision(CGameObject* obj);
	void Render(Camera *camera);
};
