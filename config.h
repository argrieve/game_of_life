#ifndef CONFIG_H
#define CONFIG_H

#include "coord.h"
#include <vector>

class config {
	coord *x_range, *y_range;
	std::vector<coord> alive;
	public:
		config();
		inline coord getX() { return x_range; }
		inline coord getY() { return y_range; }
		void setX(int _l, int _h);
		void setY(int _l, int _h);
		void add(int _x, int _y);
		std::vector<coord>& getAlive();
		// For debugging:
		void print();
};

#endif
