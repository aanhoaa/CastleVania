#pragma once
#include "GameObject.h"

class HidenObject : public CGameObject
{
private:
	int width;
	int height;

public:
	HidenObject(int X, int Y, int Wight, int Height);
	~HidenObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
};
