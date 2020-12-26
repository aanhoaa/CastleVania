#include "Camera.h"


Camera::Camera(int _width, int _height)
{
	width = _width;
	height = _height;
	isAllowFollowSimon = true;
	isAutoGo = false;

	// Biên mặc định ban đầu là kích thước MAP
	boundaryLeft = 0;
	boundaryRight = 0;
	vx = 0;

	x_camBackUp = y_camBackUp = 0;
	SetBoundaryBackup(boundaryLeft, boundaryRight);
}

Camera::~Camera()
{
}

int Camera::GetWidth()
{
	return width;
}

int Camera::GetHeight()
{
	return height;
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

void Camera::Update(DWORD dt)
{
	this->dt = dt;

	if (isAutoGo)
	{
		float dx = vx * dt;
		x_cam += dx;

		if (abs(x_cam - x_root) >= autoGo_dx)
		{
			x_cam = x_cam - (abs(x_cam - x_root) - autoGo_dx); // set lại vị trí mới cho cam
			isAutoGo = false; // dừng auto cam
		}
	}

	if (x_cam < boundaryLeft)
		x_cam = boundaryLeft;

	if (x_cam > boundaryRight) // khi cam đến cuối map thì S sẽ đi đến cuối, cam đứng yên k render nữa (giu nguyen render cũ)
		x_cam = boundaryRight;

	Data::GetInstance()->boundaryLeft = GetBoundaryLeft();
	Data::GetInstance()->boundaryRight = GetBoundaryRight();
	Data::GetInstance()->y_Cam = GetY_cam();
}

bool Camera::isObjectInCamera(float x, float y, float w, float h)
{
	if (x + w < x_cam || x_cam + width < x || y + h < y_cam || y_cam + height < y)
		return false;

	return true;
}

bool Camera::AllowFollowSimon()
{
	return isAllowFollowSimon;
}

void Camera::SetAllowFollowSimon(bool b)
{
	isAllowFollowSimon = b;
}

void Camera::AutoGo(float _autoGo_dx, float _autoGo_vx)
{
	if (isAutoGo)
		return;

	isAutoGo = true;
	isAllowFollowSimon = false;
	vx = _autoGo_vx;
	x_root = x_cam;
	autoGo_dx = _autoGo_dx;
}

bool Camera::GetIsAutoGoX()
{
	return isAutoGo;
}

void Camera::StopAutoGoX()
{
	isAutoGo = false;
}

void Camera::SetBoundary(float left, float right)
{
	boundaryLeft = left;
	boundaryRight = right;
}

float Camera::GetBoundaryRight()
{
	return boundaryRight;
}

float Camera::GetBoundaryLeft()
{
	return boundaryLeft;
}

void Camera::SetPositionBackup(float X, float Y)
{
	x_camBackUp = X;
	y_camBackUp = Y;
}

void Camera::RestorePosition()
{
	x_cam = x_camBackUp;
	y_cam = y_camBackUp;
	boundaryLeft = boundaryLeftBackup;
	boundaryRight = boundaryRightBackup;
}

void Camera::SetBoundaryBackup(float l, float r)
{
	boundaryLeftBackup = l;
	boundaryRightBackup = r;
}

void Camera::RestoreBoundary()
{
	boundaryLeft = boundaryLeftBackup;
	boundaryRight = boundaryRightBackup;
}