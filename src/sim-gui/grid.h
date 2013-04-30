#ifndef GRID_H
#define GRID_H

#include <QColor>
#include <QImage>
#include <QWidget>
#include "world.h"

class Grid : public QWidget
{
	Q_OBJECT

	//Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
	Q_PROPERTY(int zoomFactor READ zoomFact WRITE setZoomFact)

	Q_PROPERTY(QColor aliveColor READ aliveColor WRITE setAliveColor)
	Q_PROPERTY(QColor deadColor READ deadColor WRITE setDeadColor)
	
	world *w;

	public:
		Grid(QWidget *parent = 0);

		void setAliveColor(const QColor &newColor);
		QColor aliveColor() const { return aColor; }
		void setDeadColor(const QColor &newColor);
		QColor deadColor() const { return dColor; }

		void setZoomFact(int newZoom);
		int zoomFact() const { return zoom; }

		void setSize(int w, int h);
		void setCell(int x, int y, bool alive);
		void setWorld(world *ptr) { w = ptr; }

		//void setIconImage(const QImage &newImage);
		//QImage iconImage() const { return image; }
		QSize sizeHint() const;
	
	public slots:
		void update_grid();

	protected:
		//void mousePressEvent(QMouseEvent *event);
		//void mouseMoveEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);

	private:
		//void setImagePixel(const QPoint &pos, bool opaque);
		QRect pixelRect(int i, int j) const;

		QColor aColor, dColor;
		QImage image;
		int zoom;
};

#endif