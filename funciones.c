#include "funciones.h"


// Lee la imagen de formato .pmg 
unsigned char* leer_imagen(char *imagen_entrada){
    // Variables para leer la imagen
    FILE *imagen;
    unsigned char caracter1, caracter2;
    int filas, columnas, maximo;
    char *dimensiones;

    

    //------------------------------------- podria ser dinamica -------------------------------
    char linea[100];
    char *linea_2;
    char *linea_3;

    int contador = 0;

    // Abre la imagen en modo lectura binaria
    imagen = fopen(imagen_entrada, "rb");

    caracter1 = fgetc(imagen);
    printf("caracter1: %c\n", caracter1);
    caracter2 = fgetc(imagen);
    printf("caracter2: %c\n", caracter2);

    // Comprueba si la imagen tiene el formato .pgm
    if(caracter1 != 'P' || caracter2 != '5'){
        printf("La imagen no es formato .pgm\n");
        return NULL;
    }

    // Ignora el carácter de nueva línea
    fgetc(imagen);
    // Recorro la imagen para obtener las filas, columnas y el valor máximo
    linea_2 = fgets(linea, 100, imagen);
    printf("linea_2: %s\n", linea_2);
    filas = atoi(strtok(linea_2, " "));
    printf("filas: %d\n", filas);
    columnas = atoi(strtok(NULL, " "));

    

    linea_3 = fgets(linea, 100, imagen);
    maximo = atoi(linea_3);
    printf("maximo: %d\n", maximo);

   
    

    // Imprimo las dimensiones de la imagen
    printf("Dimensiones de la imagen: %d x %d\n", filas, columnas);


    // creacion arreglo dinamico
    unsigned char *arreglo = (unsigned char *)malloc((filas*columnas)*sizeof(unsigned char));
    unsigned char palabra;

    fread(arreglo, sizeof(unsigned char), (filas*columnas), imagen);

    

    // leer palabra por palabra


    // Liberar memoria
    free(arreglo);
    // Cierro la imagen
    fclose(imagen);
    return arreglo;
}

// implementar secuencial


//  implementar paralelo usando SIMD


