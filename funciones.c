#include "funciones.h"


/*
Descripción:    Lee la imagen de entrada y guarda los valores en un arreglo. Además, modifica el valor de filas y columnas
                y el valor máximo de la imagen
Entrada:        imagen_entrada: nombre de la imagen de entrada
                filas: entero que representa el número de filas y columnas de la imagen
                maximo: entero que representa el valor máximo de la imagen
Salida:         arreglo: arreglo que contiene los valores de la imagen de entrada
*/
unsigned char* leer_imagen(char *imagen_entrada, int* filas, int* maximo){
    FILE *imagen;

    unsigned char caracter1, caracter2;
    int columnas;
    char linea[50];
    char *linea_2;
    char *linea_3;

    // Abre la imagen en modo lectura binaria
    imagen = fopen(imagen_entrada, "rb");

    if (!imagen){
        perror("Error al abrir la abrir la imagen");
        exit(1);
    }

    caracter1 = fgetc(imagen);
    caracter2 = fgetc(imagen);

    // Comprueba si la imagen tiene el formato .pgm
    if (caracter1 != 'P' || caracter2 != '5'){
        printf("La imagen no está en formato .pgm\n");
        exit(1);
    }

    // Ignora el carácter de nueva línea
    fgetc(imagen);
    // Recorro la imagen para obtener las filas, columnas y el valor máximo
    linea_2 = fgets(linea, 50, imagen);
    *filas = atoi(strtok(linea_2, " "));
    columnas = atoi(strtok(NULL, " "));
    linea_3 = fgets(linea, 50, imagen);
    *maximo = atoi(linea_3);

    // Creacion arreglo dinamico
    unsigned char *arreglo = (unsigned char *)malloc((*filas*columnas)*sizeof(unsigned char));

    // Leo la imagen y guardo los valores en el arreglo
    fread(arreglo, sizeof(unsigned char), (*filas*columnas), imagen);
    fclose(imagen);
    return arreglo;
}

/*
Descripción:    Crea la imagen de salida con el formato .pgm
Entrada:        filas: entero que representa el número de filas y columnas de la imagen
                maximo: entero que representa el valor máximo de la imagen
Salida:         No posee retorno
*/
void crear_imagen_salida(int *filas, int *maximo){

    // Creacion imagenes de salida
    FILE *imagen_salida1, *imagen_salida2;
    imagen_salida1 = fopen("imagen_salida1.pgm", "wb");
    imagen_salida2 = fopen("imagen_salida2.pgm", "wb");

    // Escribo el encabezado de las imagenes
    fprintf(imagen_salida1, "P5\n");
    fprintf(imagen_salida1, "%d %d\n", *filas, *filas);
    fprintf(imagen_salida1, "%d\n", *maximo);

    fprintf(imagen_salida2, "P5\n");
    fprintf(imagen_salida2, "%d %d\n", *filas, *filas);
    fprintf(imagen_salida2, "%d\n", *maximo);

    // Cierro las imagenes
    fclose(imagen_salida1);
    fclose(imagen_salida2);
}

/*
Descripción:    Añade los bordes de la imagen de entrada al arreglo de salida   
Entrada:        arreglo: arreglo que contiene los valores de la imagen de entrada
                arreglo_salida: arreglo que contiene los valores de la imagen de salida
                filas: entero que representa el número de filas y columnas de la imagen
                maximo: entero que representa el valor máximo de la imagen
Salida:         No posee retorno
*/
void anyadir_bordes(unsigned char *arreglo, unsigned char *arreglo_salida, int *filas, int *maximo){
    int fila_actual;

    // Añado los bordes de la imagen al arreglo de salida
    for (int i = 0; i < (*filas)*(*filas); i += *filas){
        fila_actual = (int)(i/(*filas));

        // Si es la primera fila o ultima fila, la escribo completa
        if (fila_actual == 0 || fila_actual == ((*filas)-1)){
            for (int j = 0; j < *filas; j++){
                arreglo_salida[i+j] = arreglo[i+j];
            }
        }
        // Si no es la primera o ultima fila, escribo el primer y ultimo elemento
        else{
            arreglo_salida[i] = arreglo[i];
            arreglo_salida[i+(*filas)-1] = arreglo[i+(*filas)-1];
        }
    }
}

