#include "rules.h"

rules::rules(char _alive, char _dead)
{
	alive = _alive;
	dead = _dead;
}

void rules::update_cell(cell c, unsigned int neighbors)
{
	if(c.isAlive()) {
		// Cell lives if there are 2 or 3 neighbors
		if(neighbors == 2 || neighbors == 3) c.set_state(true);

		// Cell dies if neighbors < 2 (loneliness)
		// Cell dies if neighbors > 3 (overpopulation)
		else c.set_state(false);
	}
	else {
		// Cell lives if neighbors = 3 (reproduction)
		if (neighbors == 3) c.set_state(true);

		else c.set_state(false);
	}
	
	return;
}
