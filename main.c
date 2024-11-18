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

        do {
            printf("\t\tIngrese monto para apuestas (mínimo: USD 500 - máximo USD 5000): ");
            scanf("%d", &jugadores[numJugadores].monto_apuesta);
            getchar();
            if(jugadores[numJugadores].monto_apuesta >= 500 && jugadores[numJugadores].monto_apuesta <= 5000){
                saludo_bienvenida(jugadores, numJugadores);
                imprimir_reglas();

            } else {
                printf("\n\t\tMonto Ingresado inválido, intente de nuevo\n");
            }

        } while(jugadores[numJugadores].monto_apuesta < 500 || jugadores[numJugadores].monto_apuesta > 5000);
            
        (numJugadores)++;
    }

    choose_opt(&opt, jugadores, &numJugadores);
    

    // ---------- ranking --------------
    //          codigo aqui
    // ---------- ranking --------------

    printf("\nPresione una tecla para salir\n");
    getchar();

    return 0;
}