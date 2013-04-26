#ifndef CONFIG_H
#define CONFIG_H

#include <vector>

class config {
	int *range_xl, *range_xh;
	int *range_yl, *range_yh;
	std::vector<int> alive;
	public:
		config();
		~config();
		inline int getXL() { return *range_xl; }
		inline int getXH() { return *range_xh; }
		inline int getYL() { return *range_yl; }
		inline int getYH() { return *range_yh; }
		void setX(int _l, int _h);
		void setY(int _l, int _h);
		void add(int _x, int _y);
		inline std::vector<int>& getAlive() { return alive; }
		// For debugging:
		void print();
};

#endif
