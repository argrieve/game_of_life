#ifndef GRID_H
#define GRID_H

#include <QColor>
#include <QImage>
#include <QWidget>
#include "world.h"

class Grid : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(int zoomFactor READ zoomFact WRITE setZoomFact)
	Q_PROPERTY(QColor aliveColor READ aliveColor WRITE setAliveColor)
	Q_PROPERTY(QColor deadColor READ deadColor WRITE setDeadColor)
	
	world *w;

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

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		//void setImagePixel(const QPoint &pos, bool opaque);
		QRect pixelRect(int i, int j) const;
		void setCell(int x, int y, bool alive);

		QColor aColor, dColor;
		QImage image;
		int zoom;
};

#endif
