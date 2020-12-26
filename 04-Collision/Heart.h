#pragma once
#include "Items.h"

#define LARGEHEART_GRAVITY 0.25f

#define LARGEHEART_TIMEDISPLAYMAX 3000
#define LARGEHEART_TIMEWAITMAX 300

class BigHeart : public Items
{
public:
	//BigHeart();
	BigHeart(float X = 0, float Y = 0);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL); // only collision with ground(brick)

	~BigHeart();
};

#define SMALLHEART_GRAVITY 0.04f
#define SMALLHEART_TIMEDISPLAYMAX 6000
#define SMALLHEART_TIMEWAITMAX 150

#define SMALLHEART_SPEED_X 0.05f

#define DeltaX 25 //px


class SmallHeart : public Items
{
private:
	float rootX; // lưu vị trị x khi bắt đầu tạo heart

public:
	SmallHeart(float X = 0, float Y = 0);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL); // Update và xét va chạm đất

	virtual ~SmallHeart();
};