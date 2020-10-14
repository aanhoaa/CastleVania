#pragma once
#include "Items.h"
#include "Data.h"

#define LARGEHEART_GRAVITY 0.25f

#define LARGEHEART_TIMEDISPLAYMAX 3000

class BigHeart : public Items
{
public:
	BigHeart();
	BigHeart(float X, float Y);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	void SetReward();
	//void Render(Camera * camera);

	~BigHeart();
};

