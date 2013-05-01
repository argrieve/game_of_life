ComS 229 Project 2
Spring 2013
Alex Grieve

*******************************************************************
*													CONTENTS																*
*******************************************************************
  I.	Compilation Instructions
		
 II.	Source File Descriptions
		a. config.h/config.cpp
		b. reader.h/reader.cpp
		c. world.h/world.cpp
		d. window.h/window.cpp
		e. grid.h/grid.cpp
		f. controls.h/controls.cpp



*******************************************************************
*									I. Compilation Instructions											*
*******************************************************************
To compile all programs, execute the top level Makefile by typing
'make' and pressing enter. Each of the three programs is built, and
the executable is copied to the 'bin' directory. To quickly view how
to use a program, type './<program name> -h' to bring up the 
program's help screen.



*******************************************************************
*									II. Source File Descriptions										*
*******************************************************************
The following section describes the main source files used in this
project. For specific details and functions, open the corresponding
source file and examine the code and comments.

a. config.h/config.cpp
	The 'config' class is simply a class that contains information
	about a world that has been parsed from a .aut file. This class
	is used to intialize a world, set its properties, and set the
	state of the world's cells at generation 0.
	
b. reader.h/reader.cpp
	The 'reader' class is responsible for parsing keywords and values
	from a .aut file. This class saves values it finds into a 'config'
	class object.
	
c. world.h/world.cpp
	The 'world' class is the heart of the project. It sets its initial
	values and properties based on the contents of a config file. The
	world class is responsible for updating its cell state arrays 
	from generation i to generation i+1.

d. window.h/window.cpp
	The 'window' class acts as a sort of viewport into the world. This
	class determines what portions of the world class are visible to
	the user at any given time, and writes these cells to the screen.
	The window class is moveable, allowing the user to traverse the
	world object at their leisure.

e. grid.h/grid.cpp
	The 'grid' class is a windowed GUI class that is derived from the
	Qt4 library. It provides the same purpose/functionality as the
	window class, and is only used in sim-gui.

f. controls.h/controls.cpp
	The 'controls' class is also a Qt GUI class that is derived from
	the Qt4 library. It is the user's main 'switch panel' in sim-gui.
	It allows users to interact with the world of cells by controlling
	the grid class/window.
