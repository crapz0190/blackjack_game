#include <stdio.h>
#include <string.h>
#include "config.h"

int main(){

    int opt = 0;
    Jugador jugadores[MAX_JUGADORES];
    int numJugadores = 0;

    FILE *archivo;
    char c;
    archivo=fopen("archivo.txt","r");
    if(archivo==NULL){
        printf("El archivo no se puede abrir.\n");
        return 1;
    }
    while((c=fgetc(archivo))!=EOF){
        printf("%c",c);
    }

    printf("\n");
    printf("\n");

    if (numJugadores < MAX_JUGADORES) {
        printf("\t\tIngrese su nombre: ");
        fgets(jugadores[numJugadores].nombre, sizeof(jugadores[numJugadores].nombre), stdin);
        size_t len = strlen(jugadores[numJugadores].nombre);
        // Se elimina salto de línea del arreglo de caracteres
        if (len > 0 && jugadores[numJugadores].nombre[len - 1] == '\n') {
            jugadores[numJugadores].nombre[len - 1] = '\0';
        }
        (numJugadores)++;
    }

    saludo_bienvenida(jugadores, numJugadores);
    imprimir_reglas();

    choose_opt(&opt, jugadores, &numJugadores);

    // ---------- ranking --------------
    //          codigo aqui
    // ---------- ranking --------------

    printf("\nPresione una tecla para salir\n");
    getchar();

    return 0;
}