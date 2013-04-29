/*
 * ComS 229 Project 2: showgen
 * Spring 2013
 * Alex Grieve
 *
 * reader.h
 */
 
#ifndef READER_H
#define READER_H

#include <vector>
#include "config.h"

/*
 * This class reads a .aut file and stores parsed
 * attributes into a config class/file.
 */
class reader {
	// Member variables
	std::string data;
	public:
		reader();
		// Main function to called to read file
		void read(config &cnfg, char *fname);
	private:
		// Helper functions to read specific attribtes
		void remove_comments();
		void set_name(config &cnfg, char *fname);
		void set_chars(config &cnfg);
		void set_colors(config &cnfg);
		void set_range(config &cnfg, char c);
		void set_living(config &cnfg);
};

#endif
