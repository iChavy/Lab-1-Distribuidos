#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <time.h>
#include <immintrin.h> //__mm128i 16 x 8 bits

// Valor máximo que almacena los registros de 8 bits
#define MAX 16

// Lee la imagen y devuelve un arreglo con los pixeles de la imagen
unsigned char* leer_imagen(char *imagen_entrada, int* filas, int* maximo);
// Crea la imagen de salida con formato PGM
void crear_imagen_salida(int *filas, int *maximo);
// Añade los bordes de la imagen de entrada modificando el arreglo de salida
void anyadir_bordes(unsigned char *arreglo, unsigned char *arreglo_salida, int *filas, int *maximo);
// Calcula el máximo del elemento estructural
int maximo_local(unsigned char *arreglo);
// Calcula el máximo de los valores de los pixeles de la imagen usando SIMD
void paralelo(unsigned char * arreglo, int * filas, int * maximo);
// Calcula el máximo de los valores de los pixeles de la imagen de forma secuencial
void secuencial(unsigned char * arreglo, int * filas, int * maximo);
