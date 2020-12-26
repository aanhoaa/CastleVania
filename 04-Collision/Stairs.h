#pragma once
#include "GameObject.h"

#define BOTTOM_STAIR 1
#define TOP_STAIR 2

class Stairs : public CGameObject
{
private:
	int width;
	int height;
	int stairType; // kiểu object cầu thang, 1 ở dưới, 2 ở trên

public:
	Stairs(int X, int Y, int _stairType);
	virtual ~Stairs();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
};


