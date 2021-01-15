final.out: Conexion-archivos-c.o suma.o resta.o
	gcc -o final.out Conexion-archivos-c.o suma.o resta.o

Conexion-archivos-c.o: Conexion-archivos-c.c
	gcc -c Conexion-archivos-c.c

suma.o: suma.c
	gcc -c suma.c

resta.o: resta.c
	gcc -c resta.c

clean:
	rm *.o

compile:
	./final.out
