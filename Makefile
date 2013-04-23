all:showgen
showgen:showgen.o cell.o rules.o terrain.o
	g++ -o showgen showgen.o cell.o rules.o terrain.o
showgen.o:showgen.cpp
	g++ -c showgen.cpp
rules.o:rules.cpp rules.h
	g++ -c rules.cpp
terrain.o:terrain.cpp terrain.h
	g++ -c terrain.cpp
cell.o: cell.cpp cell.h
	g++ -c cell.cpp
clean:
	rm -f *.o *.gch  showgen 
