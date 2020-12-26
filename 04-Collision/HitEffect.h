#pragma once
#include "Load_img_file.h"
#include "Load_resources.h"
#include "Camera.h"
#include "LoadTexture.h"

class HitEffect
{
protected:
	Load_img_file * texture;
	Load_resources * sprite;

	int x;
	int y;
	bool isFinish;

public:
	HitEffect();
	 ~HitEffect();

	virtual void Render(Camera * camera);
	virtual void Update(DWORD dt);
	bool GetFinish();
	void SetFinish(int b);
};


/* hit */
class Hit : public HitEffect
{
public:
	Hit(int X = 0, int Y = 0);
	~Hit();

	void Update(DWORD dt);
};

/* Effect */
class Effect : public HitEffect
{
	int times;
public:
	Effect(int X = 0, int Y = 0, int _times = 1);
	~Effect();

	void Update(DWORD dt);

};


/* brick flash */
#define BRICKSPLASH_GRAVITY 0.0015f 


class BrickSplash : public Effect
{
private:
	int direction;
	DWORD dt;
	float dx;
	float dy;
	float vx;
	float vy;
	int nx;

public:
	BrickSplash(int X, int Y, int _direction);
	virtual ~BrickSplash();
	void Update(DWORD dt);
};

/* water */
#define WATER_GRAVITY 0.0015f 


class Water : public Effect
{
private:
	int _model;
	DWORD dt;
	float dx;
	float dy;
	float vx;
	float vy;

public:
	Water(float X, float Y, int Model);
	virtual ~Water();

	void Update(DWORD dt);

};