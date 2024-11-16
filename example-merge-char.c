#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Para usar malloc y free

// Función para fusionar dos subcadenas ordenadas
void fusionar(char* cadena, int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1; // Tamaño del subarreglo izquierdo
    int n2 = fin - medio; // Tamaño del subarreglo derecho

    // Asignar memoria dinámica para los subarreglos temporales
    char *izquierda = (char *)malloc(n1 * sizeof(char));
    char *derecha = (char *)malloc(n2 * sizeof(char));

    if (izquierda == NULL || derecha == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1); // Si no se pudo asignar memoria, salir del programa
    }

    // Copiar los datos a los arreglos temporales
    for (int i = 0; i < n1; i++) {
        izquierda[i] = cadena[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        derecha[j] = cadena[medio + 1 + j];
    }

    // Fusionar los arreglos temporales de nuevo en la cadena original
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (izquierda[i] <= derecha[j]) {
            cadena[k++] = izquierda[i++];
        } else {
            cadena[k++] = derecha[j++];
        }
    }

    // Copiar los elementos restantes de izquierda[], si hay alguno
    while (i < n1) {
        cadena[k++] = izquierda[i++];
    }

    // Copiar los elementos restantes de derecha[], si hay alguno
    while (j < n2) {
        cadena[k++] = derecha[j++];
    }

    // Liberar la memoria asignada dinámicamente
    free(izquierda);
    free(derecha);
}

// Función recursiva para dividir y ordenar la cadena
void mergesort(char *cadena, int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2; // Encuentra el punto medio

        // Ordenar la primera mitad
        mergesort(cadena, inicio, medio);
        
        // Ordenar la segunda mitad
        mergesort(cadena, medio + 1, fin);

        // Fusionar las dos mitades ordenadas
        fusionar(cadena, inicio, medio, fin);
    }
}

int main() {
    char cadena[] = "programacion";

    // Obtenemos la longitud de la cadena
    int longitud = strlen(cadena);

    // Llamamos a mergesort para ordenar la cadena
    mergesort(cadena, 0, longitud - 1);

    // Imprimimos la cadena ordenada
    printf("Cadena ordenada: %s\n", cadena);

    return 0;
}
