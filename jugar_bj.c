#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

// Barajar el mazo de cartas
void barajar(int cartas[]) {
    int mazo[MAX_CARTAS];

    for (int i = 0; i < MAX_CARTAS; i++) {
        mazo[i] = (i / 13 + 3) * 100 + i % 13 + 1; // Representar cartas con código
    }

    srand(time(NULL));
    for (int i = 0; i < MAX_CARTAS; i++) {
        int t;
        do {
            t = rand() % MAX_CARTAS;
        } while (mazo[t] == 0);

        cartas[i] = mazo[t];
        mazo[t] = 0; // Marca la carta como tomada
    }
}

// Convertir el valor de la carta
int convertir_valor_carta(int carta, int *sumaActual) {
    int valor = carta % 100;
    if (valor >= 11 && valor <= 13) { // J, Q, K
        return 10;
    }
    if (valor == 1) {
        return (*sumaActual + 11 > 21) ? 1 : 11;
    }
    return valor;
}

// Mostrar una carta
void mostrar_carta(int carta) {
    char palo = carta / 100; // Determina el palo de la carta
    int valor = carta % 100;

    printf("\t\t*******\n");
    printf("\t\t*     *\n");
    printf("\t\t* %c   *\n", palo);
    
    if (valor == 1) {
        printf("\t\t*   A *\n");
    } else if (valor >= 2 && valor <= 10) {
        printf("\t\t*  %2d *\n", valor);
    } else if (valor == 11) {
        printf("\t\t*   J *\n");
    } else if (valor == 12) {
        printf("\t\t*   Q *\n");
    } else if (valor == 13) {
        printf("\t\t*   K *\n");
    }

    printf("\t\t*     *\n");
    printf("\t\t*******\n");
}

// Mostrar la mano de un jugador
void mostrar_mano(int mano[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        mostrar_carta(mano[i]);
    }
}

// Mostrar resultados finales
void mostrar_resultado(Jugador jugadores[], int numJugadores, Jugador *crupier) {
    // Si el crupier se pasó de 21, todos los jugadores ganan
    if (crupier->suma > 21) {
        for (int i = 0; i < numJugadores; i++) {
            // Los jugadores ganan el doble de su apuesta
            jugadores[i].dinero_ganado = jugadores[i].dinero_apostado * 2;
            jugadores[i].monto_apuesta += jugadores[i].dinero_ganado;  // Sumar lo ganado al saldo del jugador
            printf("%s has ganado USD %d\n", jugadores[i].nombre, jugadores[i].dinero_ganado);
        }
        return; // Salir ya que el crupier perdió automáticamente
    }

    // Caso donde el crupier no se pasó de 21
    for (int i = 0; i < numJugadores; i++) {
        if (jugadores[i].suma > 21) {
            printf("%s, te pasaste de 21. ¡GANA EL CRUPIER!\n", jugadores[i].nombre);
            jugadores[i].dinero_perdido = jugadores[i].dinero_apostado; // Perdió su apuesta
            printf("Has perdido USD %d\n", jugadores[i].dinero_perdido);
        } else if (jugadores[i].suma > crupier->suma) {
            printf("\n%s tus puntos fueron %d, ¡GANASTE!\n", jugadores[i].nombre, jugadores[i].suma);
            jugadores[i].dinero_ganado = jugadores[i].dinero_apostado * 2;  // Doble de la apuesta
            jugadores[i].monto_apuesta += jugadores[i].dinero_ganado;  // Sumar lo ganado
            printf("Has ganado USD %d\n", jugadores[i].dinero_ganado);
        } else if (jugadores[i].suma < crupier->suma) {
            printf("El crupier gana contra %s\n", jugadores[i].nombre);
            jugadores[i].dinero_perdido = jugadores[i].dinero_apostado; // Perdió su apuesta
            printf("Has perdido USD %d\n", jugadores[i].dinero_perdido);
        } else {
            jugadores[i].monto_apuesta += jugadores[i].dinero_apostado;  // Vuelve a sumarse la apuesta
            printf("%s tus puntos fueron de %d, ¡Es un empate!\n", jugadores[i].nombre, jugadores[i].suma);
        }
    }
}


// Turno del crupier
void turno_crupier(Jugador *crupier, int cartas[], int *indiceCarta) {
    printf("\nTURNOS DEL CRUPIER:\n");

    // Mostrar las cartas del crupier al principio (una boca arriba y otra boca abajo)
    printf("Carta visible del crupier: \n");
    mostrar_carta(crupier->mano[0]);
    printf("Carta oculta del crupier: [Carta oculta]\n");

    // El crupier pide cartas hasta que tenga al menos 17 puntos
    while (crupier->suma < 17) {
        crupier->mano[2] = cartas[*indiceCarta];
        (*indiceCarta)++;
        printf("El crupier pide una carta: \n");
        mostrar_carta(crupier->mano[2]);
        crupier->suma += convertir_valor_carta(crupier->mano[2], &crupier->suma);
        printf("Total del crupier: %d\n", crupier->suma);
    }

    // Si el crupier supera los 21 puntos, se declara que ha perdido
    if (crupier->suma > 21) {
        printf("\nEl crupier se pasó de 21, ¡todos los jugadores ganan!\n");
    } else {
        printf("\nEl crupier se planta con %d puntos\n", crupier->suma);
    }
}

