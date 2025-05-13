#include <stdio.h>
#include <stdlib.h>

// Función para cargar la matriz, verificar si es cuadrada y si solo contiene 0s y 1s utilizando punteros
int **cargar_matriz(const char *nombre_archivo, int *tamano) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo.\n");
        exit(1);
    }

    int **matriz = NULL;
    int filas = 0, columnas = 0;
    int valor;
    char linea[1024];

    while (fgets(linea, sizeof(linea), archivo)) {
        filas++;
        columnas = 0;

        matriz = realloc(matriz, filas * sizeof(int *));
        matriz[filas - 1] = NULL;  // Inicializar fila

        char *ptr = linea;
        while (sscanf(ptr, "%d", &valor) == 1) {
            if (valor != 0 && valor != 1) {
                printf("Error: La matriz contiene valores distintos de 0 y 1.\n");
                exit(1);
            }

            columnas++;
            matriz[filas - 1] = realloc(matriz[filas - 1], columnas * sizeof(int));
            matriz[filas - 1][columnas - 1] = valor;

            ptr += 2; // Avanzamos en la línea
        }
    }
    fclose(archivo);

    if (filas != columnas) {
        printf("Error: La matriz no es cuadrada (%d filas, %d columnas).\n", filas, columnas);
        exit(1);
    }

    *tamano = filas;
    return matriz;
}

// Función para mostrar la matriz
void mostrar_matriz(int **matriz, int tamano) {
    printf("Matriz cargada (%dx%d):\n", tamano, tamano);
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Función para encontrar la secuencia más larga en dirección ↑↙
int encontrar_max_secuencia(int **matriz, int tamano) {
    int max_secuencia = 0;
    int contador = 0;

    // Se revisan diagonales empezando desde cada columna en la primera fila
    for (int col = tamano - 1; col >= 0; col--) {
        int fila = 0, columna = col;

        while (fila >= 0 && columna >= 0) {
            if (matriz[fila][columna] == 1) {
                contador++;
                if (contador > max_secuencia) {
                    max_secuencia = contador;
                }
            } else {
                contador = 0;  // Reiniciar solo cuando se encuentra un 0
            }
            fila++;  // Mover abajo
            columna--;  // Mover izquierda
        }
    }

    // Se revisan las diagonales empezando desde cada fila en la última columna
    for (int fila = tamano - 2; fila >= 0; fila--) {
        int columna = tamano - 1;

        while (fila >= 0 && columna >= 0) {
            if (matriz[fila][columna] == 1) {
                contador++;
                if (contador > max_secuencia) {
                    max_secuencia = contador;
                }
            } else {
                contador = 0;
            }
            fila--;  
            columna--;  
        }
    }
    printf("La secuencia de 1s más larga en dirección ↑↙ es: %d\n", max_secuencia);

    return max_secuencia;
}

// Función para liberar memoria
void liberar_matriz(int **matriz, int tamano) {
    for (int i = 0; i < tamano; i++) {
        free(matriz[i]);
    }
    free(matriz);
}


int main() {
    int tamano;
    int **matriz = cargar_matriz("matriz.txt", &tamano);
    mostrar_matriz(matriz, tamano);
    encontrar_max_secuencia(matriz, tamano);
    liberar_matriz(matriz, tamano);
    return 0;
}