#ifndef CONFIG_H
#define CONFIG_H

#include "stdlib.h"
#include <string>
#include <vector>

class config {
	std::string name;
	char *dead, *alive;
	char *color_dead, *color_alive;
	int *range_xl, *range_xh;
	int *range_yl, *range_yh;
	std::vector<int> alive_cells;
	public:
		config();
		~config();
		inline std::string get_name() { return name; }
		inline char get_dead() { return *dead; }
		inline char get_alive() { return *alive; }
	//	inline char* get_dead_colors { return color_dead; }
	//	inline char* get_alive_colors { return color_alive; }
		inline int getXL() { return *range_xl; }
		inline int getXH() { return *range_xh; }
		inline int getYL() { return *range_yl; }
		inline int getYH() { return *range_yh; }
		void set_name(const char* str);
		void set_chars(char d, char a);
		void set_colors(char *d, char *a);
		void setX(int _l, int _h);
		void setY(int _l, int _h);
		void add(int _x, int _y);
		inline std::vector<int>& getAlive() { return alive_cells; }
		// For debugging:
		void print();
};

#endif
