#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h>  // strcpy
#include "producto.h" // Definición de la estructura Producto

/* --------------------------- FUNCIONES ----------------------*/

// Función para cargar los productos desde un archivo
Producto* cargarProductosDesdeArchivo(const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "r");  // Abrir archivo para lectura
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    Producto* head = NULL; // apuntador a la cabeza de la lista, lo inicializamos en NULL porque pensamos que la lista está vacía
    Producto* tail = NULL; // apuntador a la cola de la lista, lo inicializamos en NULL

    // Variables temporales para almacenar los datos leídos del archivo
    char nombre[100];
    float costo;
    int cantidad;
    char categoria[50];
    char marca[50];
    float voltaje;
    char descripcion[200];
    char caracteristicas[200];

    // Leer los productos desde el archivo
    while (fscanf(f, "%s %f %d %s %s %f %s %[^\n]",
                  nombre, &costo, &cantidad, categoria, marca, &voltaje, caracteristicas, descripcion) == 8) {
        Producto* nuevo = (Producto*)malloc(sizeof(Producto)); // Reservamos memoria para un nuevo nodo de producto
        if (nuevo == NULL) { // Si no se pudo reservar memoria
            printf("Error de memoria.\n");
            fclose(f);
            return NULL;
        }

        // Asignar valores a los campos del nuevo producto
        strcpy(nuevo->nombre, nombre);
        nuevo->costo = costo;
        nuevo->cantidad = cantidad;
        strcpy(nuevo->categoria, categoria);
        strcpy(nuevo->marca, marca);
        nuevo->voltaje = voltaje;
        strcpy(nuevo->descripcion, descripcion);
        strcpy(nuevo->caracteristicas, caracteristicas);
        nuevo->siguiente = NULL;

        // Agregar el nuevo producto a la lista
        if (head == NULL) { // Si la lista está vacía
            head = nuevo; // La cabeza de la lista apunta al nuevo nodo
            tail = nuevo; // La cola de la lista apunta al nuevo nodo
        } else { // Si no está vacía
            tail->siguiente = nuevo; // La cola de la lista apunta al nuevo nodo
            tail = nuevo; // La cola de la lista se actualiza para que apunte al nuevo nodo
        }
    }

    fclose(f); // Cerramos el archivo abierto
    return head; // Regresamos la cabeza de la lista (el primer nodo)
}

// Función para mostrar un producto
void mostrarProductoActual(Producto* actual) {
    // Verificamos que el apuntador actual no sea NULL
    if (actual != NULL) {
        // Mostrar el nombre del producto
        printf("Producto: %s\n", actual->nombre);
        printf("Costo: $%.2f\n", actual->costo);
        printf("Cantidad: %d\n", actual->cantidad);
        printf("Categoría: %s\n", actual->categoria);
        printf("Marca: %s\n", actual->marca);
        printf("Voltaje: %.2f\n", actual->voltaje);
        printf("Descripción: %s\n", actual->descripcion);
        printf("Características: %s\n", actual->caracteristicas);
    } else {
        // Si el puntero es NULL, mostrar un mensaje de error
        printf("Error: El producto es NULL.\n");
    }
}

// Función para avanzar al siguiente producto
Producto* avanzarProducto(Producto* actual) {
    if (actual == NULL) { // Si la lista está vacía
        printf("Error: El producto actual es NULL.\n");
        return actual; // No cambia el apuntador si es NULL
    }
    if (actual->siguiente == NULL) { // Si no hay más productos
        printf("No hay más productos.\n");
        return actual; // Mantenemos el apuntador en el último producto
    }
    return actual->siguiente; // Avanzar al siguiente producto
}

// Función para retroceder al producto anterior
Producto* retrocederProducto(Producto* cabeza, Producto* actual) {
    if (actual == NULL) { // Si la lista está vacía
        printf("Error: El producto actual es NULL.\n");
        return actual; // No cambiamos el apuntador si es NULL
    }
    if (actual == cabeza) { // Si estamos en el primer producto
        printf("No hay producto anterior.\n");
        return actual; // Mantenemos el apuntador en el primer producto
    }

    // Buscar el nodo anterior
    Producto* temp = cabeza;
    while (temp != NULL && temp->siguiente != actual) {
        temp = temp->siguiente; // Avanzamos al siguiente nodo de la lista
    }

    return temp; // Devolvemos el nodo anterior al producto actual
}

// Función para copiar un producto
Producto* copiarProducto(Producto* original) {
    if (original == NULL) { // Si el producto original es NULL
        return NULL; // No hay nada que copiar
    }

    Producto* nuevo = (Producto*)malloc(sizeof(Producto)); // Reservamos memoria para un nuevo nodo de producto
    if (nuevo == NULL) { // Si no se pudo reservar memoria
        printf("Error de memoria al copiar el producto.\n");
        return NULL; // Regresamos NULL
    }

    // Copiar los datos del producto original
    strcpy(nuevo->nombre, original->nombre);
    nuevo->costo = original->costo;
    nuevo->cantidad = original->cantidad;
    strcpy(nuevo->categoria, original->categoria);
    strcpy(nuevo->marca, original->marca);
    nuevo->voltaje = original->voltaje;
    strcpy(nuevo->descripcion, original->descripcion);
    strcpy(nuevo->caracteristicas, original->caracteristicas);
    nuevo->siguiente = NULL; // El nuevo producto no tiene siguiente

    return nuevo;
}