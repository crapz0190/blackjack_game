#include <stdio.h>
#include <string.h>
#include "config.h"
#include<stdlib.h>

// Comparar jugadores para el ranking combinado
int comparar_combinado(const void *a, const void *b) {
    const Jugador *jugadorA = (const Jugador *)a;
    const Jugador *jugadorB = (const Jugador *)b;

    // Primero, comparar por ganancias
    if (jugadorB->contador_ganancias != jugadorA->contador_ganancias) {
        return jugadorB->contador_ganancias - jugadorA->contador_ganancias;
    }

    // Si las ganancias son iguales, ordenar por menor cantidad de pérdidas
    return jugadorA->contador_perdidas - jugadorB->contador_perdidas;
}

// Mostrar ranking combinado
void mostrar_ranking_combinado(Jugador jugadores[], int numJugadores) {
    if (numJugadores == 0) {
        printf("No hay jugadores registrados para mostrar el ranking.\n");
        return;
    }

    // Crear una copia para no modificar el arreglo original
    Jugador copiaJugadores[MAX_JUGADORES];
    memcpy(copiaJugadores, jugadores, sizeof(Jugador) * numJugadores);

    // Ordenar jugadores usando la función comparar_combinado
    qsort(copiaJugadores, numJugadores, sizeof(Jugador), comparar_combinado);

    printf("\n----- RANKING COMBINADO -----\n");
    printf("Posición\tNombre\t\tGanancias\tPérdidas\n");

    for (int i = 0; i < numJugadores; i++) {
        printf("%d\t\t%s\t\t%d\t\t%d\n",
            i + 1, // Posición del jugador (i+1 para numerar desde 1)
            copiaJugadores[i].nombre, // Nombre del jugador
            copiaJugadores[i].contador_ganancias, // Número de ganancias del jugado
            copiaJugadores[i].contador_perdidas); // Número de pérdidas del jugador
    }
}
