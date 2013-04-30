/*
 * ComS 229 Project 2: sim-tui
 * Spring 2013
 * Alex Grieve
 *
 * config.cpp
 */

#include "config.h"
#include <iostream>
#include "stdio.h"

using namespace std;

/*
 * Reserve space for all member variables. Initialize to zero.
 */ 
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

/*
 * Free space allocated for member variables.
 */
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

/*
 * RETURN: The array of RGB colors for dead cells.
 */
char* config::get_dead_colors()
{
	return color_dead;
}

/*
 * RETURN: The array of RGB colors for alive cells.
 */
char* config::get_alive_colors()
{
	return color_alive;
}

/*
 * Set the name of the simulation.
 *
 * INPUT: *str Name of the simulation.
 */
void config::set_name(const char* str)
{
	name.clear();
	name = str;
}

/*
 * Set the characters for alive/dead cells.
 *
 * INPUT: d Character representing a dead cell.
 * INPUT: a Character representing an alive cell.
 */
void config::set_chars(char d, char a)
{
	*dead = d;
	*alive = a;
}

/*
 * Set the colors for alive and dead cells.
 *
 * INPUT: dr Dead cell red componet
 * INPUT: dg Dead cell green component
 * INPUT: db Dead cell blue component
 * INPUT: ar Alive cell red componet
 * INPUT: ag Alive cell green component
 * INPUT: ab Alive cell blue component
 */
void config::set_colors(int dr, int dg, int db, int ar, int ag, int ab)
{
	color_dead[0] = (unsigned char)dr;
	color_dead[1] = (unsigned char)dg;
	color_dead[2] = (unsigned char)db;
	color_alive[0] = (unsigned char)ar;
	color_alive[1] = (unsigned char)ag;
	color_alive[2] = (unsigned char)ab;
}

/*
 * Set the XRange for the simulation
 *
 * INPUT: _l Lower value of the range
 * INPUT: _H Upper value of the range
 */
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

/*
 * Set the YRange for the simulation
 *
 * INPUT: _l Lower value of the range
 * INPUT: _H Upper value of the range
 */
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

/*
 * Add a cell to the initial 'alive cells' list.
 *
 * INPUT: _x X-coordinate of the alive cell
 * INPUT: _y Y-coordinate of the alive cell
 */
void config::add(int _x, int _y) 
{
	alive_cells.push_back(_x);
	alive_cells.push_back(_y);
}

/*
 * Print the attrivutes of the config file for debugging.
 */
void config::print()
{
	cout << "CONFIG:\n";
	cout << "Name \"" << name << "\";\n";
	cout << "Chars " << (int)*dead << ", " << (int)*alive << ";\n";
	unsigned char r = color_dead[0];
	unsigned char g = color_dead[1];
	unsigned char b = color_dead[2];
	printf("Colors (%d, %d, %d)", r, g, b);
	r = color_alive[0];
	g = color_alive[1];
	b = color_alive[2];
	printf(", (%d, %d, %d);\n", r, g, b);
	cout << "Xrange: " << *range_xl << " to " << *range_xh << "\n";
	cout << "Yrange: " << *range_yl << " to " << *range_yh << "\n";
	for (int i=0; i<alive_cells.size(); i+=2)
		cout << "(" << alive_cells[i] << ", " << alive_cells[i+1] << ")\n";
	cout << "END CONFIG\n";
}
