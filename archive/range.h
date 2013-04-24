#ifndef RANGE_H
#define RANGE_H

#include <stdlib.h>

class range {
	int low, high;
	public:
		range(int _low, int _high) {
			low = _low;
			high = _high;
		}
		inline int getLow() { return low; }
		inline int getHigh() { return high; }
		inline int getSpread() { return abs(high) + abs(low) + 1; }
};

#endif
