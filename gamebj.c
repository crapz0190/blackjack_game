#include <stdio.h>
#include <string.h>
#define SIZE 50

void greeting();
void get_name(char *name);
void choose_opt(int *opt);

int main() {
    char name[SIZE];
    int opt = 0;

    get_name(name);

    choose_opt(&opt);

    return 0;
}

void greeting() {
    // Representación de "Bienvenido" en asteriscos
    const char *welcome[] = {
        "************   ******  *************  ***          ***   ***                 ***   ************* ***          ***  ******  ****              *****************",
        "*************   ****  *** *********   ***          ***   ***                 ***  *************  ***          ***   ****   ********          *****************",
        "***        ***  ****  ***             ***          ***   ***                 ***  ***            ***          ***   ****   **********        *****       *****",
        "***        ***  ****  ***             ****         ***   ***                 ***  ***            ****         ***   ****   ************      *****       *****",
        "***        ***  ****  ***             *****        ***   ***                 ***  ***            *****        ***   ****   ****    ******    *****       *****",
        "***        ***  ****  ***             ******       ***   ***                 ***  ***            ******       ***   ****   ****      *****   *****       *****",
        "***        ***  ****  ***             *** ***      ***   ***                 ***  ***            *** ***      ***   ****   ****        ***   *****       *****",
        "***       ***   ****  ***             ***  ***     ***   ***                 ***  ***            ***  ***     ***   ****   ****        ****  *****       *****",
        "************    ****  ***********     ***   ***    ***    ***               ***   ***********    ***   ***    ***   ****   ****        ****  *****       *****",
        "************    ****  ***********     ***    ***   ***     ***             ***    ***********    ***    ***   ***   ****   ****        ****  *****       *****",
        "***       ***   ****  ***             ***     ***  ***      ***           ***     ***            ***     ***  ***   ****   ****        ****  *****       *****",
        "***        ***  ****  ***             ***      *** ***       ***         ***      ***            ***      *** ***   ****   ****        ****  *****       *****",
        "***        ***  ****  ***             ***       ******        ***       ***       ***            ***       ******   ****   ****        ****  *****       *****",
        "***        ***  ****  ***             ***        *****         ***     ***        ***            ***        *****   ****   ****       ****   *****       *****",
        "***        ***  ****  ***             ***         ****          ***   ***         ***            ***         ****   ****   ****     *****    *****       *****",
        "***        ***  ****  ***             ***          ***           *** ***          ***            ***          ***   ****   ***********       *****       *****",
        "*************   ****  *************   ***          ***            *****           ************   ***          ***   ****   ********          *****************",
        "************   ******  *************  ***          ***             ***             ************  ***          ***  ******  ****              *****************"
    };

    int rows = sizeof(welcome) / sizeof(welcome[0]); // Número de filas de "Bienvenido"

    // Imprimir filas de asteriscos
    for (int i = 0; i < 24; i++) {
        if (i >= 3 && i < 3 + rows) { // Fila donde se imprime el mensaje
            printf("      "); // Espacio inicial para centrar
            printf("%s\n", welcome[i - 3]); // Imprimir la línea del mensaje
        } else {
            // Imprimir solo asteriscos en otras filas
            for (int j = 0; j < 170; j++) {
                printf("*");
            }
            printf("\n"); // Salto de línea al final de cada fila
        }
    }
}

void get_name(char *name) {
    printf("\n¿Cuál es tu nombre? ");
    fgets(name, SIZE, stdin);
    name[strcspn(name, "\n")] = '\0'; // Reemplaza el salto de línea con el terminador de cadena
    greeting();
    printf("\nHola %s,", name);
    printf("\n");
}

void choose_opt(int *opt){
    do {
        printf("\n\n1) Jugar");
        printf("\n2) Ver reglas");
        printf("\n3) Salir del juego");
        printf("\nElija una opción: ");
        scanf("%d", opt);
        getchar();
        switch (*opt) {
            case 1:
                printf("\nOpción 1 elegida: Jugar");
                break;
            case 2:
                printf("\nOpción 2 elegida: Ver reglas");
                break;
            case 3:
                printf("\nSaliendo del juego.");
                break;      
            default:
                printf("\nOpción no válida. Por favor, elija nuevamente.");
                break;
        }
    } while (*opt != 3);
}