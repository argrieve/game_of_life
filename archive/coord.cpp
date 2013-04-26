#include "coord.h" 
coord::coord()
{
	x = new int;
	y = new int;
}

coord::coord(int _x, int _y)
{
	x = new int;
	*x = _x;
	y = new int;
	*y = _y;
}

coord::~coord()
{
	delete x;
	delete y;
}
