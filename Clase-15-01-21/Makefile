final.out: ConexionArchivos.o suma.o resta.o
	gcc -o final.out ConexionArchivos.o suma.o resta.o

ConexionArchivos.o: ConexionArchivos.c
	gcc -g -c ConexionArchivos.c

suma.o: suma.c
	gcc -g -c suma.c

resta.o: resta.c
	gcc -g -c resta.c

clean:
	rm *.o

compile:
	./final.out
