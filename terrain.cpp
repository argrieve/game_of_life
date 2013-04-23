#include "terrain.h"
#include "cell.h"



terrain::terrain(unsigned int _x, unsigned int _y)
{
	x = _x;
	y = _y;
	carr = new cell*[x];
	for (int i=0; i<x; i++) carr[i] = new cell[y]; 
}

terrain::~terrain()
{
	for (int i=0; i<x; i++) delete[] carr[i];
	delete[] carr;
}

cell& terrain::get_cell(unsigned int _x, unsigned int _y)
{
	return carr[_x][_y];
}
