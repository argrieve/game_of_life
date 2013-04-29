all:sim-tui
sim-tui:sim-tui.o config.o world.o reader.o window.o 
	g++ -o sim-tui sim-tui.o config.o world.o reader.o window.o -lncurses
sim-tui.o:sim-tui.cpp
	g++ -c sim-tui.cpp
config.o:config.cpp config.h
	g++ -c config.cpp
world.o:world.cpp world.h
	g++ -c world.cpp
reader.o:reader.cpp reader.h
	g++ -c reader.cpp
window.o:window.cpp window.h
	g++ -c window.cpp
clean:
	rm -f *.o sim-tui
