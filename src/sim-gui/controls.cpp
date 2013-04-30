#include <QtGui>

#include "controls.h"

Controls::Controls(QWidget *parent)
: QDialog(parent)
{
	// Widget Init
	gen_num = new QLabel("gen_num");
	gen_label = new QLabel("Generation:");
	delay_label = new QLabel("Delay:");
	delay_box = new QSpinBox;
	delay_slider = new QSlider(Qt::Horizontal);
	quit = new QPushButton("Quit");
	play = new QPushButton("Play");
	step = new QPushButton("Step");

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
	delay_box->setRange(0,2500);
	delay_slider->setRange(0,2500);
	QObject::connect(delay_box, SIGNAL(valueChanged(int)), delay_slider, SLOT(setValue(int)));
	QObject::connect(delay_slider, SIGNAL(valueChanged(int)), delay_box, SLOT(setValue(int)));
	delay_box->setValue(250);

	QObject::connect(quit, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(step, SIGNAL(clicked()), this, SLOT(next_gen()));
}

void Controls::next_gen()
{
	emit update_sig();
}
