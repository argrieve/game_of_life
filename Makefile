all:showgen
showgen:showgen.o cell.o coord.o config.o world.o reader.o 
	g++ -o showgen showgen.o cell.o coord.o config.o world.o reader.o 
showgen.o:showgen.cpp
	g++ -c showgen.cpp
cell.o:cell.cpp cell.h
	g++ -c cell.cpp
coord.o:coord.cpp coord.h
	g++ -c coord.cpp
config.o:config.cpp config.h
	g++ -c config.cpp
world.o:world.cpp world.h
	g++ -c world.cpp
reader.o:reader.cpp reader.h
	g++ -c reader.cpp
clean:
	rm -f *.o showgen
