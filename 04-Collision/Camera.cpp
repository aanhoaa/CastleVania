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

D3DXVECTOR2 Camera::Translate(int x, int y)
{
	return D3DXVECTOR2(x - viewport.x, y - viewport.y);
}

void Camera::SetPosition(int x, int y)
{
	viewport.x = x;
	viewport.y = y;
}

D3DXVECTOR2 Camera::GetViewport()
{
	return viewport;
}

void Camera::Update()
{

	if (viewport.x < 0)
			viewport.x = 0;

	if (viewport.x > MapWidth - Window_Width) // khi cam đến cuối map thì S sẽ đi đến cuối, cam đứng yên k render nữa (giu nguyen render cũ)
			viewport.x = MapWidth - Window_Width;

}

