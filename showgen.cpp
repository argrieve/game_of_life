#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <getopt.h>
#include <string.h>

using namespace std;

bool parse_lh(char *in1, char *in2, int *low, int *high);
void show_help();

int main(int argc, char *argv[]) 
{
	// Store values of command line args
	bool isASCII = true;
	char *filename = NULL;
	int num_gens = 0;
	int tx_l = 0;
	int tx_h = 9;
	int ty_l = 0;
	int ty_h = 9;
	int wx_l = 0;
	int wx_h = 9;
	int wy_l = 0;
	int wy_h = 9;

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
				break;

			case '?':
				cerr << "Illegal switch detected. For help, use '-h'.\n";
				return 1;

			default:
				show_help();
				return 0;
		}
	}
	// Debugging
	cout << "isASCII: " << isASCII << '\n';
	cout << "filename: " << filename << '\n';
	cout << "gens: " << num_gens << '\n';
	cout << "tx: " << tx_l << " to " << tx_h << '\n';
	cout << "ty: " << ty_l << " to " << ty_h << '\n';
	cout << "wx: " << wx_l << " to " << wx_h << '\n';
	cout << "wy: " << wy_l << " to " << wy_h << '\n';

	return 0;
}

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

void show_help()
{
	cout << "Program help goes here.\n";
}
