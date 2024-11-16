#ifndef CONFIG_H
#define CONFIG_H

#define MAX_CARTAS 52 // maximo de cartas en un mazo americano
#define CARTAS_JUGADOR 10 // cantidad maxima de cartas de un jugador/crupier
#define MAX_JUGADORES 4 // máximo de jugadores permitidos

// Estructura para un jugador
typedef struct {
    char nombre[100];
    int mano[CARTAS_JUGADOR];
    int suma;
} Jugador;

void choose_opt(int *opt, Jugador jugadores[], int *numJugadores);
void imprimir_jugadores(Jugador jugadores[], int numJugadores);
void saludo_bienvenida(Jugador jugadores[], int numJugadores);
void imprimir_reglas();
void barajar(int cartas[]);
void jugar_blackjack(int cartas[], Jugador jugadores[], int numJugadores);
int convertir_valor_carta(int carta, int *sumaActual);
void mostrar_carta(int carta);
void mostrar_mano(int mano[], int cantidad);
void mostrar_resultado(Jugador jugadores[], int numJugadores, Jugador *crupier);
void turno_crupier(Jugador *crupier, int cartas[], int *indiceCarta);

#endif