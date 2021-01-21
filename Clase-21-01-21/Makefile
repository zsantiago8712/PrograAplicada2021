final.out: suma.o resta.o
	gcc -o final.out modulo1.o modulo2.o

suma.o: modulo1.c
	gcc -g -c modulo1.c

resta.o: modulo2.c
	gcc -g -c modulo2.c

clean:
	rm *.o

compile:
	./final.out
