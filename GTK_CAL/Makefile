# 21/20 - 01 - 21 
final.out: gtk.o
	gcc -o gtk.out gtk.o `pkg-config --libs gtk+-2.0`

gtk.o: gtk.c
	gcc -c -g gtk.c `pkg-config --cflags gtk+-2.0`

clean:
	rm *.o
	clear

compile:
	./final.out
