#pragma once
#include "Items.h"

#define LARGEHEART_GRAVITY 0.25f

#define LARGEHEART_TIMEDISPLAYMAX 3000
#define LARGEHEART_TIMEWAITMAX 300

class BigHeart : public Items
{
public:
	BigHeart();
	BigHeart(float X = 0, float Y = 0);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL); // only collision with ground(brick)
	void SetReward();
	//void Render(Camera * camera);

	~BigHeart();
};

