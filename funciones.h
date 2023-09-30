#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <time.h>

// includes de paralelo
#include <immintrin.h> //__mm128i 16 x 8 bits



// definicion de las funciones
//float sumar(float, float);

unsigned char* leer_imagen(char *imagen_entrada, int* filas, int* maximo);
void secuencial(unsigned char * arreglo, int * filas, int * maximo);
void paralelo(unsigned char * arreglo, int * filas, int * maximo);

void crear_imagen_salida(int *filas, int *maximo);
void anyadir_bordes(unsigned char *arreglo, unsigned char *arreglo_salida, int *filas, int *maximo);
int maximo_local(unsigned char *arreglo);
