#include "Camera.h"


Camera::Camera(int w, int h)
{
	_width = w;
	_height = h;
}

Camera::~Camera()
{
}

int Camera::GetWidth()
{
	return _width;
}

int Camera::GetHeight()
{
	return _height;
}

D3DXVECTOR2 Camera::Translate(float x_w, float y_w)
{
	return D3DXVECTOR2(x_w - x_cam, y_w - y_cam);
}

void Camera::SetPosition(float x, float y)
{
	x_cam = x;
	y_cam = y;
}

float Camera::GetX_cam()
{
	return x_cam;
}

float Camera::GetY_cam()
{
	return y_cam;
}

void Camera::Update()
{

	if (x_cam < 0)
		x_cam = 0;

	if (x_cam > MapWidth - Window_Width) // khi cam đến cuối map thì S sẽ đi đến cuối, cam đứng yên k render nữa (giu nguyen render cũ)
		x_cam = (float)(MapWidth - Window_Width);

}

