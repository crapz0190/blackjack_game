#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <stdlib.h>

void merge(Jugador jugadores[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Asignación dinámica de memoria
    Jugador *L = (Jugador *)malloc(n1 * sizeof(Jugador));
    Jugador *R = (Jugador *)malloc(n2 * sizeof(Jugador));

    // Verificar si la asignación fue exitosa
    if (L == NULL || R == NULL) {
        printf("Error al asignar memoria.\n");
        exit(EXIT_FAILURE); // Terminar el programa en caso de error
    }

    // Copiar datos a los arreglos temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = jugadores[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = jugadores[mid + 1 + i];

    int i = 0, j = 0, k = left;

    // Mezclar los arreglos L[] y R[] en jugadores[]
    while (i < n1 && j < n2) {
        if (L[i].contador_ganancias >= R[j].contador_ganancias) {
            jugadores[k] = L[i];    
            i++;
        } else {
            jugadores[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si los hay
    while (i < n1) {
        jugadores[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si los hay
    while (j < n2) {
        jugadores[k] = R[j];
        j++;
        k++;
    }

    // Liberar la memoria dinámica asignada
    free(L);
    free(R);
}


void merge_sort(Jugador jugadores[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(jugadores, left, mid);
        merge_sort(jugadores, mid + 1, right);

        merge(jugadores, left, mid, right);
    }
}

// Mostrar ranking de ganadores
void mostrar_ranking(Jugador jugadores[], int numJugadores) {
    merge_sort(jugadores, 0, numJugadores - 1);

    printf("\n--- Ranking de Ganadores ---\n");
    for (int i = 0; i < numJugadores; i++) {
        if (jugadores[i].contador_ganancias > 0) {
            printf("%d. %s - Ganancias: USD %d\n", i + 1, jugadores[i].nombre, jugadores[i].contador_ganancias);
        }
    }
}

// Mostrar ranking de perdedores
void mostrar_ranking_perdedores(Jugador jugadores[], int numJugadores) {
    merge_sort(jugadores, 0, numJugadores - 1);

    printf("\n--- Ranking de Perdedores ---\n");
    for (int i = 0; i < numJugadores; i++) {
        if (jugadores[i].contador_perdidas > 0) {
            printf("%d. %s - Pérdidas: USD %d\n", i + 1, jugadores[i].nombre, jugadores[i].contador_perdidas);
        }
    }
}


void mostrar_ranking_empatadas(Jugador jugadores[], int numJugadores) {
    merge_sort(jugadores, 0, numJugadores - 1);

    printf("\n--- partidas empatadas ---\n");
    for (int i = 0; i < numJugadores; i++) {
        if (jugadores[i].partidas_empatadas > 0) {
            printf("%d. %s - Partidas empatadas\n", i + 1, jugadores[i].nombre, jugadores[i].partidas_empatadas);
        }
    }
}

void mostrar_contenido_archivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s para mostrar su contenido.\n", nombreArchivo);
        return;
    }

    char linea[256];
    printf("\n-------- REGISTROS --------\n", nombreArchivo);
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea); // Imprime cada línea del archivo
    }
    printf("--------------------------------");
    printf("\n");
    fclose(archivo);
}
