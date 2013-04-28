#ifndef WINDOW_H
#define WINDOW_H

#include "world.h"

class window {
	unsigned int width, height;
	int anchor_x, anchor_y;
	public:
		window(int wx_l, int wx_h, int wy_l, int wy_h);
		void print_world(world &w, bool ascii);
	private:
		void print_ascii(world &w);
		void print_aut(world &w);
		void print_col(world &w, int y, int start_x, int end_x);
};

#endif
