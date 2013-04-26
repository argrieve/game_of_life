#ifndef COORD_H
#define COORD_h

class coord {
	int *x, *y;
	public:
		coord();
		coord(int _x, int _y) {
			*x = _x; 
			*y = _y;
		}
		~coord();
		inline int getX() { return *x; }
		inline int getY() { return *y; }
		inline void setX(int _x) { *x = _x; };
		inline void setY(int _y) { *y = _y; };
};

#endif
