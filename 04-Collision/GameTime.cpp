#include "GameTime.h"

CGameTime::CGameTime()
{
	this->timed = 0;
	frameStart = GetTickCount();
	SetTime(0);
}


CGameTime::~CGameTime()
{
}

void CGameTime::Update()
{
	DWORD now = GetTickCount();
	DWORD dt = now - frameStart;

	if (timed + dt < 1000)
	{
		timed += dt;
	}
	else
	{
		timed = (timed + dt) % 1000;
		time++;
		standardTime = true; // set trạng thái thay đổi
	}

	frameStart = now;
}

void CGameTime::SetTime(int _time)
{
	time = _time;
}

int CGameTime::GetTime()
{
	return time;
}

bool CGameTime::checkIstandardTime()
{
	bool _standardTime = standardTime;
	standardTime = false; // sau khi lấy trạng thái xong rồi thì coi như "chưa thay đổi"
	return _standardTime;
}