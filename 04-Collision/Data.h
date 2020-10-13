#pragma once
#include "define.h"
#include <vector>
#include "Items.h"

class Data
{
public:
	static Data * __Instance;
	static Data * GetInstance();

	vector<Items*> ListItem;
	int HeartCollect; // số lượng item heart người chơi nhặt được

	//vector<Item *> ListItem; // lisst chứa các item

	Data();
	~Data();
};
