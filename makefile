all: main.o control.o
	gcc -o program main.o control.o

main.o: main.c control.h
	gcc -c main.c control.h

control.o: control.c control.h
	gcc -c control.c

run:
	./output

clean:
	rm output *.o *.gch
