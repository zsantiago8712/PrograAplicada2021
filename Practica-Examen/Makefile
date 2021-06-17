# 21/20 - 01 - 21 
final.out: modulo1.o modulo2.o modulo3.o
	gcc -o final.out modulo1.o modulo2.o modulo3.o

modulo1.o: modulo1.c
	gcc -g -c modulo1.c

modulo2.o: modulo2.c
	gcc -g -c modulo2.c

modulo3.o: modulo3.c
	gcc -g -c modulo3.c

clean:
	rm *.o
	clear

compile:
	./final.out
