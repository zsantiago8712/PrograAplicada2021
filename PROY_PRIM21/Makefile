# 21/20 - 01 - 21 
final.out: gtk.o gtk2.o gtk3.o gtk4.o gtk5.o funcionesGen.o
	gcc -o gtk.out gtk.o gtk2.o gtk3.o gtk4.o gtk5.o funcionesGen.o `pkg-config --libs gtk+-2.0`

gtk.o: gtk.c
	gcc -c gtk.c `pkg-config --cflags gtk+-2.0`

gtk2.o: gtk2.c
	gcc -c gtk2.c `pkg-config --cflags gtk+-2.0`

gtk3.o: gtk3.c
	gcc -c gtk3.c `pkg-config --cflags gtk+-2.0`

gtk4.o: gtk4.c
	gcc -c gtk4.c `pkg-config --cflags gtk+-2.0`

gtk5.o: gtk5.c
	gcc -c gtk5.c `pkg-config --cflags gtk+-2.0`

funcionesGen.o: funcionesGen.c
	gcc -c funcionesGen.c `pkg-config --cflags gtk+-2.0`

clean:
	rm *.o
	clear

compile:
	./final.out -h


#gtk.o: gtk3.c
#	gcc -c gtk3.c `pkg-config --cflags gtk+-2.0`

#funcionesGen.o: funcionesGen.c
#	gcc -c funcionesGen.c `pkg-config --cflags gtk+-2.0`



