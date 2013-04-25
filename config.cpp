#include "config.h"
#include <iostream>

using namespace std;

void config::setX(int _l, int _h)
{
	x_range = coord(_l, _h);
}

void config::setY(int _l, int _h)
{
	y_range = coord(_l, _h);
}

void config::add(int _x, int _y) 
{
	alive.push_back(coord(_x, _y));
}

std::vector<coord>& config::getAlive()
{
	return alive;	
}

// For debugging
void config::print()
{
	cout << "CONFIG:\n";
	cout << "Xrange: " << x_range.getX() << " to " << x_range.getY() << "\n";
	cout << "Yrange: " << y_range.getX() << " to " << y_range.getY() << "\n";
	for (int i=0; i<alive.size(); i++)
		cout << "(" << alive.at(i).getX() << ", " << alive.at(i).getY() << ")\n";
	cout << "END CONFIG\n";
}
