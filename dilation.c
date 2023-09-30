#include "funciones.h"
#include <unistd.h> // Incluye unistd.h para optarg

int main(int argc, char *argv[]){
    // Guarda las opciones ingresadas	
	int option;
	//Nombre de la imagen de entrada y de las imagenes de salida
    char *imagen_entrada, *imagen_salida1, *imagen_salida2;

    clock_t inicio, fin;
    double tiempo;

    int filas, maximo;
	
	// Recibe entradas por línea de comandos
  	while((option = getopt(argc, argv, "i:s:p:")) != -1){     
        switch(option){         
            // Nombre de la imagen de entrada
            case 'i':
                imagen_entrada = optarg;
                break;
            // Nombre de la imagen de salida del proceso secuencial
            case 's':
                imagen_salida1 = optarg;
                break;
            // Nombre de la imagen de salida del proceso paralelo
            case 'p':
                imagen_salida2 = optarg;
                break;
            
            // Opciones invalidas
            case '?':
                printf("La opción ingresada no existe: %c\n", optopt);
                return 1;
        }
    }

    unsigned char * arreglo = leer_imagen(imagen_entrada, &filas, &maximo);
    crear_imagen_salida(&filas, &maximo, imagen_salida1, imagen_salida2);
    
    inicio = clock();
    secuencial(arreglo, &filas, &maximo, imagen_salida1);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo secuencial: %f\n", tiempo);

    inicio = clock();
    paralelo(arreglo, &filas, &maximo, imagen_salida2);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo paralelo: %f\n", tiempo);   

    free(arreglo);
    return 0;
}