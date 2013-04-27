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
		//~world();
		void next_gen();
		inline unsigned int curr_gen() { return gen; }
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
