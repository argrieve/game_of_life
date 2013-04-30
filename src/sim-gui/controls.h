#ifndef CONTROLS_H
#define CONTROLS_H

#include <QDialog>

class QLabel;
class QPushButton;
class QSpinBox;
class QSlider;

class Controls : public QDialog
{
	Q_OBJECT

	public:
		Controls(QWidget *parent = 0);
	
	private:
		QLabel *delay_label, *gen_num, *gen_label;
		QSpinBox *delay_box;
		QSlider *delay_slider;
		QPushButton *quit, *play, *step;
};

#endif
