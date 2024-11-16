#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_CARTAS 52 // máximo de cartas en un mazo americano
#define CARTAS_JUGADOR 10 // cantidad máxima de cartas de un jugador/crupier
#define MAX_JUGADORES 4 // máximo de jugadores permitidos

// Estructura para un jugador
typedef struct {
    char nombre[100];
    int mano[CARTAS_JUGADOR];
    int suma;
} Jugador;

// prototipos de funciones
void imprimir_saludo(char nombre[]);
void choose_opt(int *opt, Jugador jugadores[], int *numJugadores);
void imprimir_reglas();
void barajar(int cartas[]);
void jugar_blackjack(int cartas[], Jugador *jugador);
int convertir_valor_carta(int carta, int *sumaActual);
void mostrar_carta(int carta);
void mostrar_mano(int mano[], int cantidad);
void mostrar_ranking_ganador();
void mostrar_perdedores();
void guardar_ganador(char nombre[]);
void guardar_perdedor(char nombre[]);

int main() {
    int opt = 0;
    Jugador jugadores[MAX_JUGADORES];
    int numJugadores = 0;

    printf("\nBienvenido a BLACKJACK!\n");
    choose_opt(&opt, jugadores, &numJugadores);

    return 0;
}

// Saludo del jugador
void imprimir_saludo(char nombre[]) {   
    size_t len = strlen(nombre);
    if(len > 0 && nombre[len-1] == '\n') {    
        nombre[len-1] = '\0';
    }
    printf("\nHOLA %s! Bienvenido a BLACKJACK \n", nombre);
}

// Menú principal
void choose_opt(int *opt, Jugador jugadores[], int *numJugadores) {
    do {
        printf("\n1) Agregar jugador\n");
        printf("2) Jugar\n");
        printf("3) Ver reglas\n");
        printf("4) Ver ranking de ganadores\n");
        printf("5) Ver ranking de perdedores\n");
        printf("6) Salir del juego\n");
        printf("\n");
        scanf("%d", opt);
        getchar(); // limpia el buffer
        switch (*opt) {
            case 1:
                if (*numJugadores < MAX_JUGADORES) {
                    printf("Ingrese el nombre del jugador %d: ", *numJugadores + 1);
                    fgets(jugadores[*numJugadores].nombre, sizeof(jugadores[*numJugadores].nombre), stdin);
                    size_t len = strlen(jugadores[*numJugadores].nombre);
                    if (len > 0 && jugadores[*numJugadores].nombre[len - 1] == '\n') {
                        jugadores[*numJugadores].nombre[len - 1] = '\0';
                    }
                    (*numJugadores)++;
                } else {
                    printf("Máximo de jugadores alcanzado.\n");
                }
                break;

            case 2:
                if (*numJugadores > 0) {
                    printf("\nOpción 2 elegida: Jugar\n");
                    int cartas[MAX_CARTAS];
                    barajar(cartas); // baraja cartas
                    for (int i = 0; i < *numJugadores; i++) {
                        jugar_blackjack(cartas, &jugadores[i]);
                    }
                } else {
                    printf("No hay jugadores para jugar.\n");
                }
                break;

            case 3:
                printf("\nOPCION 3 ELEGIDA: VER REGLAS\n");
                imprimir_reglas();
                break;

            case 4:
                printf("\nOPCION 4 ELEGIDA: Ver ranking de ganadores:\n");
                mostrar_ranking_ganador();
                break;

            case 5:
                printf("OPCION 5 ELEGIDA: Ver ranking de perdedores:\n");
                mostrar_perdedores();
                break;

            case 6:
                printf("SALIENDO DEL JUEGO!");
                break;

            default:
                printf("\nOpción no válida. Por favor, elija nuevamente.");
                break;
        }
    } while (*opt != 6);
}

