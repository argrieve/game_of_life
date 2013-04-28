all:showgen
showgen:showgen.o config.o world.o reader.o window.o 
	g++ -o showgen showgen.o config.o world.o reader.o window.o 
showgen.o:showgen.cpp
	g++ -c showgen.cpp
config.o:config.cpp config.h
	g++ -c config.cpp
world.o:world.cpp world.h
	g++ -c world.cpp
reader.o:reader.cpp reader.h
	g++ -c reader.cpp
window.o:window.cpp window.h
	g++ -c window.cpp
clean:
	rm -f *.o showgen
