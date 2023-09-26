#include "funciones.h"

int main(int argc, char *argv[]){
    // Guarda las opciones ingresadas	
	int option;
	//Nombre de la imagen de entrada y de las imagenes de salida
    char *imagen_entrada, *imagen_salida1, *imagen_salida2;
	
	// Recibe entradas por línea de comandos
  	while((option = getopt(argc, argv, "i:s:p")) != -1){     
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
                break;
        }
    }

    unsigned char * arreglo = leer_imagen(imagen_entrada);

    for(int i = 0; i < (512*512); i++){
            printf("arreglo[%d]: %d\n", i, arreglo[i]);
        }

    return 0;
}