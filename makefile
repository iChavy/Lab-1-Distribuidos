programa: dilation.o funciones.o
	gcc -o programa dilation.o funciones.o

dilation.o: dilation.c funciones.h
	gcc -Wall -c dilation.c

funciones.o: funciones.c funciones.h
	gcc -Wall -c funciones.c

clean:
	rm -f programa *.o 
	find . -type f \( -name '*.pgm' ! -name 'bike.pgm' ! -name 'lines.pgm' \) -exec rm -f {} +