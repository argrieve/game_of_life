#ifndef CELL_H
#define CELL_H

class cell {
	bool curr, next;
	char c;
	public:
		cell() {
			curr = false;
			next = false;
		}
		inline void update() {
			curr = next;
		}
		inline void set_state(bool isAlive) {
			next = isAlive;
		}
		inline void set_char(char _c) {
			c = _c;
		}
		inline bool isAlive() {
			return curr;
		}
};

#endif
