#ifndef TERRAIN_H
#define TERRAIN_H

#include "cell.h"

class terrain {
	unsigned int x, y;
	cell **carr;
	public:
		terrain(unsigned int _x, unsigned int _y);
		~terrain();
		inline unsigned int get_x() { return x; }
		inline unsigned int get_y() { return y; }
		cell& get_cell(unsigned int _x, unsigned int _y);
};

#endif
