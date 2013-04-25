#include "world.h"

world::world(int tx_l, int tx_h, int ty_l, int ty_h)
{
	// Reset generation number
	gen = 0;

	// Correct backwards coordinates
	if (tx_l > tx_h) {
		int tmp = tx_l;
		tx_l = tx_h;
		tx_h = tmp;
	}
	if (ty_l > ty_h) {
		int tmp = ty_l;
		ty_l = ty_h;
		ty_h = tmp;
	}
	
	// Set anchor as upper left corner of the world
	anchor_x = tx_l; 
	anchor_y = ty_h; 

	// Determine width of the world based on tx_l and tx_h
	width = 0;
	for (int i=tx_l; i<=tx_h; i++) width++;

	// Determine height of the world based on ty_l and ty_h
	height = 0;
	for (int i=ty_l; i<=ty_h; i++) height++;

	// Build the array of cells (i.e. the world)
	carr = new cell*[width];
	for (int i=0; i<width; i++) carr[i] = new cell[height];
}

void world::next_gen()
{
	for(int i=0; i<width; i++)
		for(int j=0; j<height; j++)
			update_cell(i, j);
	
	gen++;
	return;
}

world::~world()
{
	for (int i=0; i<width; i++) delete[] carr[i];
	delete[] carr;
}

void world::update_cell(int x, int y)
{
	int neighbors = count_neighbors(x, y);
	cell &c = carr[x][y];
	
	// Apply GoL rules
	if (c.isAlive()) {
		// Cell lives if there are 2 or 3 neighbors
		if(neighbors == 2 || neighbors == 3) c.set_state(true);

		// Cell dies if neighbors < 2 (loneliness)
		// Cell dies if neighbors > 3 (overpopulation)
		else c.set_state(false);
	}
	else {
		// Cell lives if neighbors = 3 (reproduction)
		if (neighbors == 3) c.set_state(true);

		else c.set_state(false);
	}

	return;
}

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
			if (carr[i][j].isAlive()) count++;
		}

	return count;
}
