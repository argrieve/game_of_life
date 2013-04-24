all:showgen
showgen:showgen.o cell.o world.o
	g++ -o showgen showgen.o cell.o world.o
showgen.o:showgen.cpp
	g++ -c showgen.cpp
cell.o:cell.cpp cell.h
	g++ -c cell.cpp
world.o:world.cpp world.h
	g++ -c world.cpp
clean:
	rm -f *.o showgen
