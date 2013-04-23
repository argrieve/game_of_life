#ifndef RULES_H
#define RULES_H

#include "cell.h"

class rules {
	char alive;
	char dead;
	public:
		rules(char _alive, char _dead);
		void update_cell(cell &c, unsigned int neighbors);
};

#endif
