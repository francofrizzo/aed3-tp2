CC=g++
CFLAGS=-g -Wall -O2 -std=c++11
EXECUTABLES_BASE=UnaNuevaEsperanza ElImperioContraataca ElRetornoDelJedi
EXECUTABLES=$(addsuffix Solver, $(EXECUTABLES_BASE))
MAIN_OBJECT=main.o
OTHER_OBJECTS=solver.o performance.o test.o

.PHONY: all clean test $(addsuffix test, $(EXECUTABLES_BASE))

all: $(EXECUTABLES)

test: $(addprefix test,$(EXECUTABLES_BASE))

clean:
	rm -rf $(EXECUTABLES) $(MAIN_OBJECT) $(addsuffix /*.o,$(EXECUTABLES_BASE))

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@

.SECONDEXPANSION:

$(EXECUTABLES): $(MAIN_OBJECT) $$(addprefix $$(subst Solver,,$$@)/,$(OTHER_OBJECTS))
	$(CC) $(CFLAGS) -o $@ $^

$(addprefix test, $(EXECUTABLES_BASE)): $$(addsuffix Solver,$$(subst test,,$$@))
	@echo "Testeando $(subst test,,$@). Número de test a correr: " ;\
	read SEED ;\
	java -jar ../test/$(subst test,,$@)Tester.jar -exec ./$(subst test,,$@)Solver -test $$SEED
