FILENAME = exec
MAINCODE = entrada.cpp

all:
	g++ $(MAINCODE) -o $(FILENAME) -g

run:
	./$(FILENAME) < 1.in
