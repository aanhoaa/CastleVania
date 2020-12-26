#ifndef __BRICK_H__
#define __BRICK_H__

#include "GameObject.h"

class Brick : public CGameObject
{
protected:
	int width;
	int height;

public:
	Brick(int X, int Y, int W, int H, int updateBrick);
	virtual void Render(Camera * camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

#endif