#include "terrain.h"

terrain::terrain(range _x, range _y)
: x(_x), y(_y)
{
	carr = new cell*[x.getSpread()];
	for (int i=0; i<x.getSpread(); i++) carr[i] = new cell[y.getSpread()]; 
}

terrain::~terrain()
{
	for (int i=0; i<x.getSpread(); i++) delete[] carr[i];
	delete[] carr;
}

cell& terrain::get_cell(coord point)
{
	// Adjust x as needed
	int val_x =  point.getX() + abs(x.getLow());

	// Adjust y as needed
	int val_y = point.getY() + abs(y.getLow());

	return carr[val_x][val_y];
}
