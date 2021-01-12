﻿#pragma once
#include "define.h"
#include <vector>
#include "Camera.h"

class Data
{
public:
	static Data * __Instance;
	static Data * GetInstance();
	int scene;
	float boundaryLeft;
	float boundaryRight;
	bool bossAppear = false;
	bool passBoss = false;
	bool passGate = false;
	float y_Cam;

	int hpBoss = 16;


	Data();
	~Data();
};
