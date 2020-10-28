#pragma once
#include "define.h"
#include <vector>

class Data
{
public:
	static Data * __Instance;
	static Data * GetInstance();
	int scene;

	//vector<Item *> ListItem; // lisst chứa các item



	Data();
	~Data();
};