// Imprimir reglas
void imprimir_reglas() {
    printf("\n\t-----------------------------------------------------------------------------------------------------\n");
    printf("1) Objetivo: Acercarse lo más posible a 21 puntos sin pasarse.\n");
    printf("2) Valor de las cartas: Las cartas numéricas valen su número.\n");
    printf("\t-> Las figuras (J, Q, K) valen 10 puntos.\n");
    printf("\t-> El As vale 1 o 11, según lo que más beneficie al jugador.\n");
    printf("3) Reparto: El crupier reparte dos cartas al jugador y dos para sí mismo (una boca arriba y otra boca abajo).\n");
    printf("4) Acciones del jugador: Pedir carta (Hit): Recibir una carta adicional.\n");
    printf("\t-> Plantarse (Stand): No recibir más cartas.\n");
    printf("5) Crupier: Debe pedir cartas hasta tener al menos 17 puntos. Si supera 21, pierde.\n");
    printf("6) Ganar: Gana quien tenga 21 puntos o esté más cerca sin pasarse. Si se empatan los puntos, es un 'push' (empate)\n");
    printf("\n\t-----------------------------------------------------------------------------------------------------\n");
}

void barajar(int cartas[]) {
    int mazo[MAX_CARTAS];

    for (int i = 0; i < MAX_CARTAS; i++) {
        mazo[i] = (i / 13 + 3) * 100 + i % 13 + 1; // representar cartas con código
    }

    srand(time(NULL));
    for (int i = 0; i < MAX_CARTAS; i++) {
        int t;
        do {
            t = rand() % MAX_CARTAS;
        } while (mazo[t] == 0);

        cartas[i] = mazo[t];
        mazo[t] = 0; // marca la carta como tomada
    }
}

void jugar_blackjack(int cartas[], Jugador *jugador) {
    jugador->suma = 0;
    jugador->mano[0] = cartas[rand() % MAX_CARTAS];
    jugador->mano[1] = cartas[rand() % MAX_CARTAS];

    printf("\nCARTAS DE %s:\n", jugador->nombre);
    mostrar_mano(jugador->mano, 2);
    
    for (int i = 0; i < 2; i++) {
        jugador->suma += convertir_valor_carta(jugador->mano[i], &jugador->suma);
    }

    printf("TOTAL DE %s: %d\n", jugador->nombre, jugador->suma);

    char opcion;
    while (jugador->suma < 21) {
        printf("Deseas pedir otra carta? (s/n): ");
        opcion = getchar();
        getchar(); // limpia el buffer
        if (opcion == 's') {
            jugador->mano[2] = cartas[rand() % MAX_CARTAS];
            printf("DIBUJASTE: \n");
            mostrar_carta(jugador->mano[2]);
            jugador->suma += convertir_valor_carta(jugador->mano[2], &jugador->suma);
            printf("TOTAL DE %s: %d\n", jugador->nombre, jugador->suma);
        } else {
            break; // el jugador no pide más cartas
        }
    }

    if (jugador->suma > 21) {
        printf("%s, te pasaste de 21. ¡GANA EL CRUPIER!\n", jugador->nombre);
        guardar_perdedor(jugador->nombre);
    } else {
        // Aquí podrías añadir la lógica para el crupier y determinar el ganador.
        printf("Resultados del crupier se determinarán aquí...\n");
    }
}

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

// Mostrar mano del jugador
void mostrar_mano(int mano[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        mostrar_carta(mano[i]);
    }
}

void guardar_ganador(char nombre[]) {
    FILE *archivo = fopen("ranking.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "%s\n", nombre);
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo de ganadores.\n");
    }
}

void guardar_perdedor(char nombre[]) {
    FILE *archivo = fopen("perdedores.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "%s\n", nombre);
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo de perdedores.\n");
    }
}

void mostrar_ranking_ganador() {
    FILE *archivo = fopen("ranking.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de ranking de ganadores.\n");
        return;
    }

    printf("------------------------------------------------------\n");
    printf("\nRANKING DE GANADORES: \n");
    char linea[100];
    while (fgets(linea, sizeof(linea), archivo)) {
        printf(" %s", linea);
    }
    fclose(archivo);
    printf("\n------------------------------------------------------\n");
}

void mostrar_perdedores() {
    FILE *archivo = fopen("perdedores.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de ranking de perdedores.\n");
        return;
    }
    printf("-----------------------------------------------------\n");
    printf("\nRANKING DE PERDEDORES:\n");
    char linea[100];
    while (fgets(linea, sizeof(linea), archivo)) {
        printf(" %s", linea);
    }
    fclose(archivo);
    printf("\n-----------------------------------------------------\n");
}
