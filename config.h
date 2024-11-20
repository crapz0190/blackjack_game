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
    int monto_inicial;
    int monto_apuesta;
    int dinero_apostado;
    int dinero_perdido;
    int dinero_ganado;
    int partidas_ganadas;
    int partidas_perdidas;
    int partidas_empatadas;
    int contador_ganancias;
    int contador_perdidas;
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

void merge_sort(Jugador jugadores[], int left, int right);
void merge(Jugador jugadores[], int left, int mid, int right);
void mostrar_ranking(Jugador jugadores[], int numJugadores);
void mostrar_ranking_perdedores(Jugador jugadores[], int numJugadores);
void mostrar_ranking_empatadas(Jugador jugadores[], int numJugadores);

void guardar_datos_jugador(Jugador jugador);
void guardar_registro_partida(Jugador jugadores);
void mostrar_contenido_archivo(const char *nombreArchivo);

void mostrar_ranking_combinado(Jugador jugadores[], int numJugadores);



#endif
