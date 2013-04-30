/*
 * ComS 229 Project 2: sim-gui
 * Spring 2013
 * Alex Grieve
 *
 * world.cpp
 */

#include "world.h"
#include <iostream>

using namespace std;

/*
 * Initializes world's properties with values from
 * the specified config class/file.
 *
 * INPUT: &cnfg Config file that contains information from .aut file
 */
world::world(config &cnfg)
{
	// Grab the name
	name = cnfg.get_name();

	// Grab charcters
	dead = cnfg.get_dead();
	alive = cnfg.get_alive();

	// Grab colors
	dead_color = cnfg.get_dead_colors();
	alive_color = cnfg.get_alive_colors();

	// Reset generation number
	gen = 0;

	// Set anchor as upper left corner of the world
	anchor_x = cnfg.getXL();
	anchor_y = cnfg.getYH(); 

	// Determine width of the world based on tx_l and tx_h
	width = 0;
	for (int i=cnfg.getXL(); i<=cnfg.getXH(); i++) width++;

	// Determine height of the world based on ty_l and ty_h
	height = 0;
	for (int i=cnfg.getYL(); i<=cnfg.getYH(); i++) height++;

	// Build the array of cells (i.e. the world)
	cells.resize(width);
	cells_next.resize(width);
	for (int i=0; i<width; i++) {
		cells[i].resize(height);
		cells_next[i].resize(height);
	}

	// Initialize the array of cells to 'dead'
	for (int i=0; i<cells.size(); i++) 
		for (int j=0; j<cells[0].size(); j++) {
			cells[i][j] = 0;
			cells_next[i][j] = 0;
		}
	
	// Initialize alive cells from config class
	vector<int> alive = cnfg.getAlive();	
	int x, y;
	for (int i=0; i<alive.size(); i+=2) {
		// Make sure alive cell is in the terrain size
		if (alive[i] < cnfg.getXL() || alive[i] > cnfg.getXH()) continue;
		if (alive[i+1] < cnfg.getYL() || alive[i+1] > cnfg.getYH()) continue;
		x = to_screen_x(alive[i]);
		y = to_screen_y(alive[i+1]);
		cells[x][y] = 1;
	}
	
}

/*
 * Gets the color components for dead cells.
 *
 * RETURN: Pointer to array containing dead cell color
 */
char* world::get_dead_color()
{
	return dead_color;
}

/*
 * Gets the color components for alive cells.
 *
 * RETURN: Pointer to array containing alive cell color
 */
char* world::get_alive_color()
{
	return alive_color;
}

/*
 * Compute generation i+1 of the world.
 */
void world::next_gen()
{
	for(int i=0; i<width; i++)
		for(int j=0; j<height; j++)
			update_cell(i, j);
	
	update_world();

	return;
}

/*
 * Gets a cell's current state.
 *
 * INPUT: x Cartesian x-coordinate of the cell
 * INPUT: y Cartesian y-coordinate of the cell
 * RETURN: Cell's state (0=dead, 1=alive)
int world::get_cell(int x, int y)
{
	int scr_x = to_screen_x(x);
	int scr_y = to_screen_y(y);
	return cells[scr_x][scr_y];
}
*/
int world::get_cell(int x, int y)
{
	return cells[x][y];
}

/*
 * Prints the world in the specified format to stdout.
 *
 * INPUT: ascii If true, print the world in ASCII format, .aut format otherwise
 */
void world::print_world(bool ascii)
{
	// Print ASCII representation
	if (ascii) {
		for (int i=anchor_y; i>(int)(anchor_y-height); i--) {
			for (int j=anchor_x; j<(int)(anchor_x+width); j++) {
				if (cells[to_screen_x(j)][to_screen_y(i)]) cout << '1';
				else cout << '~';
			}
			cout << endl;
		}
	}
	// Print .aut file format
	else {
		// Print generation number as a comment
		cout << "#\n" << "# Generation: " << gen << "\n#\n";

		// Range keywords
		cout << "Xrange " << anchor_x << " " << (int)(anchor_x + width-1) << ";\n";
		cout << "Yrange " << (int)(anchor_y-height+1) << " " << anchor_y << ";\n";

		// Initial keyword
		cout << "Initial {\n";

		for (int i=anchor_y; i>(int)(anchor_y-height); i--) {
			// Search each column for 'alive' cells
			for (int j=anchor_x; j<(int)(anchor_x+width); j++) {
				if (cells[to_screen_x(j)][to_screen_y(i)]) {
					print_col(i); 
					break;
				}
			} // end width loop
		} // end height loop
		
		cout << "};\n";
	}
}

