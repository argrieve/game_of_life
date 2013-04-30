/*
 * ComS 229 Project 2: sim-gui
 * Spring 2013
 * Alex Grieve
 *
 * controls.h
 */

#ifndef CONTROLS_H
#define CONTROLS_H

#include <QDialog>

class QLabel;
class QPushButton;
class QSpinBox;
class QSlider;

/*
 * This class defines the control window and its behavior
 */
class Controls : public QDialog
{
	Q_OBJECT

	unsigned int gen;
	bool play_set;

	public:
		Controls(QWidget *parent = 0);

	signals:
		void update_sig();  // update the grid
		void zoom_sig(int); // change zoom number
		void prog_exit();   // exiting

	private slots:
		void step_gen();      // increase generation count
		void play_toggle();   // toggle 'play' state
		void zoom_change(int);// changing zoom
		void prog_close();    // close the window

	private:
		// Qt Gui Objects
		QLabel *delay_label, *gen_num, *gen_label, *zoom_label;
		QSpinBox *delay_box, *zoom_box;
		QSlider *delay_slider, *zoom_slider;
		QPushButton *quit, *play, *step;
		QTimer *timer;
};

#endif
