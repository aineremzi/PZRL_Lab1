FLAGS=-c --all
all: main.o func.o
	gcc main.o func.o -o sed_simplified
main.o: main.c
	gcc main.c -o main.o $(FLAGS)
func.o: func.c
	gcc func.c -o func.o $(FLAGS)
clean:
	rm -rf *.o sed_simplified
test_r: all
	./sed_simplified input.txt 's/OLD_TEXT/TEXT/'
test_d: all
	./sed_simplified input.txt '/TO_DELETE/d'
test_p: all
	./sed_simplified input.txt 's/^/prefix/'
