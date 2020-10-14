#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h"

class Camera
{
protected:
	float x_cam;
	float y_cam;
	int _width;
	int _height;

public:
	Camera(int w, int h);
	~Camera();

	D3DXVECTOR2 Translate(float x_w, float y_w);
	void SetPosition(float x, float y);
	void Update();
	int GetWidth();
	int GetHeight();

	float GetX_cam();
	float GetY_cam();
};

#endif
