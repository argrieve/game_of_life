#include <QtGui>

#include "controls.h"

Controls::Controls(QWidget *parent)
: QDialog(parent)
{
	gen_num = new QLabel("gen_num");
	gen_label = new QLabel("Generation:");
	delay_label = new QLabel("Delay:");
	delay_box = new QSpinBox;
	delay_slider = new QSlider(Qt::Horizontal);
	quit = new QPushButton("Quit");
	play = new QPushButton("Play");
	step = new QPushButton("Step");

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
}
