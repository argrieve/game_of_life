#ifndef WINDOW_H
#define WINDOW_H

#include "range.h"
#include "coord.h"

class window {
	coord &anchor;
	range &x, &y;
	public:
		window(coord _anchor, range _x, range_y);
		inline coord getAnchor() { return anchor; }
		inline range getX() { return x; }
		inline range getY() { return y; }
		void move_up();
		void move_down();
		void move_left();
		void move_right();
};

#endif
