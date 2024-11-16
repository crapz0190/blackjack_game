#include <stdio.h>
#include <stdlib.h>

void ordenar(int arreglo[], int tamanio);
void merge_sort(int arreglo[], int inicio, int fin);
void merge(int arreglo[], int inicio, int medio, int fin);
void imprimir_arreglo(int arreglo[], int tamanio);

int main(){
    int arr[] = {12,65,3,87,-23,199,-345,-1,0,10};
    int longitud = sizeof(arr) / sizeof(arr[0]);

    // arreglo si ordenar
    printf("\narreglo sin ordenar\n");
    imprimir_arreglo(arr, longitud);
    // metodo de ordenamiento
    ordenar(arr, longitud-1);
    // arreglo ordenado
    printf("\narreglo ordenado\n");
    imprimir_arreglo(arr, longitud);

    return 0;
}

void ordenar(int arreglo[], int tamanio){
    merge_sort(arreglo, 0, tamanio);
}

void merge_sort(int arreglo[], int inicio, int fin){
    if(inicio < fin){
        // encontrar punto medio
        int medio = inicio + (fin - inicio) / 2;

        // ordenar la 1ra y 2da mitad
        merge_sort(arreglo, inicio, medio);
        merge_sort(arreglo, medio + 1, fin);

        // fusionar las mitades ordenadas
        merge(arreglo, inicio, medio, fin);
    }
}

void merge(int arreglo[], int inicio, int medio, int fin){
    int tamLadoIzq = medio - inicio + 1;
    int tamLadoDer = fin - medio;

    // crear arreglos temporales para almacenar los datos
    int *izq = (int *)malloc(tamLadoIzq * sizeof(int));
    int *der = (int *)malloc(tamLadoDer * sizeof(int));

    // copiar los datos a los arreglos temporales izq[] y der[]
    for(int i = 0; i < tamLadoIzq; i++){
        izq[i] = arreglo[inicio + i];
    }

    for(int j = 0; j < tamLadoDer; j++){
        der[j] = arreglo[medio + 1 + j];
    }

    // fusionar los subarreglos en un nuevo arreglo[izq ... der]
    int i = 0,j = 0, k=inicio;
    while(i < tamLadoIzq && j < tamLadoDer){
        if(izq[i] <= der[j]){
            arreglo[k] = izq[i];
            i++;
        } else {
            arreglo[k] = der[j];
            j++;
        }
        k++;
    }

    // copiar los elementos restantes de izq[], si los hay
    while(i < tamLadoIzq){
        arreglo[k] = izq[i];
        i++;
        k++;
    }
    
    // copiar los elementos restantes de der[], si los hay
    while(j < tamLadoDer){
        arreglo[k] = der[j];
        j++;
        k++;
    }

    // Liberar la memoria de los arreglos temporales
    free(izq);
    free(der);
}

void imprimir_arreglo(int arreglo[], int tamanio){
    for(int i = 0; i < tamanio; i++){
        printf("%d ", arreglo[i]);
    }
}