ENTREGABLE=aed3-tp2.tar.gz
FILES=latex/informe.pdf src/Makefile src/*.h src/*.cpp src/*/*.h src/*/*.cpp

.PHONY: all clean

all: $(ENTREGABLE)

clean:
	rm -f aed3-tp2.tar.gz
	$(MAKE) clean -C latex
	$(MAKE) clean -C src

$(ENTREGABLE):
	$(MAKE) -C latex
	tar -cvzf $(ENTREGABLE) $(FILES)