/*
 * Sets the current state of the world to generation i+1
 */
void world::update_world()
{
	for (int i=0; i<width; i++)
		for (int j=0; j<height; j++)
			cells[i][j] = cells_next[i][j];	
	
	gen++;

	return;
}

/* 
 * Update a current cell's state in generation i+1
 *
 * INPUT: x Cartesian x-coordinate of the cell
 * INPUT: y Cartesian y-coordinate of the cell
 */
void world::update_cell(int x, int y)
{
	int neighbors = count_neighbors(x, y);
	
	// Apply GoL rules
	if (cells[x][y]) {
		// Cell lives if there are 2 or 3 neighbors
		if(neighbors == 2 || neighbors == 3) cells_next[x][y] = 1;

		// Cell dies if neighbors < 2 (loneliness)
		// Cell dies if neighbors > 3 (overpopulation)
		else cells_next[x][y] = 0;
	}
	else {
		// Cell lives if neighbors = 3 (reproduction)
		if (neighbors == 3) cells_next[x][y] = 1;

		else cells_next[x][y] = 0;
	}

	return;
}

/*
 * Counts the number of alive neighbors immediately touching a cell.
 *
 * INPUT: x Cartesian x-coordinate of the cell
 * INPUT: y Cartesian y-coordinate of the cell
 * RETURN: Number of neighbors the cell has
 */
int world::count_neighbors(int x, int y)
{
	// Alive neighbor count
	int count = 0;

	// Start with upper left neighbor
	int y_start, x_start;
	if (y == 0) y_start = y;
	else y_start = y - 1;
	if (x == 0) x_start = x;
	else x_start = x - 1;

	// Find lower right neighbor
	int y_end, x_end;
	if (y == (height-1)) y_end = y;
	else y_end = y + 1;
	if (x == (width - 1)) x_end = x;
	else x_end = x + 1;

	// Count neighbors
	for (int i=x_start; i<=x_end; i++)
		for (int j=y_start; j<=y_end; j++) {
			// Don't count the cell itself
			if (i==x && j==y) continue;
			// Check neighbor
			if (cells[i][j] == 1) count++;
		}

	return count;
}

/*
 * Converts a cartesian x-coordinate into a screen coordinate
 *
 * INPUT: _x Cartesian x-coordinate
 * RETURN: Screen space x-coordinate
 */
int world::to_screen_x(int _x)
{
	int screen_x = 0;
	int end_x = (int)(anchor_x + width);

	for (int i=anchor_x; i<end_x, i!=_x; i++) screen_x++;
	return screen_x;
}

/*
 * Converts a cartesian y-coordinate into a screen coordinate
 *
 * INPUT: _y Cartesian y-coordinate
 * RETURN: Screen space y-coordinate
 */
int world::to_screen_y(int _y)
{
	int screen_y = 0;
	int end_y = (int)(anchor_y - height);
	
	for (int i=anchor_y; i>end_y, i!=_y; i--) screen_y++;
	return screen_y;
}

/*
 * Prints a column that contains alive cells in .aut format
 *
 * INPUT: y Column number to print
 */
void world::print_col(int y)
{
	cout << "  Y = " << y << " :   ";

	// Find all alive cells in the column
	bool first = true;
	for (int i=anchor_x; i<(int)(anchor_x+width); i++) {
		// Found an live cell
		if (cells[to_screen_x(i)][to_screen_y(y)]) {
			// Don't print a comma if it is the first alive cell
			if (first) { cout << i;	first = false; }
			else cout << ", " << i;
		}
	}

	cout << ";\n";
}
