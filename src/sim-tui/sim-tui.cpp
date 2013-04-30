/*
 * ComS 229 Project 2: sim-tui
 * Spring 2013
 * Alex Grieve
 *
 * sim-tui.cpp
 *
 * Compile with Makefile: make
 * Alternatively, compile with the following commands:
 *  g++ -c window.cpp
 *  g++ -c reader.cpp
 *  g++ -c world.cpp
 *  g++ -c config.cpp
 *  g++ -c sim-tui.cpp
 *  g++ -o sim-tui sim-tui.o config.o world.o reader.o window.o -lncurses
 */

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <getopt.h>
#include <string.h>
#include "reader.h"
#include "config.h"
#include "world.h"
#include <curses.h>
#include "window.h"

using namespace std;

/*******************************************************************/
/*											FUNCTION PROTOTYPES												 */
/*******************************************************************/

/*
 * Redraws the ncurses window with the current/updated state of the
 * world, window, and delay properties.
 *
 * INPUT: rows Number of rows in the current window
 * INPUT: cols Number of columns in the current window
 * INPUT: &w World object to write to screen
 * INPUT: &win Window object to view the world through
 * INPUT: delay Delay between successive world/screen updates
 */ 
void draw_window(int rows, int cols, world &w, window &win, int delay);

/* 
 * Draws the labels above and below the world to the window.
 *
 * INPUT: rows Number of rows in the current window
 * INPUT: cols Number of columns in the current window
 * INPUT: *name Name of the world/simulation
 * INPUT: gen Current generation
 * INPUT: delay Delay between successive world/screen updates
 */
void draw_labels(int rows, int cols, const char *name, int gen, int delay);

/*
 * Draws the world border to the window.
 *
 * INPUT: rows Number of rows in the current window
 * INPUT: cols Number of columns in the current window
 */
void draw_border(int rows, int cols);

/*
 * Draw scrollbars and their current positions to the window.
 *
 * INPUT: rows Number of rows in the current window
 * INPUT: cols Number of columns in the current window
 * INPUT: &win Window class that computes states for the scrollbars
 */
void draw_scrollbars(int rows, int cols, window &win);

/*
 * Gets the state of cells in the viewing window, and draws them to
 * the screen.
 *
 * INPUT: &w World object that contains dead/alive characters
 * INPUT: &win Window object to view the world through
 *
 */
void draw_cells(world &w, window &win);

/*
 * Parses a coordinate pair out of a string or a pair of strings (if
 * the coordinate pair is seperated by a space instead of a comma.)
 *
 * INPUT: *in1 First portion of the command string
 * INPUT: *in2 Second portion of the command string
 * INPUT: *low Place to store the lower coordinate
 * INPUT: *high Place to store the higher coordinate
 * RETURN: True if a valid coordinate pair was parsed, false otherwise
 */
bool parse_lh(char *in1, char *in2, int *low, int *high);

/*
 * Show the program help and information.
 */
void show_help();



