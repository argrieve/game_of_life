all:showgen
showgen:showgen.o rules.o
	g++ -o showgen showgen.o rules.o
showgen.o:showgen.cpp
	g++ -c showgen.cpp
rules.o:rules.cpp
	g++ -c rules.cpp
clean:
	rm -f *.o showgen 
