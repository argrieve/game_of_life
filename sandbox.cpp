#include <fstream>
#include <iostream>
#include <sstream>
#include "coord.h"
#include <vector>
#include <cctype>

using namespace std;

void remove_comments(string &str);
coord get_range(char c, string &str);
vector<coord> get_living(string &str);

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
	get_living(str);
	//cout << "X: (" << x.getX() << ", " << x.getY() << ")\n";
	//cout << "Y: (" << y.getX() << ", " << y.getY() << ")\n";
	//cout << str;

	return 0;
}

void remove_comments(string &str)
{
	unsigned int found1, found2;
	while (1) {
		// Find next comment
		found1 = str.find("#");
		if (found1 == string::npos || found1 > str.size()) break;
		
		// Find the end of the comment
		found2 = str.find("\n", found1+1);

		// Erase the comment
		str.erase(found1, found2-found1);
	}
	return;
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

vector<coord> get_living(string &str)
{
	vector<coord> alive;
	unsigned int start, end;

	// Check if the keyword exists
	start = str.find("Initial");
	if (start >= str.size()) return alive; 

	// Find the start and end index of the "Initial" statement
	start = str.find("{", start+7);
	end = str.find("}", start+1);
	// Make sure a complete statement exists
	if (start >= str.size() || end >= str.size()) return alive;	

	int x, y;
	bool done = false;
	istringstream stream(str.substr(start, end-start+1));
	
	while (stream.good()) {
		// Find the next 'Y' char
		if (stream.peek() == 'Y') {
			done = false;

			// Process the column of alive cells (current row in .aut file)
			while (!done) {
				// Grab the y coordinate
				if (isdigit(stream.peek()) || stream.peek() == '-') {
					stream >> y;

					// Grab the x coordinates
					while (1) {
						if (isdigit(stream.peek()) || stream.peek() == '-') {
							stream >> x;	
							//cout << "( " << y << ", " << x << ")" << endl;
							alive.push_back(coord(x,y));
						}
						else if (stream.peek() == ';') break;
						else stream.get();
					} // End x coordinates

					done = true;
				}
				else stream.get();
			} // End processing row

		}
		else stream.get();
	}

	return alive;	
}
