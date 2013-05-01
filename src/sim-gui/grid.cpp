/*
 * ComS 229 Project 2: sim-gui
 * Spring 2013
 * Alex Grieve
 *
 * grid.cpp
 */

#include <QtGui>

#include "grid.h"
#include <iostream>

Grid::Grid(QWidget *parent)
: QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	zoom = 8;
}

/*
 * Determine the preferred size of the widget
 *
 * RETURN: QSize object containing the perferred size
 */
QSize Grid::sizeHint() const
{
	QSize size = zoom * image.size();
	if (zoom >= 3)
		size += QSize(1, 1);
	return size;
}

/*
 * Set the QColor object for alive cells
 *
 * INPUT: newColor QColor object to assign to alive cells
 */
void Grid::setAliveColor(const QColor &newColor)
{
	aColor = newColor;
}

/*
 * Set the QColor object for dead cells
 *
 * INPUT: newColor QColor object to assign to dead cells
 */
void Grid::setDeadColor(const QColor &newColor)
{
	dColor = newColor;
}

/*
 * Set the zoom factor and update the grid accordingly
 *
 * INPUT newZoom New zoom value
 */
void Grid::setZoomFact(int newZoom)
{
	if (newZoom < 1)
		newZoom = 1;
	
	if (newZoom != zoom) {
		zoom = newZoom;
		update();
		updateGeometry();
	}
}

/*
 * Initialize the grid with the given world object
 *
 * INPUT: *ptr World object to map to the grid
 */
void Grid::setWorld(world *ptr)
{
	// Set the world pointer
	w = ptr;

	// Set the grid image
	image = QImage(w->get_width(), w->get_height(), QImage::Format_ARGB32);
	image.fill(dColor.rgb());

	// Initialize the grid with gen 0
	for (int i=0; i<w->get_height(); i++) {
		for (int j=0; j<w->get_width(); j++) {
			setCell(j, i, w->get_cell(j, i));
		}
	}
	update();
	updateGeometry();
}


/*
 * Update all cells to generation i+1, then update the grid window
 */
void Grid::update_grid()
{
	w->next_gen();
	for (int i=0; i<w->get_height(); i++) {
		for (int j=0; j<w->get_width(); j++) {
			setCell(j, i, w->get_cell(j, i));
		}
	}
	update();
	updateGeometry();
}

/*
 * Receive the 'zoom updated' signal, store the new zoom value,
 * and redraw the grid window based on the new zoom value
 *
 * INPUT: nZoom New zoom value
 */
void Grid::update_zoom(int nZoom)
{
	setZoomFact(nZoom);
}

/*
 * Main drawing method, draws the cells to the window
 *
 * INPUT event Paint event that is raised when a re-draw ( update(); ) is called
 */
void Grid::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	// Draw grid if we are zoomed in far enough
	if (zoom >= 3) {
		painter.setPen(palette().foreground().color());
		for (int i=0; i<= image.width(); ++i)
			painter.drawLine(zoom * i, 0, zoom * i, zoom * image.height());
		for (int j=0; j<= image.height(); ++j)
			painter.drawLine(0, zoom * j, zoom * image.width(), zoom * j);
	}

	// Redraw image
	for (int i=0; i<image.width(); ++i) {
		for (int j=0; j<image.height(); ++j) {
			QRect rect = pixelRect(i,j);
			if (!event->region().intersect(rect).isEmpty()) {
				QColor color = QColor::fromRgba(image.pixel(i,j));
				painter.fillRect(rect,color);
			}
		}
	}

}

/*
 * Gets a rectangle object that represents a cell, where the size
 * of the rectangle is directly related to the zoom factor
 *
 * INPUT: i X-coordinate of the image
 * INPUT: j Y-coordinate of the image
 */
QRect Grid::pixelRect(int i, int j) const
{
	if (zoom >= 3) {
		return QRect(zoom * i + 1, zoom * j + 1, zoom -1, zoom -1);
	} else {
		return QRect(zoom * i, zoom * j, zoom, zoom);
	}
}

/*
 * Set the color of the given cell, based on its state
 *
 * INPUT: x X-coordinate of the cell
 * INPUT: y Y-coordinate of the cell
 * INPUT: alive Determines whether to apply dead or alive color to the cell
 */
void Grid::setCell(int x, int y, bool alive) 
{
	if (alive) image.setPixel(x, y, aColor.rgba());	
	else image.setPixel(x, y, dColor.rgba());
}
