/*
 * ComS 229 Project 2: showgen
 * Spring 2013
 * Alex Grieve
 *
 * reader.cpp
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "reader.h"

using namespace std;

/*
 * Default constructor
 */
reader::reader() 
{ }

/*
 * Parse a file and store attributes in a config class/file.
 *
 * INPUT: &cnfg Config class to store attributes in
 * INPUT: *fname File name of the .aut file
 */
void reader::read(config &cnfg, char *fname)
{
	// Read from the appropriate location
	filebuf fb;
	istream fin(cin.rdbuf());
	if (NULL != fname) {
		fb.open(fname, ios::in);
		fin.rdbuf(&fb);
	}
	
	// Get length of the file
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, fin.beg);

	// Read file into a buffer
	char *buffer = new char[length];
	fin.read(buffer, length);

	// Now copy buffer into our string
	data.append(buffer);
	
	// Clean up
	delete[] buffer;
	if (fb.is_open()) fb.close();

	// Set up the config file object
	remove_comments();
	set_name(cnfg, fname);
	set_chars(cnfg);
	set_colors(cnfg);
	set_range(cnfg, 'x');
	set_range(cnfg, 'y');
	set_living(cnfg);

	return;
}

/*
 * Removes comments from a .aut file (makes parsing easier)
 */
void reader::remove_comments()
{
	int indx1, indx2;

	while (1) {
		// Find next comment
		indx1 = data.find("#");
		if (indx1 == string::npos || indx1 > data.size()) break;

		// Find the end of the comment
		indx2 = data.find("\n", indx1+1);

		//Erase the comment
		data.erase(indx1, indx2-indx1);
	}

	return;
}

/*
 * Sets the name of the simulation. If no name is specified in
 * the .aut file, the .aut filename is used instead.
 * 
 * INPUT: &cnfg Config class to store name
 * INPUT: *fname Name of the .aut file
 */
void reader::set_name(config &cnfg, char *fname)
{
	// Find the name keyword
	int indx1 = data.find("Name");
	if (indx1 == string::npos) {
		cnfg.set_name(fname);
		return;
	}
	
	// Find start and ending quotes
	indx1 = data.find("\"", indx1+1);
	int indx2 = data.find("\"", indx1+1);

	// Parse the name out
	const char *name = data.substr(indx1+1, indx2-indx1-1).c_str();

	// Save to config
	cnfg.set_name(name);
}

/*
 * Sets the characters used to represent alive and dead cells.
 *
 * INTPUT: &cnfg Config file to store characters
 */
void reader::set_chars(config &cnfg)
{
	// Check for the Chars keyword
	int indx1 = data.find("Chars");
	if (indx1 == string::npos) return;

	// Locate the alive/dead characters
	int indx2 = data.find(";", indx1+1);
	
	// Parse the ASCII values
	string str(data.substr(indx1+6, indx2-indx1));
	str.erase(str.find(";"), 1);
	str.erase(str.find(","), 1);
	istringstream stream(str);
	int one, two;
	stream >> one >> two;	

	// Save to config
	cnfg.set_chars((char)one, (char)two);
}

/*
 * Sets the colors used to represent alive and dead cells.
 *
 * INPUT: &cnfg Config file to store characters
 */
void reader::set_colors(config &cnfg)
{
	// Check for the Colors keyword
	int indx1 = data.find("Colors");
	if (indx1 == string::npos) return;
	
	// Find dead RGB
	indx1 = data.find("(", indx1+1);
	int indx2 = data.find(")", indx1+1);
	string str1(data.substr(indx1+1, indx2-indx1-1));
	str1.erase(str1.find(","),1);
	str1.erase(str1.find(","),1);

	// Parse dead RGB
	int dr, dg, db;
	istringstream stream(str1);
	stream >> dr >> dg >> db;

	// Find alive RGB
	indx1 = data.find("(",indx1+1);
	indx2 = data.find(")",indx1+1);
	string str2(data.substr(indx1+1, indx2-indx1-1));
	str2.erase(str2.find(","),1);
	str2.erase(str2.find(","),1);

	// Parse alive RGB
	int ar, ag, ab;
	istringstream stream2(str2);
	stream2 >> ar >> ag >> ab;

	// Save to config
	cnfg.set_colors(dr, dg, db, ar, ag, ab);
}

/*
 * Set the range of the simulation.
 *
 * INPUT: &cnfg Config file to store ranges to
 * INPUT: c Character to indicate whether to parse X or Y coordinates
 */
void reader::set_range(config &cnfg, char c)
{
	// Find the range keyword
	int indx1;
	if (c == 'x' || c == 'X') indx1 = data.find("Xrange");
	else indx1 = data.find("Yrange");

	// Find the end of the keyword statement
	int indx2 = data.find(";", indx1+1);
	
	// Parse the integers out of it
	istringstream stream(data.substr(indx1+6, indx2-indx1));
	int low, high;
	stream >> low >> high;

	// Save to config class
	if (c == 'x' || c == 'X') cnfg.setX(low, high);
	else cnfg.setY(low, high);

	return;
}

/*
 * Set the initial 'alive' cells.
 * 
 * INPUT: &cnfg Config file to store initial 'alive' cells
 */
void reader::set_living(config &cnfg)
{
	int start, end;

	// Check if the keyword exists
	start = data.find("Initial");
	if (start == string::npos || start >= data.size()) return; 

	// Find the start and end index of the "Initial" statement
	start = data.find("{", start+7);
	end = data.find("}", start+1);
	// Make sure a complete statement exists
	if (start == string::npos || start >= data.size() || end == string::npos || end >= data.size()) return;	

	int x, y;
	bool done = false;
	istringstream stream(data.substr(start, end-start+1));
	
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
							cnfg.add(x, y);
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

	return;
}
