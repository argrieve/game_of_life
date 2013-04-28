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
	dead = new char;
	alive = new char;
	*dead = '~';
	*alive = '1';
	color_dead = new char[3];
	color_alive = new char[3];
	color_dead[0] = 0;
	color_dead[1] = 0;
	color_dead[2] = 0;
	color_alive[0] = 0;
	color_alive[1] = 0;
	color_alive[2] = 0;
}

config::~config()
{
	delete range_xl;
	delete range_xh;
	delete range_yl;
	delete range_yh;
	delete dead;
	delete alive;
	delete[] color_dead;
	delete[] color_alive;
}

char* config::get_dead_colors()
{
	return color_dead;
}

char* config::get_alive_colors()
{
	return color_alive;
}

void config::set_name(const char* str)
{
	name.clear();
	name = str;
}

void config::set_chars(char d, char a)
{
	*dead = d;
	*alive = a;
}

void config::set_colors(int dr, int dg, int db, int ar, int ag, int ab)
{
	color_dead[0] = (char)dr;
	color_dead[1] = (char)dg;
	color_dead[2] = (char)db;
	color_alive[0] = (char)ar;
	color_alive[1] = (char)ag;
	color_alive[2] = (char)ab;
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
	alive_cells.push_back(_x);
	alive_cells.push_back(_y);
}

// For debugging
void config::print()
{
	cout << "CONFIG:\n";
	cout << "Name \"" << name << "\";\n";
	cout << "Chars " << (int)*dead << ", " << (int)*alive << ";\n";
	cout << "Colors (";
	cout << (int)color_dead[0] << ", " << (int)color_dead[1] << ", " << (int)color_dead[2] << "), ";
	cout << "(" << (int)color_alive[0] << ", " << (int)color_alive[1] << ", " << (int)color_alive[2];
	cout << ");\n";
	cout << "Xrange: " << *range_xl << " to " << *range_xh << "\n";
	cout << "Yrange: " << *range_yl << " to " << *range_yh << "\n";
	for (int i=0; i<alive_cells.size(); i+=2)
		cout << "(" << alive_cells[i] << ", " << alive_cells[i+1] << ")\n";
	cout << "END CONFIG\n";
}
