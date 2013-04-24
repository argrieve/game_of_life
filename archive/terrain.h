#ifndef TERRAIN_H
#define TERRAIN_H

#include "cell.h"
#include "coord.h"
#include "range.h"

class terrain {
	range &x, &y;
	cell **carr;
	public:
		terrain(range _x, range _y);
		~terrain();
		inline range getX() { return x; }
		inline range getY() { return y; }
		cell& get_cell(coord point);
};

#endif
