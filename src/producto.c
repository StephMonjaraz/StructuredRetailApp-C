#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "producto.h"

// Función para poder cargar productos desde archivo
Producto* cargarProductosDesdeArchivo(const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "r");
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    Producto* head = NULL;
    Producto* tail = NULL;
    char nombre[100];
    float costo;

    while (fscanf(f, "%s %f", nombre, &costo) == 2) {
        Producto* nuevo = (Producto*)malloc(sizeof(Producto));
        if (nuevo == NULL) {
            printf("Error de memoria.\n");
            fclose(f);
            return NULL;
        }

        strcpy(nuevo->nombre, nombre);
        nuevo->costo = costo;
        nuevo->siguiente = NULL;

        if (head == NULL) {
            head = nuevo;
            tail = nuevo;
        } else {
            tail->siguiente = nuevo;
            tail = nuevo;
        }
    }

    fclose(f);
    return head;
}

// muestraa todos los productos 
void mostrarListaProductos(Producto* lista) {
    Producto* actual = lista;
    while (actual != NULL) {
        printf("Producto: %s\n", actual->nombre);
        printf("Costo: $%.2f\n", actual->costo);
        printf("----------------------\n");
        actual = actual->siguiente;
    }
}

//prueba
int main() {
    Producto* lista = cargarProductosDesdeArchivo("../data/productos.txt");

    if (lista == NULL) {
        printf("No se cargaron productos.\n");
        return 1;
    }

    printf("Productos cargados desde archivo:\n\n");
    mostrarListaProductos(lista);


    // liberar memoria
    Producto* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->siguiente;
        free(temp);

    }

    return 0;
}
