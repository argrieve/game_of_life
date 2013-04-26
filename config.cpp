#include "config.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

config::config()
{
	range_xl = new int;
	range_xh = new int;
	range_yl = new int;
	range_yh = new int;
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
	*range_xl = _l;
	*range_xh = _h;
}

void config::setY(int _l, int _h)
{
	*range_yl = _l;
	*range_yh = _h;
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
		cout << "(" << alive.at(i) << ", " << alive.at(i+1) << ")\n";
	cout << "END CONFIG\n";
}
