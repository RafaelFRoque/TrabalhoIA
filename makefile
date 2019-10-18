FILENAME = exec

all:
	g++ *.cpp -o $(FILENAME) -g

run:
	./$(FILENAME) < 1.in
