.PHONY: showgen

all:bin showgen
bin:
	mkdir bin
showgen:
	$(MAKE) -C src/showgen
	cp src/showgen/showgen ./bin
clean:
	$(MAKE) -C src/showgen clean
	rm -r bin