// Jugar Blackjack para todos los jugadores y el crupier
void jugar_blackjack(int cartas[], Jugador jugadores[], int numJugadores) {
    Jugador crupier = {"Crupier", {0}, 0}; // Crear al crupier
    int indiceCarta = 0;

    // Repartir dos cartas a cada jugador
    for (int i = 0; i < numJugadores; i++) {
        jugadores[i].suma = 0;
        jugadores[i].mano[0] = cartas[indiceCarta++];
        jugadores[i].mano[1] = cartas[indiceCarta++];
    }

    // Repartir dos cartas al crupier
    crupier.mano[0] = cartas[indiceCarta++];
    crupier.mano[1] = cartas[indiceCarta++];

    // Mostrar las manos de los jugadores y del crupier
    for (int i = 0; i < numJugadores; i++) {
        printf("\nDinero disponible de %s: USD %d\n", jugadores[i].nombre, jugadores[i].monto_apuesta);
        printf("\nCARTAS DE %s:\n", jugadores[i].nombre);
        mostrar_mano(jugadores[i].mano, 2);
        jugadores[i].suma = 0;
        for (int j = 0; j < 2; j++) {
            jugadores[i].suma += convertir_valor_carta(jugadores[i].mano[j], &jugadores[i].suma);
        }
        printf("TOTAL DE %s: %d\n", jugadores[i].nombre, jugadores[i].suma);
    }

    printf("\nCARTAS DEL CRUPIER:\n");
    mostrar_mano(crupier.mano, 2);
    crupier.suma = 0;
    for (int i = 0; i < 2; i++) {
        crupier.suma += convertir_valor_carta(crupier.mano[i], &crupier.suma);
    }
    printf("TOTAL DEL CRUPIER: %d\n", crupier.suma);

    // Turno de cada jugador
    for (int i = 0; i < numJugadores; i++) {
        char opcion;
        
        // -------------------- apuestas ----------------------

        char valor[3];  // Arreglo para captura de respuesta (s/n)
        // Preguntar si desea realizar una apuesta
        printf("\n¿Quieres realizar una apuesta? (s/n): ");
        fgets(valor, sizeof(valor), stdin);
        // Eliminar el salto de línea '\n' capturado por fgets
        valor[strcspn(valor, "\n")] = '\0';

        // Validación de entrada
        if (strlen(valor) != 1 || (valor[0] != 's' && valor[0] != 'n')) {
            printf("Entrada no válida, solo se permite una letra (s/n)\n");
            break;
        }

        // Si el jugador dice NO, se termina la partida y se regresa al menú
        if (valor[0] == 'n') {
            printf("Has elegido no apostar. Terminando la partida y regresando al menú\n");
            return; // Sale de la función y termina la partida
        }

        if (valor[0] == 's') {
            printf("Has elegido sí\n");

            // Pedir monto de la apuesta
            int apuestaValida = 0;
            do {
                printf("\t\tIngrese el monto de tu apuesta (mínimo USD 50): ");
                int valor_apuesta;
                scanf("%d", &valor_apuesta);
                getchar(); // Limpiar el buffer

                // Validar monto de apuesta
                if (valor_apuesta >= 50 && valor_apuesta <= jugadores[i].monto_apuesta) {
                    if (valor_apuesta <= jugadores[i].monto_apuesta) {
                        jugadores[i].monto_apuesta -= valor_apuesta; // Restar monto apostado del saldo disponible
                        jugadores[i].dinero_apostado = valor_apuesta;  // Guardar el monto apostado
                        printf("Apuesta de USD %d realizada\n", valor_apuesta);
                        apuestaValida = 1;
                    } else {
                        printf("No tienes suficiente dinero para realizar esa apuesta. Tu saldo es de USD %d\n", jugadores[i].monto_apuesta);
                    }
                } else {
                    printf("\t\tMonto de apuesta inválido\n");
                }
            } while (!apuestaValida);  // Repetir hasta que la apuesta sea válida
        }

        // -------------------- apuestas ----------------------

        // Si el jugador quiere apostar, continúa con el turno de pedir cartas
        while (jugadores[i].suma < 21) {
            printf("%s, ¿deseas pedir otra carta? (s/n): ", jugadores[i].nombre);
            opcion = getchar();
            getchar(); // Limpiar buffer
            if (opcion == 's') {
                jugadores[i].mano[2] = cartas[indiceCarta++];
                printf("Tienes las cartas: \n");
                mostrar_mano(jugadores[i].mano, 3);
                jugadores[i].suma += convertir_valor_carta(jugadores[i].mano[2], &jugadores[i].suma);
                printf("Total: %d\n", jugadores[i].suma);
            } else {
                break;
            }
        }
    }

    // Turno del crupier
    turno_crupier(&crupier, cartas, &indiceCarta);

    // Mostrar el resultado
    mostrar_resultado(jugadores, numJugadores, &crupier);
}
