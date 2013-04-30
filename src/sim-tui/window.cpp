/*
 * ComS 229 Project 2: sim-tui
 * Spring 2013
 * Alex Grieve
 *
 * window.cpp
 */

#include "window.h"
#include <iostream>
#include "stdio.h"

using namespace std;

/*
 * Constructor that intializes the X and Y window ranges
 */
window::window(int _width, int _height, world &wrld)
: w(wrld)
{
	// Set width/height
	width = _width + 1;
	height = _height + 1;

	// Set anchors
	anchor_x = w.get_anchor_x();
	anchor_y = w.get_anchor_y();

	// Calculate vertical scroll bar thumb size
	if (height >= w.get_height()) vsize = -1;
	else {
		double step = (double)(height-2)/w.get_height();
		// Scrollbar size = step size*number of characters in the window
		vsize = (int)(step * height);
	}

	// Calculate horizontal scroll bar thumb size
	if (width >= w.get_width()) hsize = -1;
	else {
		double step = (double)(width-2)/w.get_width();
		// Scrollbar size = step size*number of characters in the window
		hsize = (int)(step * width);
	}

	// Initialize scroll indexes/counts
	x_indx = 0;
	y_indx = 0;
}

/*
 * Gets the cell at the specified screen coordinates. Caller doesn't
 * need to know anything about where the window is, just need the
 * screen coordinate of the cell.
 *
 * INPUT: x Screen x-coordinate of the desired cell
 * INPUT: y Screen y-coordinate of the desired cell
 * RETURN: State of the cell located at screen coordinate (x,y) if it
 *         is inside the current window range, -1 otherwise
 */
int window::get_cell(int x, int y)
{
	// Convert screen coordinates
	int cartx = anchor_x + x;
	int carty = anchor_y - y;

	// Check if we are inside the window range
	if (cartx < w.get_anchor_x() || cartx >= (int)(w.get_anchor_x()+w.get_width())) return -1;
	if (carty > w.get_anchor_y() || carty <= (int)(w.get_anchor_y()-w.get_height())) return -1;

	return w.get_cell(cartx, carty);
}

/*
 * Calculates the offset for the vertical scrollbar thumb based on 
 * the current number of up/down keypresses (y_indx) and the size
 * of the world and window. Offset is given from the top of the
 * scrollbar.
 *
 * RETURN: Vertical scrollbar offset
 */
int window::get_vscroll_pos()
{
	// Calculate the offset from the bottom for the scrollbar thumb
	double px = (double)((height-2)-vsize)/(w.get_height()-height);
	int offset = px * y_indx;
	// Make sure offset doesn't exceed maximum available spaces
	if (offset > ((height-2)-vsize)) offset = (height-2)-vsize;
	return offset;
}

/*
 * Calculates the offset for the horizontal scrollbar thumb based on 
 * the current number of left/right keypresses (x_indx) and the size
 * of the world and window. Offset is given from the left of the
 * scrollbar.
 *
 * RETURN: Horizontal scrollbar offset
 */
int window::get_hscroll_pos()
{
	// Calculate the offset from the left for the scrollbar thumb
	double px = (double)((width-2)-hsize)/(w.get_width()-width);
	int offset = px * x_indx;
	// Make sure offset doesn't exceed maximum available spaces
	if (offset > ((width-2)-hsize)) offset = (width-2)-hsize;
	return offset;
}

/*
 * Moves the window up one position, adjusts window state accordingly.
 */
void window::scroll_up()
{
	// Move anchor up
	if (anchor_y+1 > w.get_anchor_y()) return;
	anchor_y++;
	if (y_indx-1 >= 0) y_indx--; 
}

/*
 * Moves the window down one position, adjusts window state accordingly.
 */
void window::scroll_down()
{
	// Move anchor down
	if ((anchor_y-((int)height-1))-1 <= w.get_anchor_y()-(int)w.get_height()) return;
	anchor_y--;
	y_indx++;
}

/*
 * Moves the window left one position, adjusts window state accordingly.
 */
void window::scroll_left()
{
	// Move anchor left
	if (anchor_x-1 < w.get_anchor_x()) return;
	anchor_x--;
	if (x_indx-1 >= 0) x_indx--;
}

/*
 * Moves the window right one position, adjusts window state accordingly.
 */
void window::scroll_right()
{
	// Move anchor right
	if ((anchor_x+((int)width-1))+1 >= w.get_anchor_x()+(int)w.get_width()) return;
	anchor_x++;
	x_indx++;
}
