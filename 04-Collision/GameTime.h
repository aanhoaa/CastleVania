#pragma once
#include "define.h"

class CGameTime
{
private:
	DWORD timed; // timed đã tích lũy
	int time; // time game
	DWORD frameStart;
	bool standardTime; // flag mỗi khi time tăng đủ 1s tròn thì chuyển trạng thái

public:
	CGameTime();
	~CGameTime();
	void Update();
	void SetTime(int _time);
	int GetTime();
	bool checkIstandardTime(); // check khi nào time đủ 1s tròn thì sẽ reset lại trạng thái time
};
