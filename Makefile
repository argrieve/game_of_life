.PHONY: showgen sim-tui

all:bin showgen sim-tui
bin:
	mkdir bin
showgen:
	$(MAKE) -C src/showgen
	cp src/showgen/showgen ./bin
sim-tui:
	$(MAKE) -C src/sim-tui
	cp src/sim-tui/sim-tui ./bin
clean:
	$(MAKE) -C src/showgen clean
	$(MAKE) -C src/sim-tui clean
	rm -r bin
