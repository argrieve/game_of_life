#include "world.h"
#include <iostream>

using namespace std;

world::world(config &cnfg)
{
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
		x = to_screen_x(alive[i]);
		y = to_screen_y(alive[i+1]);
		cells[x][y] = 1;
	}
	
}

void world::next_gen()
{
	for(int i=0; i<width; i++)
		for(int j=0; j<height; j++)
			update_cell(i, j);
	
	update_world();

	return;
}

void world::print_gen(bool ascii)
{
	// Print ASCII representation
	if (ascii) {
		for (int i=0; i<height; i++) {
			for (int j=0; j<width; j++) {
				if (cells[j][i]) cout << 1;
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

		for (int i=0; i<height; i++) {
			// Search each column for 'alive' cells
			for (int j=0; j<width; j++) {
				if (cells[j][i]) {
					print_col(i); 
					break;
				}
			} // end width loop
		} // end height loop
		
		cout << "};\n";
	}
}

void world::update_world()
{
	for (int i=0; i<width; i++)
		for (int j=0; j<height; j++)
			cells[i][j] = cells_next[i][j];	
	
	gen++;

	return;
}

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

int world::to_screen_x(int _x)
{
	return _x + width/2;
}

int world::to_screen_y(int _y)
{
	return height/2 - _y;
}

void world::print_col(int y)
{
	cout << "  Y = " << (int)(height/2 - y) << " :   ";

	// Find all alive cells in the column
	bool first = true;
	for (int i=0; i<width; i++) {
		// Found an live cell
		if (cells[i][y]) {
			// Don't print a comma if it is the first alive cell
			if (first) { cout << (int)(i-width/2);	first = false; }
			else cout << ", " << (int)(i-width/2);
		}
	}

	cout << ";\n";
}
