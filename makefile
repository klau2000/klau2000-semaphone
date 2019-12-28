all: main.o control.o
	gcc -o control control.o
	gcc -o write main.o

main.o: main.c control.h
	gcc -c main.c control.h

control.o: control.c control.h
	gcc -c control.c

clean:
	rm output *.o *.gch