/*
Descripción:    Calcula el máximo local del elemento estructural
Entrada:        arreglo_aux: arreglo que contiene los valores del elemento estructural
Salida:         maximo: entero máximo valor del elemento estructural
*/    
int maximo_local(unsigned char *arreglo_aux){
    // Como los valores del elemento estructural son positivos, el máximo inicial es -1
    int maximo = -1;
    for (int i = 0; i < 5; i++){
        if (arreglo_aux[i] > maximo){
            maximo = arreglo_aux[i];
        }
    }
    return maximo;
}        

/*
Descripción:    Recorre la imagen de entrada con un elemento estructural en forma de cruz de forma secuencial,
                calcula el máximo local de cada elemento estructural y lo escribe en la imagen de salida
Entrada:        arreglo: arreglo que contiene los valores de la imagen de entrada
                filas: entero que representa el número de filas y columnas de la imagen
                maximo: entero que representa el valor máximo de la imagen
Salida:         No posee retorno
*/
void secuencial(unsigned char * arreglo, int *fila, int *maximo){
    // Creo arreglo de salida
    unsigned char *arreglo_salida = (unsigned char *)malloc(((*fila)*(*fila))*sizeof(unsigned char));
    // Arreglo auxiliar que se utiliza para guardar los valores actuales del elemento estructural
    unsigned char arreglo_aux[5];
    int fila_actual, valor_final_fila, max_local;

    // Abro la imagen de salida en modo apertura binaria
    FILE *imagen_salida1;
    imagen_salida1 = fopen("imagen_salida1.pgm", "ab");

    // Añado los bordes de la imagen de entrada al arreglo de salida
    anyadir_bordes(arreglo, arreglo_salida, fila, maximo);

    // Recorro la imagen con el elemento estructural sin considerar el borde superior, inferior y laterales
    for (int i = (*fila)+1; i < ((*fila)*(*fila)-1); i ++){
        fila_actual = (int)(i/(*fila));
        valor_final_fila = ((fila_actual+1)*(*fila))-1;
        max_local = -1;

        // Si el elemento estructural (centro) no está en un borde izquierdo o derecho
        if (i != (*fila)*fila_actual && i != valor_final_fila){
            // Guardo los valores actuales del elemento estructural
            arreglo_aux[0] = arreglo[i-(*fila)];  // arriba
            arreglo_aux[1] = arreglo[i-1];        // izquierda
            arreglo_aux[2] = arreglo[i];          // centro
            arreglo_aux[3] = arreglo[i+1];        // derecha
            arreglo_aux[4] = arreglo[i+(*fila)];  // abajo

            max_local = maximo_local(arreglo_aux);

            // Guardo el maximo en el arreglo de salida
            arreglo_salida[i] = max_local;
        }
    }
    
    // Escribo la imagen de salida
    fwrite(arreglo_salida, sizeof(unsigned char), ((*fila)*(*fila)), imagen_salida1);
    // Cierro la imagen y libero memoria
    fclose(imagen_salida1);
    free(arreglo_salida);
}

