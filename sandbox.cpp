#include <stdlib.h>
#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>
#include "coord.h"

using namespace std;

void remove_comments(string &str);
coord get_range(char c, string &str);

int main(int argc, char **argv)
{
	ifstream foo(argv[1]);
	istream fin(cin.rdbuf());

	if (argc > 1) {
		fin.rdbuf(foo.rdbuf());
	}

	// Get length of the file
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg (0, fin.beg);

	//cout << length << endl;

	char *buffer = new char[length];

	fin.read(buffer, length);
	foo.close();

	string str(buffer);
	delete[] buffer;

	remove_comments(str);
	coord x = get_range('x', str);
	coord y = get_range('y', str);

	cout << "X: (" << x.getX() << ", " << x.getY() << ")\n";
	cout << "Y: (" << y.getX() << ", " << y.getY() << ")\n";

	//cout << str;

	return 0;
}

void remove_comments(string &str)
{
	unsigned int found1, found2;
	while (1) {
		found1 = str.find("#");
		if (found1 == string::npos || found1 > str.size()) break;
		found2 = str.find("\n", found1+1);
		str.erase(found1, found2-found1);
	}
}

coord get_range(char c, string &str)
{
	// Find the range keyword
	unsigned int indx1;
	if (c == 'x' || c == 'X') indx1 = str.find("Xrange");
	else indx1 = str.find("Yrange");

	// Find the end of the keyword statement
	unsigned int indx2 = str.find(";", indx1+1);
	
	// Parse the integers out of it
	istringstream stream(str.substr(indx1+6, indx2-indx1));
	int low, high;
	stream >> low >> high;

	return coord(low, high);	
}
