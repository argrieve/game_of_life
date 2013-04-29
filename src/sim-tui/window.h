/*
 * ComS 229 Project 2: showgen
 * Spring 2013
 * Alex Grieve
 *
 * window.h
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "world.h"

/*
 * This class determines how to display the cells
 * in a world class.
 */
class window {
	// Member variables
	unsigned int width, height;
	int anchor_x, anchor_y;
	world &w;
	public:
		window(int _width, int _height, world &wrld);
		inline unsigned int get_width() { return width; }
		inline unsigned int get_height() { return height; }
		int get_cell(int x, int y);
		void scroll_up();
		void scroll_down();
		void scroll_left();
		void scroll_right();
		int get_vscroll_size();
		int get_hscroll_size();
		int get_vscroll_pos();
		int get_hscroll_pos();
};

#endif
