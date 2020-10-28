#pragma once
#include "Load_img_file.h"
#include "Load_resources.h"
#include "Camera.h"


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

class Hit : public HitEffect
{
public:
	Hit(int X = 0, int Y = 0);
	~Hit();

	void Update(DWORD dt);
};

class Effect : public HitEffect
{


public:
	Effect(int X = 0, int Y = 0);
	~Effect();

	void Update(DWORD dt);

};