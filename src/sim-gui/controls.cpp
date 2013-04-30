/*
 * ComS 229 Project 2: sim-gui
 * Spring 2013
 * Alex Grieve
 *
 * controls.cpp
 */

#include <QtGui>

#include "controls.h"
#include "stdio.h"

Controls::Controls(QWidget *parent)
: QDialog(parent)
{
	gen = 0;
	play_set = false;

	// Qt Widget Init
	gen_num = new QLabel(QString('0'));
	gen_label = new QLabel("Generation:");
	delay_label = new QLabel("Delay:");
	delay_box = new QSpinBox;
	delay_slider = new QSlider(Qt::Horizontal);
	zoom_label = new QLabel("Zoom:");
	zoom_box = new QSpinBox;
	zoom_slider = new QSlider(Qt::Horizontal);
	quit = new QPushButton("Quit");
	play = new QPushButton("Play");
	step = new QPushButton("Step");
	timer = new QTimer;
	timer->setSingleShot(false);

	// Layouts
	QHBoxLayout *zoom_layout = new QHBoxLayout;
	zoom_layout->addWidget(zoom_label);
	zoom_layout->addWidget(zoom_box);
	zoom_layout->addWidget(zoom_slider);

	QHBoxLayout *delay_layout = new QHBoxLayout;
	delay_layout->addWidget(delay_label);
	delay_layout->addWidget(delay_box);
	delay_layout->addWidget(delay_slider);

	QHBoxLayout *gen_layout = new QHBoxLayout;
	gen_layout->addWidget(gen_label);
	gen_layout->addStretch();
	gen_layout->addWidget(gen_num);

	QHBoxLayout *btn_layout = new QHBoxLayout;
	btn_layout->addWidget(quit);
	btn_layout->addWidget(play);
	btn_layout->addWidget(step);

	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->addLayout(zoom_layout);
	main_layout->addLayout(delay_layout);
	main_layout->addLayout(gen_layout);
	main_layout->addLayout(btn_layout);
	setLayout(main_layout);
	setWindowTitle("Controls");
	setFixedHeight(sizeHint().height());

	// Connections
	delay_box->setRange(1,1000);
	delay_slider->setRange(1,1000);
	QObject::connect(delay_box, SIGNAL(valueChanged(int)), delay_slider, SLOT(setValue(int)));
	QObject::connect(delay_slider, SIGNAL(valueChanged(int)), delay_box, SLOT(setValue(int)));
	delay_box->setValue(250);

	zoom_box->setRange(1,100);
	zoom_slider->setRange(1,100);
	QObject::connect(zoom_box, SIGNAL(valueChanged(int)), zoom_slider, SLOT(setValue(int)));
	QObject::connect(zoom_slider, SIGNAL(valueChanged(int)), zoom_box, SLOT(setValue(int)));
	zoom_box->setValue(8);

	QObject::connect(zoom_box, SIGNAL(valueChanged(int)), this, SLOT(zoom_change(int)));
	QObject::connect(quit, SIGNAL(clicked()), this, SLOT(prog_close()));
	QObject::connect(step, SIGNAL(clicked()), this, SLOT(step_gen()));
	QObject::connect(play, SIGNAL(clicked()), this, SLOT(play_toggle()));
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(step_gen()));
	QObject::connect(delay_box, SIGNAL(valueChanged(int)), timer, SLOT(start(int)));
}

/*
 * Increment generation count by one (step), signal
 * for the grid to be updated
 */
void Controls::step_gen()
{
	// Update generation count
	gen++;
	char tmp[20];
	sprintf(tmp, "%d", gen);
	gen_num->setText(QString(tmp));

	// Signal grid to update its state
	emit update_sig();
}

/*
 * Toggle the play bool, turn the timer on/off accordingly
 */
void Controls::play_toggle()
{
	play_set = !play_set;
	if (play_set) {
		//start timer
		timer->start(delay_box->value());
	}
	else {
		//stop timer
		timer->stop();
	}
}

/*
 * Signal the grid to update based on the new zoom value
 *
 * INPUT: newZ New zoom value
 */
void Controls::zoom_change(int newZ)
{
	emit zoom_sig(newZ);
}

/*
 * Signal the grid to close, then close the control window
 */
void Controls::prog_close()
{
	emit prog_exit();
	this->close();
}
