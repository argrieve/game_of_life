#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	std::ifstream in("test.aut");
	std::string str;

	if (in.is_open())
		while (in.good()) {
			getline(in, str);
			cout << str  << '\n';
		}
	
	cout << "Done.\n";

	return 0;
}

