#include <iostream>
#include <getopt.h>

int main(int argc, char *argv[]) 
{
	struct option long_options[] =
	{
		{"tx", required_argument, 0, 'x'},
		{0, 0, 0, 0}
	};

	int option_index = 0;
	int opt = 0;
	opterr = 0;

	while ((opt = getopt_long_only(argc, argv, "", long_options, &option_index)) != -1)
	{
		switch (opt) {
			case 'x':
				std::cout << optarg << '\n';
				break;
			default:
				std::cout << "No options found.\n";
				break;
		}
	}

	return 0;
}
