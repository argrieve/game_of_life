#ifndef WORLD_H
#define WORLD_H

#include "cell.h"

class world {
	unsigned int gen;
	cell **carr;
	unsigned int width, height;
	int anchor_x, anchor_y;
	public:
		world(int tx_l, int tx_h, int ty_l, int ty_h);
		~world();
		void next_gen();
		inline unsigned int curr_gen() { return gen; }
	private:
		void update_cell(int x, int y);
		int count_neighbors(int x, int y);
};

#endif
