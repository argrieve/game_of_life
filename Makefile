.PHONY: showgen sim-tui sim-gui

all:bin showgen sim-tui sim-gui
bin:
	mkdir bin
showgen:
	$(MAKE) -C src/showgen
	cp src/showgen/showgen ./bin
sim-tui:
	$(MAKE) -C src/sim-tui
	cp src/sim-tui/sim-tui ./bin
sim-gui:
	cd src/sim-gui && qmake-qt4 -project
	cd src/sim-gui && qmake-qt4 sim-gui.pro 
	cd src/sim-gui && make 
	cp src/sim-gui/sim-gui ./bin
clean:
	$(MAKE) -C src/showgen clean
	$(MAKE) -C src/sim-tui clean
	cd src/sim-gui && make clean
	cd src/sim-gui && rm Makefile sim-gui *.pro
	rm -r bin
