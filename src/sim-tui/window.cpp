/*
 * ComS 229 Project 2: showgen
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

	//printf("width: %d, height: %d\nanchors: %d, %d\n", width, height, anchor_x, anchor_y);
}

int window::get_cell(int x, int y)
{
	// Convert screen coordinates
	int cartx = anchor_x + x;
	int carty = anchor_y - y;

	// Check if we are in range
	if (cartx < w.get_anchor_x() || cartx >= (int)(w.get_anchor_x()+w.get_width())) return -1;
	if (carty > w.get_anchor_y() || carty <= (int)(w.get_anchor_y()-w.get_height())) return -1;

	return w.get_cell(cartx, carty);
}

void window::scroll_up()
{
	// Move anchor up
	if (anchor_y+1 > w.get_anchor_y()) return;
	anchor_y++;
}

void window::scroll_down()
{
	// Move anchor down
	if ((anchor_y-(height-1))-1 <= w.get_anchor_y()-w.get_height()) return;
	anchor_y--;
}

void window::scroll_left()
{
	// Move anchor left
	if (anchor_x-1 < w.get_anchor_x()) return;
	anchor_x--;
}

void window::scroll_right()
{
	// Move anchor right
	if ((anchor_x+(width-1))+1 >= w.get_anchor_x()+w.get_width()) return;
	anchor_x++;
}

int window::get_vscroll_size()
{
	// Don't need a scroll bar
	if (height >= w.get_height()) return -1;

	// 1 scroll character = X world chars
	double step = (double)(height-2)/w.get_height();
	
	// Scrollbar size = step size*number of characters in the window
	return (int)(step * height);
}

int window::get_hscroll_size()
{
	// Don't need a scroll bar
	if (width >= w.get_width()) return -1;

	// 1 scroll character = X world chars
	double step = (double)(width-2)/w.get_width();
	
	// Scrollbar size = step size*number of characters in the window
	return (int)(step * width);

}

int window::get_vscroll_pos()
{
	return -1;
}

int window::get_hscroll_pos()
{
	return -1;
}
