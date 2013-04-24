all:showgen
showgen:showgen.o cell.o range.o coord.o rules.o terrain.o 
	g++ -o showgen showgen.o cell.o rules.o terrain.o range.o coord.o
showgen.o:showgen.cpp
	g++ -c showgen.cpp
rules.o:rules.cpp rules.h
	g++ -c rules.cpp
terrain.o:terrain.cpp terrain.h 
	g++ -c terrain.cpp
cell.o:cell.cpp cell.h
	g++ -c cell.cpp
range.o:range.cpp range.h
	g++ -c range.cpp
coord.o:coord.cpp coord.h
	g++ -c coord.cpp
clean:
	rm -f *.o *.gch  showgen 
