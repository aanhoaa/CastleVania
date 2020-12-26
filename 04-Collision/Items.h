﻿#pragma once
#include "define.h"
#include "Camera.h"
#include "Load_img_file.h"
#include "Load_resources.h"
#include "debug.h"
#include "BBox.h"
#include "GameObject.h"
#include "LoadTexture.h"

#define TIMEWAITMAX 400

#define UPGRADEMORNINGSTAR_GRAVITY 0.25f

#define UPGRADEMORNINGSTAR_TIMEDISPLAYMAX 3000

class Items : public CGameObject
{
protected:
	DWORD  TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	DWORD  TimeDisplayed; // Thời gian đã hiển thị.

	DWORD TimeWaited; // Thời gian đã chờ trước khi hiển thị
	DWORD TimeWaitMax; // Thời gian tối đa phải chờ trước khi hiển thị

	bool isFinish; // đã kết thúc chưa?
public:
	Items();
	~Items();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	virtual void Render(Camera * camera);
	virtual bool isWaitingDisplay(); // đang chờ object hiển thi? - simon chưa được ăn

	bool GetFinish();
	void SetFinish(bool _isFinish);
};

#define UPGRADEMORNINGSTAR_TIMEWAITMAX 300

/* Morning star item*/
class Whip : public Items
{
public:
	Whip(float X, float Y);

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);

	~Whip();
};

#define ITEMDAGGER_TIMEDISPLAYMAX 3000
#define ITEMDAGGER_GRAVITY 0.25f
#define ITEMDAGGER_TIMEWAITMAX 300

/* Dagger item */
class iDagger : public Items
{
public:
	iDagger(float X = 0, float Y = 0);
	~iDagger();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL); // Update và xét va chạm đất
};

/* Money Bag*/
#define MONEY_TIMEDISPLAYMAX 3000
#define MONEY_TIMEWAITMAX 300
#define MONEY_GRAVITY 0.25f

/* Money bag*/
class MoneyBag : public Items
{
public:
	MoneyBag(float X = 0, float Y = 0);
	~MoneyBag();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
};

/* Holy water*/

#define ITEMHOLYWATER_TIMEDISPLAYMAX 3000
#define ITEMHOLYWATER_GRAVITY 0.25f
#define ITEMHOLYWATER_TIMEWAITMAX 300

class iHolyWater : public Items
{
public:
	iHolyWater(float X = 0, float Y = 0);
	~iHolyWater();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL); 
};

// postroast
#define POTROAST_GRAVITY 0.25f
#define POTROAST_TIMEDISPLAYMAX 3000
#define POTROAST_TIMEWAITMAX 300

class PotRoast : public Items
{
public:
	PotRoast(float X, float Y);
	virtual ~PotRoast();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL); // Update và xét va chạm đất
};

/* Axe */

#define ITEMTHROWINGAXE_TIMEDISPLAYMAX 3000
#define ITEMTHROWINGAXE_GRAVITY 0.25f
#define ITEMTHROWINGAXE_TIMEWAITMAX 300

class iAxe :public Items
{
public:
	iAxe(float X = 0, float Y = 0);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	virtual ~iAxe();
};


/* Magic Crystal */
#define MAGICCRYSTAL_GRAVITY 0.25f
#define MAGICCRYSTAL_TIMEWAITMAX 3000

class MagicCrystal : public Items
{
public:
	MagicCrystal(int X, int Y);
	virtual ~MagicCrystal();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	virtual void Render(Camera * camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};