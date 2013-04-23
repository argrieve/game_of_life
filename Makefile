all:showgen
showgen:showgen.o
	g++ -o showgen showgen.o
showgen.o:showgen.cpp
	g++ -c showgen.cpp
clean:
	rm -f *.o showgen 
