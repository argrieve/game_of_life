#include <stdlib.h>
#include <iostream>
#include <vector>
#include "coord.h"

using namespace std;

int main()
{
	vector<coord> myvect;

	for (int i=0; i<10; i++) myvect.push_back(coord(i, 2*i));

	cout << "Num elements: " << myvect.size() << "\n";

	for (int i=0; i<myvect.size(); i++)
		cout << "(" << myvect.at(i).getX() << ", " << myvect.at(i).getY() << ")\n";

	cout << "Done.\n";

	return 0;
}

/*
int main()
{
	vector<int> myVect;

	for (int i=0; i<10; i++) myVect.push_back(i);
	cout << "Num elements in myVect: " << myVect.size() << "\n";

	cout << "Elements in myVect:\n";

	
	for (int i=0; i<myVect.size(); i++)
		cout << myVect.at(i) << " ";
	
	cout << '\n';

	cout << "done.\n";
	return 0;
}
*/
