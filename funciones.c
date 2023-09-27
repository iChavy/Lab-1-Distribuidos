#include "funciones.h"


// Lee la imagen de formato .pmg 
unsigned char* leer_imagen(char *imagen_entrada, int* filas){
    // Variables para leer la imagen
    FILE *imagen;
    unsigned char caracter1, caracter2;
    int columnas, maximo;
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
    *filas = atoi(strtok(linea_2, " "));
    printf("filas: %d\n", *filas);
    columnas = atoi(strtok(NULL, " "));

    linea_3 = fgets(linea, 100, imagen);
    maximo = atoi(linea_3);
    printf("maximo: %d\n", maximo);

    // Imprimo las dimensiones de la imagen
    printf("Dimensiones de la imagen: %d x %d\n", *filas, columnas);


    // creacion arreglo dinamico
    unsigned char *arreglo = (unsigned char *)malloc((*filas*columnas)*sizeof(unsigned char));
    unsigned char palabra;

    fread(arreglo, sizeof(unsigned char), (*filas*columnas), imagen);

    

    // leer palabra por palabra


    // Liberar memoria
    // Cierro la imagen
    fclose(imagen);
    return arreglo;
}

// implementar secuencial


//  implementar paralelo usando SIMD

void paralelo(unsigned char * arreglo, int *columna){
    // Creacion de registros
    __m128i registro_main[5];
    int modulo;
    int fila_actual, valor_final_fila;
    int filas = *columna;
    
    // Carga de registros cada 16
    //////////////////////////////////////////////7
    
    ////////////////////////////////////////////////////
    // -1 porque no considero el borde
     for (int i = (filas+1); i < ((filas*filas)-1); i+=16) {
        fila_actual = (int)(i/filas);
        valor_final_fila = ((fila_actual+1)*filas-2);
        
        //printf("fila actual: %i\n", fila_actual);
        //printf("El resultado es %s", (i + 16) < (filas - 2) ? "verdadero\n" : "falso\n");
        //printf("i+16 = %d       y      filas-2 = %d\n", (i+16), (filas - 2));

        if ((i+16) < valor_final_fila){
            //cargar------------------------------------------------------
            // Primer registro (arriba) parte del 1 y termina en fila-2
            // Segundo registro (izq) parte de fila+1 (513) termina en (fila*2)-2
            // Tercer registro (centro) parte de (fila*2)+1 (513) termina en (fila*3)-2
            // Cuarto registro (derecha) parte de (fila*3)+1 (513) termina en (fila*4)-2
            // Quinto registro (abajo) parte de (fila*4)+1 (513) termina en (fila*5)-2
            //registro_main[0] = _mm_loadu_si128((__m128i *) &arreglo[i-filas-1]);
            
            printf("fila actual: %i    y    el valor i =%i\n", fila_actual, i);

        }
        
        // Si llega al final de la columna-1, el centro de mi elemento estructural se mueve al comienzo de la fila de abajo y le sumo 1
        else if ((i+16) == valor_final_fila){    
            // cargo registros---------------------------------------------------------------


            fila_actual = (int)(i/filas);
            // Se obtiene el primer valor de la siguiente fila y se retrocede 15 para que el for lo mueva a la fila siguiente + 1 columna.
            i = ((fila_actual+1)*filas) - 15;
        }
        // Si llega al final de la columna de la imagen, creo un arreglo aux de 0s de 3 filas y 16 columnas 
        else if ((i+16) > valor_final_fila){
            //modulo = (filas-2)%16;SS
            // crea arreglo aux, 16 para guardar los registros, +1 porque necesito guardar desde la columna anterior, +1 para que 
            // el registro derecha pueda llegar hasta el final
            int arreglo_aux[3*18] = {0};

            //--------funcion que llena el arreglo aux con valores del arreglo
            int i_aux = i;
            // Recorro desde i-1 hasta el final de cada columna y lo almaceno en arreglo_aux
            for (int j = 0; j < (((filas)%16)+2); j++){
                // Parte de la fila anterior - 1 para considerar el lado izquierdo del ES.
                arreglo_aux[j] = arreglo[i_aux-filas-1];
                arreglo_aux[j+18] = arreglo[i_aux];
                arreglo_aux[j+36] = arreglo[i_aux+(filas)];

                i_aux += 1;
            }
            
            // cargar a registros con arreglo aux----------------------------------


            fila_actual = (int)(i/filas);
            
            // Se obtiene el primer valor de la siguiente fila y se retrocede 15 para que el for lo mueva a la fila siguiente + 1 columna.
            i = ((fila_actual+1)*filas) - 15;
        }
        
    

     }

    
}


    
    


