FILENAME = exec
MAINCODE = search.cpp
OUTFILE = saida.out

all:
	g++ $(MAINCODE) -o $(FILENAME)

run1:
	./$(FILENAME) < 1.in > $(OUTFILE)

run2:
	./$(FILENAME) < 2.in > $(OUTFILE)

run3:
	./$(FILENAME) < 3.in > $(OUTFILE)

run4:
	./$(FILENAME) < 4.in > $(OUTFILE)

run5:
	./$(FILENAME) < 5.in > $(OUTFILE)

run6:
	./$(FILENAME) < 6.in > $(OUTFILE)

run7:
	./$(FILENAME) < 7.in > $(OUTFILE)

run8:
	./$(FILENAME) < 8.in > $(OUTFILE)
