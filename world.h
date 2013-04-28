#ifndef WORLD_H
#define WORLD_H

#include "config.h"
#include <vector>

using namespace std;

class world {
	unsigned int gen;
	unsigned int width, height;
	int anchor_x, anchor_y;
	vector<vector<int> > cells;
	vector<vector<int> > cells_next;
	public:
		world(config &cnfg);
		inline unsigned int curr_gen() { return gen; }
		inline unsigned int get_width() { return width; }
		inline unsigned int get_height() { return height; }
		inline int get_anchor_x() { return anchor_x; }
		inline int get_anchor_y() { return anchor_y; }
		void next_gen();
		int get_cell(unsigned int x, unsigned int y);
		void print_gen(bool ascii);
	private:
		void update_world();
		void update_cell(int x, int y);
		int count_neighbors(int x, int y);
		int to_screen_x(int _x);
		int to_screen_y(int _y);
		void print_col(int y);
};

#endif
