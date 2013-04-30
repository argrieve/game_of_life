/*
 * ComS 229 Project 2: sim-gui
 * Spring 2013
 * Alex Grieve
 *
 * grid.h
 */

#ifndef GRID_H
#define GRID_H

#include <QColor>
#include <QImage>
#include <QWidget>
#include "world.h"

/*
 * This class describes the cell/world grid and defines its behavior
 */
class Grid : public QWidget
{
	Q_OBJECT

	/*
	 * Custom properties for the grid
	 */
	Q_PROPERTY(int zoomFactor READ zoomFact WRITE setZoomFact)
	Q_PROPERTY(QColor aliveColor READ aliveColor WRITE setAliveColor)
	Q_PROPERTY(QColor deadColor READ deadColor WRITE setDeadColor)
	
	/*
	 * Member variables
	 */
	world *w;
	QColor aColor, dColor;
	QImage image;
	int zoom;

	public:
		Grid(QWidget *parent = 0);
		QSize sizeHint() const;

		// Color getters/setters
		void setAliveColor(const QColor &newColor);
		QColor aliveColor() const { return aColor; }
		void setDeadColor(const QColor &newColor);
		QColor deadColor() const { return dColor; }

		// Zoom factor getter/setter
		void setZoomFact(int newZoom);
		int zoomFact() const { return zoom; }

		// World initialization	
		void setWorld(world *ptr);
	
	public slots:
		void update_grid();
		void update_zoom(int nZoom);

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		QRect pixelRect(int i, int j) const;
		void setCell(int x, int y, bool alive);
};

#endif