/*******************************************************************/
/*													PROGRAM MAIN													*/
/*******************************************************************/
int main(int argc, char *argv[]) 
{
	// Store values of command line args
	bool isASCII = true;
	char *filename = NULL;
	int num_gens = 0;
	bool tx_found = false;
	bool ty_found = false;

	// Terrain defaults	
	int tx_l = -10;
	int tx_h = 10;
	int ty_l = -10;
	int ty_h = 10;

	// Set up list of command line options to parse
	struct option long_options[] =
	{
		{"tx", required_argument, 0, 'x'},
		{"ty", required_argument, 0, 'y'},
		{0, 0, 0, 0}
	};

	int option_index = 0;
	int opt = 0;
	opterr = 0;

	// Parse command line options
	while ((opt = getopt_long_only(argc, argv, "f:h", long_options, &option_index)) != -1)
	{
		switch (opt) {
			case 'f':
				filename = argv[optind-1];
				break;

			case 'h':
				show_help();
				return 0;

			case 'x':
				if (optind == argc)	{
					if(!parse_lh(optarg, optarg, &tx_l, &tx_h)) {
						cerr << "Invalid range for swtich -tx.\n";
						return 1;
					}
				}
				else { 
					if(!parse_lh(optarg, argv[optind], &tx_l, &tx_h)) {
						cerr << "Invalid range for switch -tx.\n";
						return 1;
					}
				}
				tx_found = true;
				break;
			
			case 'y':
				if (optind == argc) {	
					if(!parse_lh(optarg, optarg, &ty_l, &ty_h)) {
						cerr << "Invalid range for swtich -ty.\n";
						return 1;
					}
				}
				else { 
					if(!parse_lh(optarg, argv[optind], &ty_l, &ty_h)) {
						cerr << "Invalid range for switch -ty.\n";
						return 1;
					}
				}
				ty_found = true;
				break;

			case '?':
				cerr << "Illegal switch detected. For help, use '-h'.\n";
				return 1;

			default:
				show_help();
				return 0;
		}
	}

	// Read input file
	config *cnfg = new config();
	reader rd;
	rd.read(*cnfg, filename);

	// Override terrain ranges
	if (tx_found) cnfg->setX(tx_l, tx_h);
	if (ty_found) cnfg->setY(ty_l, ty_h);

	// Build world
	world w(*cnfg);

	/**********************/
	/* ` `BEGIN CURSES		*/
	/**********************/
	initscr();
  noecho();
	cbreak();
	keypad(stdscr, 1);
	
	// Window variables
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	rows--; cols--;
	int delay = 250;
	
	window win(cols-2, rows-5, w);

	// Draw the window (gen 0)
	draw_window(rows, cols, w, win, delay);

	// Main curses control loop
	bool done = false;
	while(!done) {
		int c = getch();
		switch (c) {
			case ERR: continue;
			case KEY_UP:
				win.scroll_up();
				draw_window(rows, cols, w, win, delay);
				break;
			case KEY_DOWN:
				win.scroll_down();
				draw_window(rows, cols, w, win, delay);
				break;
			case KEY_LEFT:
				win.scroll_left();
				draw_window(rows, cols, w, win, delay);
				break;
			case KEY_RIGHT:
				win.scroll_right();
				draw_window(rows, cols, w, win, delay);
				break;
			case 'Q':
			case 'q':
				done = true;
				break;
			case 'S':
			case 's':
				w.next_gen();	
				draw_window(rows, cols, w, win, delay);
				break;
			case '=':
			case '+':
				delay += 10;
				draw_window(rows, cols, w, win, delay);
				break;
			case '_':
			case '-':
				if (delay-10 >= 0) delay -= 10;
				draw_window(rows, cols, w, win, delay);
				break;
			case 'P':
			case 'p':
				// PLAY LOOP
				bool pdone = false;
				while (!pdone) {
					timeout(delay);
					w.next_gen();
					draw_window(rows, cols, w, win, delay);
					int cc = getch();
					switch (cc) {
						case ERR: continue;
						case KEY_UP:
							win.scroll_up();
							draw_window(rows, cols, w, win, delay);
							break;
						case KEY_DOWN:
							win.scroll_down();
							draw_window(rows, cols, w, win, delay);
							break;
						case KEY_LEFT:
							win.scroll_left();
							draw_window(rows, cols, w, win, delay);
							break;
						case KEY_RIGHT:
							win.scroll_right();
							draw_window(rows, cols, w, win, delay);
							break;
						case 'P':
						case 'p':
							pdone = true;
							break;
						case '=':
						case '+':
							delay += 10;
							draw_window(rows, cols, w, win, delay);
							break;
						case '_':
						case '-':
							if(delay-10 >= 0) delay -= 10;
							draw_window(rows, cols, w, win, delay);
							break;
						case 'Q':
						case 'q':
							pdone = true;
							done = true;
							break;
					}
				}
				break; // End PLAY loop
		};
	}

	endwin();
	return 0;
}



/*******************************************************************/
/*														FUNCTIONS													 	*/
/*******************************************************************/


/*
 * Redraws the ncurses window with the current/updated state of the
 * world, window, and delay properties.
 *
 * INPUT: rows Number of rows in the current window
 * INPUT: cols Number of columns in the current window
 * INPUT: &w World object to write to screen
 * INPUT: &win Window object to view the world through
 * INPUT: delay Delay between successive world/screen updates
 */ 
void draw_window(int rows, int cols, world &w, window &win, int delay)
{
	draw_labels(rows, cols, w.get_name().c_str(), w.curr_gen(), delay);
	draw_border(rows, cols);
	draw_scrollbars(rows, cols, win);
	draw_cells(w, win);
	curs_set(0);
	refresh();
}

/* 
 * Draws the labels above and below the world to the window.
 *
 * INPUT: rows Number of rows in the current window
 * INPUT: cols Number of columns in the current window
 * INPUT: *name Name of the world/simulation
 * INPUT: gen Current generation
 * INPUT: delay Delay between successive world/screen updates
 */
void draw_labels(int rows, int cols, const char *name, int gen, int delay)
{
	mvprintw(0, (cols-strlen(name))/2, "%s", name);
	mvprintw(1, 0, "Delay: %6d (+/-)", delay);	
	mvprintw(1, cols-(strlen("Generation")+10), "%s %10d", "Generation", gen);
	mvprintw(rows, 0, "(Q)uit");
	mvprintw(rows, cols/3-2, "(P)lay");
	mvprintw(rows, cols/2+cols/8, "(S)tep");
	mvprintw(rows, cols-strlen("Arrows:scroll"), "Arrows:scroll");

}

/*
 * Draws the world border to the window.
 *
 * INPUT: rows Number of rows in the current window
 * INPUT: cols Number of columns in the current window
 */
