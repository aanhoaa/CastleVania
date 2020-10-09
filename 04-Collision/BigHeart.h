#pragma once
#include "Items.h"
#include "GameObject.h"

#define LARGEHEART_GRAVITY 0.005f

#define LARGEHEART_TIMEDISPLAYMAX 200

class BigHeart : public Items
{
public:
	BigHeart();
	BigHeart(float X, float Y);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, CGameObject * listObject);
	void Render(Camera * camera);

	~BigHeart();
};

