#include <QtGui>

#include "controls.h"
#include "stdio.h"
#include "unistd.h"

Controls::Controls(QWidget *parent)
: QDialog(parent)
{
	gen = 0;
	play_set = false;

	// Widget Init
	gen_num = new QLabel(QString('0'));
	gen_label = new QLabel("Generation:");
	delay_label = new QLabel("Delay:");
	delay_box = new QSpinBox;
	delay_slider = new QSlider(Qt::Horizontal);
	quit = new QPushButton("Quit");
	play = new QPushButton("Play");
	step = new QPushButton("Step");
	timer = new QTimer;
	timer->setSingleShot(false);

	// Layouts
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

	QObject::connect(quit, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(step, SIGNAL(clicked()), this, SLOT(step_gen()));
	QObject::connect(play, SIGNAL(clicked()), this, SLOT(play_toggle()));
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(step_gen()));
	QObject::connect(delay_box, SIGNAL(valueChanged(int)), timer, SLOT(start(int)));
}

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
