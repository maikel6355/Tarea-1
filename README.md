# Tarea-1

### lo más importante de

`int **cargar_matriz(const char *nombre_archivo, int *tamano) {`
- se abre con
`fopen(nombre_archivo, "r")`
- se utilizan punteros.
- se uliliza
`realloc(matriz, filas * sizeof(int *))`
para reservar memoria dinamicamente.
- se verifica que sólo se encuenten 1s y 0s.

### lo destacado de

`int encontrar_max_secuencia(int **matriz, int tamano) {`
- se recorre la matriz en dos fases, primeron iniciando desde la primera columna, seguido de la primera fila

### Para liberar

`void liberar_matriz(int **matriz, int tamano)`
- se utiliza el `free(matriz)` para liberar la memoria dinamica utilizada

### Extras

- se utiliza `void mostrar_matriz(int **matriz, int tamano)` con un `for` y un `printf` para mostrar la matriz
- además la función principal
`int main() {` que se encarga de recopilar las anteriores.
