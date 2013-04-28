#include "window.h"
#include <iostream>

using namespace std;

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

	cout << "anchors: " << anchor_x << ", " << anchor_y << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;
}

void window::print_world(world &w, bool ascii)
{
	// Print ASCII representation
	if (ascii) print_ascii(w);

	// Print .aut format
	else print_aut(w);

	return;
}

void window::print_ascii(world &w)
{
	// Determine terrain's cartesian coordinates
	int ter_x_start = w.get_anchor_x();
	int ter_x_end = ter_x_start + w.get_width() - 1;
	int ter_y_start = w.get_anchor_y();
	int ter_y_end = ter_y_start - w.get_height() + 1;
	
	cout<< "ter_x_start: " << ter_x_start << endl;
	cout<< "ter_x_end  : " << ter_x_end << endl;
	cout<< "ter_y_start: " << ter_y_start << endl;
	cout<< "ter_y_end  : " << ter_y_end << endl;

	// Loop through window
	for (int i=anchor_y; i>(int)(anchor_y-height); i--) {
		for (int j=anchor_x; j<(int)(anchor_x+width); j++) {
			// Inside terrain
			if (i <= ter_y_start && i >= ter_y_end && j >= ter_x_start && j <= ter_x_end) {
				if(w.get_cell(j, i)) cout << "1";
				else cout << "~";
			}
			// Outside terrain
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

void window::print_aut(world &w)
{
	// Print generation number as a comment
	cout << "#\n" << "# Generation: " << w.curr_gen() << "\n#\n"; 
	
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
