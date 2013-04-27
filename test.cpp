#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cctype>
#include "config.h"
#include "reader.h"
#include "world.h"

using namespace std;

int main()
{
	config c;

	reader r;
	r.read(c, "test.aut");

	//c.print();

	world w(c);
	w.print_gen();

	w.next_gen();
	w.print_gen();

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
