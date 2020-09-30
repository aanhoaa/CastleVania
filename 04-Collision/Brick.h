#ifndef __BRICK_H__
#define __BRICK_H__

#define BRICK_FRAME_WIDTH 32
#define BRICK_FRAME_HEIGHT 32

#include "GameObject.h"

class Brick : public CGameObject
{
protected:
	int width;
	int height;

public:
	Brick(int X, int Y, int W, int H);
	virtual void Render(Camera * camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

#endif