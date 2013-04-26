#ifndef READER_H
#define READER_H

#include <vector>
#include "config.h"

class reader {
	std::string data;
	public:
		reader();
		void read(config &cnfg, char *fname);
	private:
		void remove_comments();
		void set_range(config &cnfg, char c);
		void set_living(config &cnfg);
};

#endif
