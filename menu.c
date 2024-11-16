#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "config.h"

// Menu principal
void choose_opt(int *opt, Jugador jugadores[], int *numJugadores){  // Función de elegir opción
    do {
        printf("\n1) Agregar jugador\n");
        printf("2) Jugar\n");
        printf("3) Lista de jugadores\n");
        printf("4) Ver reglas\n");
        printf("5) Ver ranking de ganadores\n");
        printf("6) Ver ranking de perdedores\n");
        printf("7) Salir del juego\n");
        printf("\nOpción: ");
        scanf("%d", opt);
        getchar(); // limpia el buffer
        switch (*opt) {
            case 1:
                printf("\nOpción %d elegida: \n", *opt);
                if (*numJugadores < MAX_JUGADORES) {
                    printf("Ingrese el nombre del jugador %d: ", *numJugadores + 1);
                    fgets(jugadores[*numJugadores].nombre, sizeof(jugadores[*numJugadores].nombre), stdin);
                    size_t len = strlen(jugadores[*numJugadores].nombre);
                    // Se elimina salto de línea del arreglo de caracteres
                    if (len > 0 && jugadores[*numJugadores].nombre[len - 1] == '\n') {
                        jugadores[*numJugadores].nombre[len - 1] = '\0';
                    }
                    (*numJugadores)++;
                } else {
                    printf("Máximo de jugadores alcanzado.\n");
                }
                break;

            // ------ case 2: funciones de juego contenidos en archivo jugar_bj.c ------
            case 2:
                if (*numJugadores > 0) {
                    printf("\nOpción %d elegida: Jugar\n", *opt);
                    int cartas[MAX_CARTAS];
                    barajar(cartas); // Baraja cartas
                    jugar_blackjack(cartas, jugadores, *numJugadores);
                } else {
                    printf("No hay jugadores para jugar.\n");
                }
                break;

            case 3:
                printf("\nOPCION 3 ELEGIDA: LISTA DE JUGADORES\n");
                imprimir_jugadores(jugadores, *numJugadores);
                break;

            case 4:
                printf("\nOpción %d elegida: VER REGLAS \n", *opt);
                imprimir_reglas();
                break;

            case 5:
                printf("\nOPCION 5 ELEGIDA: Ver ranking ganadores:\n");
                // Lógica de ranking ganadores aquí
                break;

            case 6:
                printf("\nOPCION 6 ELEGIDA: Ver ranking perdedores:\n");
                // Lógica de ranking perdedores aquí
                break;

            case 7:
                printf("SALIENDO DEL JUEGO!\n");
                break;

            default:
                printf("\nOpción no válida. Por favor, elija nuevamente.\n");
                break;
        }
    } while (*opt != 7);
}

// Imprimir reglas
void imprimir_reglas(){
    printf("\n\t-----------------------------------------------------------------------------------------------------\n");
    printf("\n1) Objetivo: Acercarse lo más posible a 21 puntos sin pasarse.\n ");
    printf("\n2) Valor de las cartas: Las cartas numéricas valen su número.\n");
    printf("\t-> Las figuras (J, Q, K) valen 10 puntos.\n");
    printf("\t-> El As vale 1 o 11, según lo que más beneficie al jugador.\n");
    printf("\n3) Reparto: El crupier reparte dos cartas al jugador y dos para sí mismo (una boca arriba y otra boca abajo).\n");
    printf("\n4) Acciones del jugador: Pedir carta (Hit): Recibir una carta adicional.\n");
    printf("\t-> Plantarse (Stand): No recibir más cartas.\n");
    printf("\n5) Crupier: Debe pedir cartas hasta tener al menos 17 puntos. Si supera 21, pierde.\n");
    printf("\n6) Ganar: Gana quien tenga 21 puntos o esté más cerca sin pasarse. Si se empatan los puntos, es un 'push' (empate).\n");
    printf("\n\t-----------------------------------------------------------------------------------------------------");
}

// Imprimir lista de jugadores
void imprimir_jugadores(Jugador jugadores[], int numJugadores){
    if (numJugadores == 0) {
        printf("No hay jugadores para mostrar.\n");
    } else {
        for (int i = 0; i < numJugadores; i++) {
            printf("Jugador[%d]: %s\n", i + 1, jugadores[i].nombre);
        }
    }
}