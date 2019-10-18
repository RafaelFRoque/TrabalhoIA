FILENAME = exec
MAINCODE = entrada.cpp

all:
	g++ $(MAINCODE) -o $(FILENAME)

run:
	./$(FILENAME) < 1.in
