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
	scene = 1;
}


Data::~Data()
{
}