FILENAME = exec

all:
	g++ *.cpp -o $(FILENAME)

run:
	./$(FILENAME) < 1.in