/*
Descripción:    Recorre la imagen de entrada con un elemento estructural en forma de cruz de forma paralela
                mediante el uso de SIMD, calcula el máximo local de los registros y lo escribe en la imagen de salida
Entrada:        arreglo: arreglo que contiene los valores de la imagen de entrada
                filas: entero que representa el número de filas y columnas de la imagen
                maximo: entero que representa el valor máximo de la imagen
Salida:         No posee retorno
*/
void paralelo(unsigned char * arreglo, int *filas, int *maximo){
    // Creacion del registro unsigned char (8 bits) que almacena hasta 16 valores
    __m128i registro_main[5];

    int fila_actual, valor_final_fila, retroceso;

    // Creo arreglo de salida
    unsigned char *arreglo_salida = (unsigned char *)malloc(((*filas)*(*filas))*sizeof(unsigned char));

    // Apertura binaria de imagen de salida
    FILE *imagen_salida;
    imagen_salida = fopen("imagen_salida2.pgm", "ab");
    anyadir_bordes(arreglo, arreglo_salida, filas, maximo);

    // Recorro la imagen con el elemento estructural sin considerar el borde superior, inferior y laterales
    for (int i = ((*filas)+1); i < (((*filas)*((*filas)-1))); i += MAX) {
        fila_actual = (int)(i/(*filas));
        valor_final_fila = ((fila_actual+1)*(*filas))-1;
        retroceso = 0;

        // Si el centro del elemento estructural no avanza hasta un borde izquierdo o derecho
        if ((i + MAX) < valor_final_fila){
            // Cargo los egistros 
            registro_main[0] = _mm_loadu_si128((__m128i *) &arreglo[i-(*filas)]);   // arriba
            registro_main[1] = _mm_loadu_si128((__m128i *) &arreglo[i-1]);          // izquierda
            registro_main[2] = _mm_loadu_si128((__m128i *) &arreglo[i]);            // centro
            registro_main[3] = _mm_loadu_si128((__m128i *) &arreglo[i+1]);          // derecha
            registro_main[4] = _mm_loadu_si128((__m128i *) &arreglo[i+(*filas)]);   // abajo
        }
        
        // Si el centro del ES, llega hasta el penultimo valor de la fila
        else if ((i + MAX) == valor_final_fila-1){   
            // Cargo los registros
            registro_main[0] = _mm_loadu_si128((__m128i *) &arreglo[i-(*filas)]);   // arriba
            registro_main[1] = _mm_loadu_si128((__m128i *) &arreglo[i-1]);          // izquierda
            registro_main[2] = _mm_loadu_si128((__m128i *) &arreglo[i]);            // centro
            registro_main[3] = _mm_loadu_si128((__m128i *) &arreglo[i+1]);          // derecha
            registro_main[4] = _mm_loadu_si128((__m128i *) &arreglo[i+(*filas)]);   // abajo

            // Me muevo al final de la fila y retrocedo 16
            i = valor_final_fila - MAX;   
            printf("entre al 2 if\n");
        }

       // Si no alcanzo a tomar 16 valores en la fila, retrocedo
        else {
            // Calculo cuánto debo retroceder
            retroceso = ((*filas)*(fila_actual+1))-1-i;
            retroceso = MAX - retroceso;
            i = i - retroceso;

            // Cargo los registros
            registro_main[0] = _mm_loadu_si128((__m128i *) &arreglo[i-(*filas)]);   // arriba
            registro_main[1] = _mm_loadu_si128((__m128i *) &arreglo[i-1]);          // izquierda
            registro_main[2] = _mm_loadu_si128((__m128i *) &arreglo[i]);            // centro
            registro_main[3] = _mm_loadu_si128((__m128i *) &arreglo[i+1]);          // derecha
            registro_main[4] = _mm_loadu_si128((__m128i *) &arreglo[i+(*filas)]);   // abajo
            
            // Me muevo al final de la fila y retrocedo 16
            i = valor_final_fila - MAX;       
        }
        // Calculo de máximo de los 5 registros
        __m128i maximo = _mm_max_epu8(registro_main[0], registro_main[1]);
        maximo = _mm_max_epu8(maximo, registro_main[2]);
        maximo = _mm_max_epu8(maximo, registro_main[3]);
        maximo = _mm_max_epu8(maximo, registro_main[4]);

        // Guardo el maximo en el arreglo de salida
        _mm_storeu_si128((__m128i *) &arreglo_salida[i], maximo);   

        // Si al aumentar 16 quedo en el final de la fila, sumo 2 para que el for me lleve  
        // a la siguiente fila + un espacio a la derecha para no considerar el borde
        if ((i + MAX) == valor_final_fila){
            i += 2;
        }
    }

    // Escribo la imagen de salida
    fwrite(arreglo_salida, sizeof(unsigned char), ((*filas)*(*filas)), imagen_salida);
    fclose(imagen_salida);
    free(arreglo_salida);
}

