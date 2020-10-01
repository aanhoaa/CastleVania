#pragma once

#define MORNINGSTAR_ANI_LEVEL0_START 0
#define MORNINGSTAR_ANI_LEVEL0_END 3


#include "Weapons.h"

class MorningStar : public Weapons
{
protected:
	int level;

public:
	MorningStar();
	~MorningStar();
	void Create(float simon_X, float simon_Y, int simon_nx);
	void Update(int dt);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdatePositionFitSimon();

};
