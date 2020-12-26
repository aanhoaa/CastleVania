#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h"
#include "Data.h"

class Camera
{
protected:
	float x_cam;
	float y_cam;

	int width;
	int height;

	float boundaryLeft; // biên giới hạn bên trái cam
	float boundaryRight; // biên giới hạn bên phải cam

	float vx;
	DWORD dt;

	bool isAutoGo; 
	float autoGo_dx;
	float x_root;
	bool isAllowFollowSimon; // 1: đi theo simon, 0: tự đi(k có dk)

	float x_camBackUp;
	float y_camBackUp;
	float boundaryLeftBackup;
	float boundaryRightBackup;

public:
	
	Camera(int _width, int _height);
	~Camera();

	D3DXVECTOR2 Translate(float x_w, float y_w);
	void SetPosition(float x, float y);
	void Update(DWORD dt);
	int GetWidth();
	int GetHeight();

	float GetX_cam();
	float GetY_cam();

	bool isObjectInCamera(float x, float y, float w, float h);
	bool AllowFollowSimon();
	void SetAllowFollowSimon(bool b);
	void AutoGo(float _autoGo_dx, float _autoGo_vx); // set các thông số auto
	bool GetIsAutoGoX();
	void StopAutoGoX();
	void SetBoundary(float left, float right); // set biên giới hạn cho camera
	float GetBoundaryRight();
	float GetBoundaryLeft();
	void SetPositionBackup(float X, float Y);
	void RestorePosition();
	void SetBoundaryBackup(float l, float r);
	void RestoreBoundary();
};

#endif