void draw_border(int rows, int cols)
{
	mvprintw(2,0,"+");
	for (int i=3; i<rows-1; i++) {
		mvprintw(i,0,"|");
		mvprintw(i,cols,"|");
	}
	mvprintw(rows-1,0,"+");	
	for (int i=1; i<cols; i++) {
		mvprintw(2,i,"-");
		mvprintw(rows-1,i,"-");
	}
	mvprintw(rows-1,cols,"+");
	mvprintw(2,cols,"+");
	return;
}

/*
 * Draw scrollbars and their current positions to the window.
 *
 * INPUT: rows Number of rows in the current window
 * INPUT: cols Number of columns in the current window
 * INPUT: &win Window class that computes states for the scrollbars
 */
void draw_scrollbars(int rows, int cols, window &win)
{
	int vsize = win.get_vscroll_size();
	int hsize = win.get_hscroll_size();

	// Draw vertical scroll bar
	if (vsize != -1) {
		// Place arrows
		mvprintw(3,cols, "^");
		mvprintw(rows-2,cols, "v");
		// Place scroller
		int offset = win.get_vscroll_pos();
		for (int i=offset; i<vsize+offset; i++) mvprintw(4+i,cols,"#");
	}

	// Draw horizontal scroll bar
	if (hsize != -1) {
		// Place arrows
		mvprintw(rows-1, 1, "<");
		mvprintw(rows-1, cols-1, ">");
		// Place scroller
		int offset = win.get_hscroll_pos();
		for (int i=offset; i<hsize+offset; i++) mvprintw(rows-1, 2+i, "#");
	}

	return;
}

/*
 * Gets the state of cells in the viewing window, and draws them to
 * the screen.
 *
 * INPUT: &w World object that contains dead/alive characters
 * INPUT: &win Window object to view the world through
 *
 */
void draw_cells(world &w, window &win)
{
	// Cell state/character variables
	char d = w.get_dead_char();
	char a = w.get_alive_char();
	char c;

	for (int i=0; i<win.get_height(); i++) {
		for (int j=0; j<win.get_width(); j++) {
			int ret = win.get_cell(j,i);
			if (ret == -1) continue; //no cell exists in terrain to print here
			else if(ret == 1) c=a;
			else c=d;
			mvaddch(i+3,j+1,c);
		}
	}

	return;
}

/*
 * Parses a coordinate pair out of a string or a pair of strings (if
 * the coordinate pair is seperated by a space instead of a comma.)
 *
 * INPUT: *in1 First portion of the command string
 * INPUT: *in2 Second portion of the command string
 * INPUT: *low Place to store the lower coordinate
 * INPUT: *high Place to store the higher coordinate
 * RETURN: True if a valid coordinate pair was parsed, false otherwise
 */
bool parse_lh(char *in1, char *in2, int *low, int *high)
{
	// Build string object
	string s;
	s += in1;
	s += " ";
	s += in2;

	// Replace first occurance of ","
	int i = s.find(",");
	if (i != string::npos) s.replace(i, 1, " ");

	// Use stream to parse integers from the string
	istringstream stream(s);
	stream >> *low >> *high;

	// Error check
	if (*low > *high) return false;

	return true;
}

/*
 * Show the program help and information.
 */
void show_help()
{
	// Program description
	cout << "\nSIM-TUI\n\n";
	cout << "\tThis program performs a simple simulation of John Conway's\n";
	cout << "\tGame of Life. A .aut file is read (either as an argument or\n";
	cout << "\tredirected from stdin) and used as a starting generation for\n";
	cout << "\tthe simulation. The current generation is displayed in the\n";
	cout << "\tterminal, and the generations can be controlled by the user.\n";
	cout << "\t(see CONTROLS section.)\n";
	
	// Usage information
	cout << "\n\nUSAGE\n\n";
	cout << "\t./sim-tui [-f <file>] [options]\n";

	// Legal switches
	cout << "\n\nSWITCHES\n\n";
	cout << "\t-h \tDisplay help and information.\n\n";
	cout << "\t-f \tSpecify a .aut file to read from. Filename must immediately\n";
	cout << "\t   \tfollow the switch.\n\n";
	cout << "\t-tx\tSet the x-range of the terrain. Switch should be followed\n";
	cout << "\t   \tby a coordinate pair, where each coordinate is seperated \n";
	cout << "\t   \tby a comma or a space. This switch will override any value\n";
	cout << "\t   \tfound in the .aut file.\n\n";
	cout << "\t-ty\tSet the y-range of the terrain. See switch '-tx' for more\n";
	cout << "\t   \tinformation.\n\n";

	// Controls
	cout << "\n\nCONTROLS\n\n";
	cout << "\t  q \tQuit the program.\n\n";
	cout << "\t  s \tStep to the next generation i+1.\n\n";
	cout << "\t  p \tAutomatically step to generation i+1 after time DELAY\n";
	cout << "\t    \tmilliseconds.\n\n";
	cout << "\t  + \tIncrement time delay.\n\n";
	cout << "\t  - \tDecrement time delay.\n\n";
	cout << "\tArrow\tMove viewing window (if world is larger than the\n";
	cout << "\t     \tprogram window.) Otherwise, no effect.\n\n";
}
