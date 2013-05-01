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
window::window(int wx_l, int wx_h, int wy_l, int wy_h)
{
	width = 0;
	height = 0;

	// Set x anchor and width
	anchor_x = wx_l;
	for (int i=anchor_x; i<=wx_h; i++) width++;

	// Set y anchor and height
	anchor_y = wy_h;
	for (int i=wy_l; i<=anchor_y; i++) height++;
}

/*
 * Print the world in the specified format to stdout
 *
 * INPUT: &w World class to print
 * INPUT: ascii Output in ASCII format if true, otherwise .aut format
 */
void window::print_world(world &w, bool ascii)
{
	// Print ASCII representation
	if (ascii) print_ascii(w);

	// Print .aut format
	else print_aut(w);

	return;
}

/*
 * Print the world in ASCII format
 *
 * INPUT: &w World class to print
 */
void window::print_ascii(world &w)
{
	// Determine terrain's cartesian coordinates
	int ter_x_start = w.get_anchor_x();
	int ter_x_end = ter_x_start + w.get_width() - 1;
	int ter_y_start = w.get_anchor_y();
	int ter_y_end = ter_y_start - w.get_height() + 1;

	// Loop through window
	for (int i=anchor_y; i>(int)(anchor_y-height); i--) {
		for (int j=anchor_x; j<(int)(anchor_x+width); j++) {
			// Inside terrain
			if (i <= ter_y_start && i >= ter_y_end && j >= ter_x_start && j <= ter_x_end) {
				if(w.get_cell(j, i)) cout << w.get_alive_char();
				else cout << w.get_dead_char();
			}
			// Outside terrain
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

/*
 * Print the world in .aut format
 *
 * INPUT: &w World class to print
 */
void window::print_aut(world &w)
{
	// Print generation number as a comment
	//cout << "#\n" << "# Generation: " << w.curr_gen() << "\n#\n"; 
	
	// Print the name
	cout << "Name \"" << w.get_name() << "\"\n";

	// Print dead/alive characters
	cout << "Chars " << (int)w.get_dead_char() << ", " << (int)w.get_alive_char() << ";\n";

	// Print colors
	char *ptr = w.get_dead_color();
	unsigned char r = ptr[0];
	unsigned char g = ptr[1];
	unsigned char b = ptr[2];
	printf("Colors (%d, %d, %d)", r, g, b);
	ptr = w.get_alive_color();
	r = ptr[0];
	g = ptr[1];
	b = ptr[2];
	printf(", (%d, %d, %d);\n", r, g, b);

	// Determine if window is inside terrain or outside
	int x_start, x_end;
	int y_start, y_end;

	// X coordinates
	if (anchor_x < w.get_anchor_x()) x_start = w.get_anchor_x();
	else x_start = anchor_x;
	if ((int)(anchor_x+width) > (int)(w.get_anchor_x()+w.get_width())) 
		x_end = (int)(w.get_anchor_x() + w.get_width());
	else x_end = (int)(anchor_x+width);

	// Y coordinates
	if (anchor_y > w.get_anchor_y()) y_start = w.get_anchor_y();
	else y_start = anchor_y;
	if ((int)(anchor_y-height) < (int)(w.get_anchor_y()-w.get_height()))
		y_end = (int)(w.get_anchor_y()-height);
	else y_end = (int)(anchor_y-height);

	// Range keywords
	cout << "Xrange " << x_start << " " << x_end-1 << ";\n";
	cout << "Yrange " << y_end+1 << " " << y_start << ";\n";
	
	// Initial keyword
	cout << "Initial {\n";

	for (int i=y_start; i>y_end; i--) {
		// Search each column for 'alive' cells
		for (int j=x_start; j<x_end; j++) {
			if (w.get_cell(j, i)) {
				print_col(w, i, x_start, x_end); 
				break;
			}
		} // end width loop
	} // end height loop
	
	cout << "};\n";

	return;
}

/*
 * Print a column that has 'alive' cells in .aut format
 *
 * INPUT: &w World class to print
 * INPUT: y Column number that contains alive cells
 * INPUT: start_x X value to start searching at
 * INPUT: end_x X value to stop searching at
 */
void window::print_col(world &w, int y, int start_x, int end_x)
{
	cout << "  Y = " << y << " :   ";

	// Find all alive cells in the column
	bool first = true;
	for (int i=start_x; i<end_x; i++) {
		// Found an live cell
		if (w.get_cell(i, y)) {
			// Don't print a comma if it is the first alive cell
			if (first) { cout << i;	first = false; }
			else cout << ", " << i;
		}
	}

	cout << ";\n";
}
