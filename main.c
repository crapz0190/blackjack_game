#include <stdio.h>
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

    choose_opt(&opt, jugadores, &numJugadores);

    // ---------- ranking --------------
    //          codigo aqui
    // ---------- ranking --------------

    printf("\nPresione una tecla para salir\n");
    getchar();

    return 0;
}