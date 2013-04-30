/*
 * ComS 229 Project 2: sim-tui
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
	int anchor_x, anchor_y; // upper left coordinates of the window
	int vsize, hsize; // scrollbar thumb sizes
	int x_indx, y_indx; // count of up/down and left/right key presses
	world &w;
	public:
		window(int _width, int _height, world &wrld);
		// Getters
		inline unsigned int get_width() { return width; }
		inline unsigned int get_height() { return height; }
		int get_cell(int x, int y);
		inline int get_vscroll_size() { return vsize; }
		inline int get_hscroll_size() { return hsize; }
		int get_vscroll_pos();
		int get_hscroll_pos();
		// Scrollbar manipulation
		void scroll_up();
		void scroll_down();
		void scroll_left();
		void scroll_right();
};

#endif
