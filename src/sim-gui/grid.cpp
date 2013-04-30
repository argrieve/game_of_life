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

QSize Grid::sizeHint() const
{
	QSize size = zoom * image.size();
	if (zoom >= 3)
		size += QSize(1, 1);
	return size;
}

void Grid::setAliveColor(const QColor &newColor)
{
	aColor = newColor;
}

void Grid::setDeadColor(const QColor &newColor)
{
	dColor = newColor;
}

void Grid::setSize(int w, int h)
{
	// Set new image size
	image = QImage(w, h, QImage::Format_ARGB32);

	// Initialize cells to dead color
	image.fill(dColor);
}

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

void Grid::setCell(int x, int y, bool alive) 
{
	if (alive) image.setPixel(x, y, aColor.rgba());	
	else image.setPixel(x, y, dColor.rgba());
	update(pixelRect(x,y));
}

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
void IconEditor::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		setImagePixel(event->pos(), true);
	} else if (event->button() == Qt::RightButton) {
		setImagePixel(event->pos(), false);
	}
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		setImagePixel(event->pos(), true);
	} else if (event->buttons() & Qt::RightButton) {
		setImagePixel(event->pos(), false);
	}
}


void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
	int i = pos.x() / zoom;
	int j = pos.y() / zoom;

	if (image.rect().contains(i, j)) {
		if (opaque) {
			image.setPixel(i, j, penColor().rgba());
		} else {
			image.setPixel(i, j, qRgba(0, 0, 0, 0));
		}

		update(pixelRect(i, j));
	}
}
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
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	IconEditor *iconEditor = new IconEditor;

	QScrollArea scrollArea;
	scrollArea.setWidget(iconEditor);
	scrollArea.viewport()->setBackgroundRole(QPalette::Dark);
	scrollArea.viewport()->setAutoFillBackground(true);
	scrollArea.setWindowTitle(QObject::tr("Icon Editor"));

	scrollArea.show();
	return app.exec();
}
*/
