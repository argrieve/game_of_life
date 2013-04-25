#ifndef COORD_H
#define COORD_h

class coord {
	int x, y;
	public:
		coord(int _x, int _y) {
			x = _x; 
			y = _y;
		}
		inline int getX() { return x; }
		inline int getY() { return y; }
};

#endif
