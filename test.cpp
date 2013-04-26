#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cctype>
#include "config.h"

using namespace std;

int main()
{
	for (int i=0; i<9; i++) {
		config c;
		c.setX(-10, 10);
		c.setY(-20, 20);
		c.add(1,-1);
		c.add(2,-2);
		c.add(3,-3);
		c.add(4,-4);
		c.print();
	}
	return 0;
}

/*
int main()
{
	string str("Y = 2 : -1;"); 

	istringstream stream(str);

	int y;
//	for (int i=0; i<str.size(); i++) {
	while (stream.good()) {
		if (isdigit(stream.peek()) || stream.peek() == '-') {
			stream >> y;
			cout << "Y: " << y << endl;
		}
		else {
			stream.get();
		}
	}


	return 0;
}
*/

/*
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
*/
