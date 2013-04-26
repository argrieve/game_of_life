#include "coord.h"

coord::coord()
{
	x = new int;
	y = new int;
}

coord::~coord()
{
	delete x;
	delete y;
}
