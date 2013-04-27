#include "config.h"
#include <iostream>

using namespace std;

config::config()
{
	range_xl = new int;
	range_xh = new int;
	range_yl = new int;
	range_yh = new int;
	*range_xl = 0;
	*range_xh = 0;
	*range_yl = 0;
	*range_yh = 0;
}

config::~config()
{
	delete range_xl;
	delete range_xh;
	delete range_yl;
	delete range_yh;
}

void config::setX(int _l, int _h)
{
	// Correct backwards parameters
	if (_l < _h) {
		*range_xl = _l;
		*range_xh = _h;
	}
	else {
		*range_xl = _h;
		*range_xh = _l;
	}
}

void config::setY(int _l, int _h)
{
	// Correct backwards parameters
	if (_l < _h) {
		*range_yl = _l;
		*range_yh = _h;
	}
	else {
		*range_yl = _h;
		*range_yh = _l;
	}
}

void config::add(int _x, int _y) 
{
	alive.push_back(_x);
	alive.push_back(_y);
}

// For debugging
void config::print()
{
	cout << "CONFIG:\n";
	cout << "Xrange: " << *range_xl << " to " << *range_xh << "\n";
	cout << "Yrange: " << *range_yl << " to " << *range_yh << "\n";
	for (int i=0; i<alive.size(); i+=2)
		cout << "(" << alive[i] << ", " << alive[i+1] << ")\n";
	cout << "END CONFIG\n";
}
