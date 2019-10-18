FILENAME = exec
MAINCODE = search.cpp

all:
	g++ $(MAINCODE) -o $(FILENAME)

run1:
	./$(FILENAME) < 1.in > saida1.out

run2:
	./$(FILENAME) < 2.in > saida2.out

run3:
	./$(FILENAME) < 3.in > saida3.out

run4:
	./$(FILENAME) < 4.in > saida4.out

run5:
	./$(FILENAME) < 5.in > saida5.out

run6:
	./$(FILENAME) < 6.in > saida6.out

run7:
	./$(FILENAME) < 7.in > saida7.out

run8:
	./$(FILENAME) < 8.in > saida8.out
