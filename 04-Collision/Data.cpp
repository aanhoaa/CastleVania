#include "Data.h"

Data * Data::__Instance = NULL;

Data * Data::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Data();
	return __Instance;
}

Data::Data()
{
	ListItem.clear();
	HeartCollect = 0;
}

Data::~Data()
{
}