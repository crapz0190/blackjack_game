#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "config.h"

// Menu principal
void choose_opt(int *opt, Jugador jugadores[], int *numJugadores){  // Función de elegir opción
    do {
        printf("\n\t1) Jugar\n");
        printf("\t2) Agregar jugador\n");
        printf("\t3) Lista de jugadores\n");
        printf("\t4) Ver reglas\n");
        printf("\t5) Ver ranking de ganadores\n");
        printf("\t6) Ver ranking de perdedores\n");
        printf("\t7) Salir del juego\n");
        printf("\nOpción: ");
        scanf("%d", opt);
        getchar(); // limpia el buffer
        switch (*opt) {
            

            // ------ case 1: funciones de juego contenidos en archivo jugar_bj.c ------
            case 1:
                if (*numJugadores > 0) {
                    printf("\nOpción %d elegida: Jugar\n", *opt);
                    int cartas[MAX_CARTAS];
                    barajar(cartas); // Baraja cartas
                    jugar_blackjack(cartas, jugadores, *numJugadores);
                } else {
                    printf("No hay jugadores para jugar.\n");
                }
                break;

            case 2:
                printf("\nOpción %d elegida: Agregar jugador\n", *opt);
                printf("\nTotal de jugadores a agregar permitidos son %d\n", MAX_JUGADORES);

                char valor[3];  // Arreglo para captura de respuesta (s/n)

                // Pedir confirmación
                printf("¿Deseas continuar? (s/n): ");
                fgets(valor, sizeof(valor), stdin);

                // Eliminar el salto de línea '\n' capturado por fgets
                valor[strcspn(valor, "\n")] = '\0';  // Esto reemplaza '\n' por '\0' si está presente

                // Validación de entrada
                if (strlen(valor) != 1 || (valor[0] != 's' && valor[0] != 'n')) {
                    printf("Entrada no válida, solo se permite una letra (s/n).\n");
                    break;
                }

                if (valor[0] == 's') {
                    if (*numJugadores < MAX_JUGADORES) {
                        printf("Ingrese el nombre del jugador %d: ", *numJugadores + 1);
                        fgets(jugadores[*numJugadores].nombre, sizeof(jugadores[*numJugadores].nombre), stdin);

                        // Eliminar salto de línea al final del nombre
                        jugadores[*numJugadores].nombre[strcspn(jugadores[*numJugadores].nombre, "\n")] = '\0';

                        (*numJugadores)++;
                    } else {
                        printf("Máximo de jugadores alcanzado.\n");
                    }
                } else if (valor[0] == 'n') {
                    printf("Has elegido no.\n");
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

void saludo_bienvenida(Jugador jugadores[], int numJugadores){
    printf("\nBienvenido/a %s\n", jugadores[0].nombre);
}