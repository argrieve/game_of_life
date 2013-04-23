#include <stdlib.h>
#include <iostream>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

bool parse_lh(char *input, unsigned int *low, unsigned int *high);
void show_help();

int main(int argc, char *argv[]) 
{
	// Store values of command line args
	bool isASCII = true;
	char *filename = NULL;
	int num_gens = 0;
	unsigned int tx_l = 0;
	unsigned int tx_h = 9;
	unsigned int ty_l = 0;
	unsigned int ty_h = 9;
	unsigned int wx_l = 0;
	unsigned int wx_h = 9;
	unsigned int wy_l = 0;
	unsigned int wy_h = 9;

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
					std::cerr << "Switch -g must be followed by a positive integer value.\n";
					return 1;
				}
				num_gens = atoi(optarg);
				break;

			case 'h':
				show_help();
				return 0;

			case 'w':
				if(!parse_lh(optarg, &tx_l, &tx_h)) {
					std::cerr << "Invalid range for switch -tx.\n";
					return 1;
				}
				break;

			case 'x':
				if(!parse_lh(optarg, &ty_l, &ty_h)) {
					std::cerr << "Invalid range for switch -ty.\n";
					return 1;
				}
				break;

			case 'y':
				if(!parse_lh(optarg, &wx_l, &wx_h)) {
					std::cerr << "Invalid range for switch -wx.\n";
					return 1;
				}
				break;

			case 'z':
				if(!parse_lh(optarg, &wy_l, &wy_h)) {
					std::cerr << "Invalid range for switch -wy.\n";
					return 1;
				}
				break;

			case '?':
				std::cerr << "Illegal switch detected. For help, use '-h'.\n";
				return 1;

			default:
				show_help();
				return 0;
		}
	}
	// Debugging
	std::cout << "isASCII: " << isASCII << '\n';
	std::cout << "filename: " << filename << '\n';
	std::cout << "gens: " << num_gens << '\n';
	std::cout << "tx: " << tx_l << " to " << tx_h << '\n';
	std::cout << "ty: " << ty_l << " to " << ty_h << '\n';
	std::cout << "wx: " << wx_l << " to " << wx_h << '\n';
	std::cout << "wy: " << wy_l << " to " << wy_h << '\n';

	return 0;
}

bool parse_lh(char *input, unsigned int *low, unsigned int *high)
{
	if (strstr(input, "-")) return false;
	sscanf(input, "%d,%d", low, high);
	if (*low >= *high) return false;
	return true;
}

void show_help()
{
	std::cout << "Program help goes here.\n";
}
