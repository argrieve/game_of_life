/*
 * ComS 229 Project 2: sim-gui
 * Spring 2013
 * Alex Grieve
 *
 * sim-gui.cpp
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
#include "grid.h"
#include <QtGui>
#include "controls.h"

using namespace std;

/*******************************************************************/
/*											FUNCTION PROTOTYPES												 */
/*******************************************************************/

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
	char *filename = NULL;
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
	world *w = new world(*cnfg);


	/**********************/
	/*			BEGIN QT  		*/
	/**********************/
	QApplication app(argc, argv);

	// Configure the grid/window
	Grid *grid = new Grid;

	// Set colors
	char *ptr = w->get_dead_color();
	grid->setDeadColor(QColor((unsigned char)ptr[0], (unsigned char)ptr[1], (unsigned char)ptr[2]));
	ptr = w->get_alive_color();
	grid->setAliveColor(QColor((unsigned char)ptr[0], (unsigned char)ptr[1], (unsigned char)ptr[2]));
	
	// Initialize grid with generation 0
	grid->setWorld(w);

	QScrollArea scroll;
	scroll.setWidget(grid);
	scroll.viewport()->setBackgroundRole(QPalette::Dark);
	scroll.viewport()->setAutoFillBackground(true);
	scroll.setWindowTitle(w->get_name().c_str());
	scroll.show();

	Controls *ctrl = new Controls;
	ctrl->show();

	QObject::connect(ctrl, SIGNAL(update_sig()), grid, SLOT(update_grid()));

	return app.exec();
}



/*******************************************************************/
/*														FUNCTIONS													 	*/
/*******************************************************************/

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
