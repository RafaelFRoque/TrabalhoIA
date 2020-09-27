FILENAME = exec
MAINCODE = search.cpp

all:
	g++ $(MAINCODE) -o $(FILENAME)

run1:
	./$(FILENAME) < entradas/1.in > saidas/saida1.out

run2:
	./$(FILENAME) < entradas/2.in > saidas/saida2.out

run3:
	./$(FILENAME) < entradas/3.in > saidas/saida3.out

run4:
	./$(FILENAME) < entradas/4.in > saidas/saida4.out

run5:
	./$(FILENAME) < entradas/5.in > saidas/saida5.out

run6:
	./$(FILENAME) < entradas/6.in > saidas/saida6.out

run7:
	./$(FILENAME) < entradas/7.in > saidas/saida7.out

run8:
	./$(FILENAME) < entradas/8.in > saidas/saida8.out
