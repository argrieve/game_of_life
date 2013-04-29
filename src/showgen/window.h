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
	public:
		window(int wx_l, int wx_h, int wy_l, int wy_h);
		// Main function called 
		void print_world(world &w, bool ascii);
	private:
		// Helper functions, based on output type
		void print_ascii(world &w);
		void print_aut(world &w);
		void print_col(world &w, int y, int start_x, int end_x);
};

#endif
