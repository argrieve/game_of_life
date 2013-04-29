/*
 * ComS 229 Project 2: showgen
 * Spring 2013
 * Alex Grieve
 *
 * showgen.cpp
 *
 * Compile with Makefile: make
 * Alternatively, compile with the following commands:
 *  g++ -c window.cpp
 *  g++ -c reader.cpp
 *  g++ -c world.cpp
 *  g++ -c config.cpp
 *  g++ -c showgen.cpp
 *  g++ -o showgen showgen.o config.o world.o reader.o window.o 
 */

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <getopt.h>
#include <string.h>
#include "reader.h"
#include "config.h"
#include "world.h"
#include "window.h"

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
	bool isASCII = true;
	char *filename = NULL;
	int num_gens = 0;
	bool tx_found = false;
	bool ty_found = false;
	bool wx_found = false;
	bool wy_found = false;

	// Terrain and window defaults	
	int tx_l = -10;
	int tx_h = 10;
	int ty_l = -10;
	int ty_h = 10;
	int wx_l = tx_l;
	int wx_h = tx_h;
	int wy_l = ty_l;
	int wy_h = ty_h;

	// Set up list of command line options to parse
	struct option long_options[] =
	{
		{"tx", required_argument, 0, 'w'},
		{"ty", required_argument, 0, 'x'},
		{"wx", required_argument, 0, 'y'},
		{"wy", required_argument, 0, 'z'},
		{0, 0, 0, 0}
	};

	int option_index = 0;
	int opt = 0;
	opterr = 0;

	// Parse command line options
	while ((opt = getopt_long_only(argc, argv, "af:g:h", long_options, &option_index)) != -1)
	{
		switch (opt) {
			case 'a':
				isASCII = false;
				break;

			case 'f':
				filename = argv[optind-1];
				break;
			
			case 'g':
				if (strstr(optarg, "-")) {
					cerr << "Switch -g must be followed by a positive integer value.\n";
					return 1;
				}
				num_gens = atoi(optarg);
				break;

			case 'h':
				show_help();
				return 0;

			case 'w':
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
			
			case 'x':
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

			case 'y':
				if (optind == argc) {	
					if(!parse_lh(optarg, optarg, &wx_l, &wx_h)) {
						cerr << "Invalid range for swtich -wx.\n";
						return 1;
					}
				}
				else { 
					if(!parse_lh(optarg, argv[optind], &wx_l, &wx_h)) {
						cerr << "Invalid range for switch -wx.\n";
						return 1;
					}
				}
				wx_found = true;
				break;

			case 'z':
				if (optind == argc) {	
					if(!parse_lh(optarg, optarg, &wy_l, &wy_h)) {
						cerr << "Invalid range for swtich -wy.\n";
						return 1;
					}
				}
				else { 
					if(!parse_lh(optarg, argv[optind], &wy_l, &wy_h)) {
						cerr << "Invalid range for switch -wy.\n";
						return 1;
					}
				}
				wy_found = true;
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

	// Set window ranges
	if (!wx_found) { wx_l = cnfg->getXL(); wx_h = cnfg->getXH(); }
	if (!wy_found) { wy_l = cnfg->getYL(); wy_h = cnfg->getYH(); }

	// Build world
	world w(*cnfg);

	// Perform specified number of generations
	for (int i=0; i<num_gens; i++)
		w.next_gen();

	// Write output file
	window win(wx_l, wx_h, wy_l, wy_h);
	win.print_world(w, isASCII);

	return 0;
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
	cout << "\nSHOWGEN\n\n";
	cout << "\tThis program performs a simple simulation of John Conway's\n";
	cout << "\tGame of Life. A .aut file is read (either as an argument or\n";
	cout << "\tredirected from stdin) and used as a starting generation for\n";
	cout << "\tthe simulation. The world is updated by a specified number of\n";
	cout << "\tgenerations (see SWITCHES section), and the resulting state\n";
	cout << "\tof the world is written to stdout.\n";

	// Usage information
	cout << "\n\nUSAGE\n\n";
	cout << "\t./showgen [-f <file>] [options]\n";
	cout << "\t./showgen [options] < <file>\n";

	// Legal switches
	cout << "\n\nSWITCHES\n\n";
	cout << "\t-a \tOutput in .aut format.\n\n";	
	cout << "\t-g \tSpecify the desired number of generations. Switch should\n";	
	cout << "\t   \tbe followed by a positive integer. If omitted, the number\n";	
	cout << "\t   \tof generations is zero.\n\n";	
	cout << "\t-h \tDisplay help and information.\n\n";
	cout << "\t-tx\tSet the x-range of the terrain. Switch should be followed\n";
	cout << "\t   \tby a coordinate pair, where each coordinate is seperated \n";
	cout << "\t   \tby a comma or a space. This switch will override any value\n";
	cout << "\t   \tfound in the .aut file.\n\n";
	cout << "\t-ty\tSet the y-range of the terrain. See switch '-tx' for more\n";
	cout << "\t   \tinformation.\n\n";
	cout << "\t-wx\tSet the x-range of the output window. Switch should be \n";
	cout << "\t   \tfollowed by a coordinate pair, where each coordinate is \n";
	cout << "\t   \tseperated by a comma or a space. If omitted, the window\n";
	cout << "\t   \tdefaults to the x-range of the terrain.\n\n";
	cout << "\t-wy\tSet the y-range of the output window. See switch '-wx' for\n";
	cout << "\t   \tmore information.\n\n";
}
