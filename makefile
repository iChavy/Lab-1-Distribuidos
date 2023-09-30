run: main.o
	./main.o -i bike.pgm -s imagen_salida1.pgm -p imagen_salida2.pgm

main.o: main.c funciones.o
	gcc main.c -o main.o funciones.o -lm

funciones.o: funciones.c funciones.h
	gcc -c funciones.c -lm

clean:
	rm main.o funciones.o imagen_salida1.pgm imagen_salida2.pgm