#pragma once
#include "Weapons.h"

#define DAGGER_SPEED 0.35f

class Dagger : public Weapons
{
public:
	Dagger();
	~Dagger();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float simonX, float simonY, int simonTrend);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool isCollision(CGameObject* obj);
	void RenderItem(int X, int Y);
	void Render(Camera *camera);

};


