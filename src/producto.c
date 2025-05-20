#include <stdio.h>
#include <stdlib.h> //libreria para las funciones de memoria dinámica. (malloc, free)
#include <string.h>  //libreria para las funciones de manipulación de cadenas (strcpy)
#include "producto.h" // donde se declaran las funciones y estructuras de producto
#include "estilos.h" // donde se declaran los estilos de texto


/* *--------------------------- FUNCIONES ----------------------* */

// Funcion que nos permite cargar los productos desde nuestro archivo de texto
Producto* cargarProductosDesdeArchivo(const char* nombreArchivo) { // indicamos que el nombre del archivo es un puntero a una cadena de caracteres y es constante ya que solo lo leeremos
    FILE* f = fopen(nombreArchivo, "r");  // FILE* es un tipo de dato que representa un archivo abierto. fopen abre el archivo en modo lectura ("r").
    if (f == NULL) { // si es que no se pudo abrir el archivo
        printf("   Error al abrir el archivo.\n"); //le indicamos al usuario que hubo un error
        return NULL;
    }

    Producto* head = NULL; // Apuntador a la cabeza de la lista, lo inicializamos en NULL porque pensamos que la lista está vacía
    Producto* tail = NULL; // APuntador a la cola de la lista, lo inicializamos en NULL

    // variables temporales que usaremos para guardar los datos de cada producto
    char nombre[100];
    float costo;
    int cantidad;
    char categoria[50];
    char marca[50];
    float voltaje;
    char descripcion[200];
    char caracteristicas[200];


    // ciclo que nos permite leer el archivo de texto y guardar los datos en la lista enlazada
    while (fscanf(f, "%s %f %d %s %s %f %s %[^\n]", // indicamos el tipo de dato que leeremos y el formato en el que lo leeremos
                  nombre, &costo, &cantidad, categoria, marca, &voltaje, caracteristicas, descripcion) == 8) {
        Producto* nuevo = (Producto*)malloc(sizeof(Producto));//se reserva memoria para un nuevo nodo de producto
        if (nuevo == NULL) { //si no fue posible reservar memoria
            printf("Error de memoria.\n");//le indicamos al usuario que hubo un error
            fclose(f); // fclose cierra el archivo abierto
            return NULL; // retorna NULL para indicar que no se pudo cargar la lista
        }

        // con strcpy copiamos los datos leídos del archivo a los campos del nuevo producto
        strcpy(nuevo->nombre, nombre);
        nuevo->costo = costo;
        nuevo->cantidad = cantidad;
        strcpy(nuevo->categoria, categoria);
        strcpy(nuevo->marca, marca);
        nuevo->voltaje = voltaje;
        strcpy(nuevo->descripcion, descripcion);
        strcpy(nuevo->caracteristicas, caracteristicas);
        nuevo->siguiente = NULL;

       // agregamos el nuevo nodo a la lista enlazada
        if (head == NULL) { //si la lista está vacía
            head = nuevo; //la cabeza de la lista apunta al nuevo nodo
            tail = nuevo; // y la cola tambien apunta al nuevo nodo ya que no hay ningun elemento.
        } else { // Si no está vacía
            tail->siguiente = nuevo; // la cola de la lista apunta al nuevo nodo
            tail = nuevo; // y actualizamos la colsa de la lista se actualiza para que apunte al nuevo nodo
        }
    }

    fclose(f); //cerramos el archivo abierto
    return head; //regresamos la cabeza de la lista que es el primer nodo
}


// Función que nos permitirá  mostrar un producto
void mostrarProductoActual(Producto* actual) {
    if (actual != NULL) { // verificamos que el producto no sea NULL es decir el apuntador actual no es NULL
        // Muestra todo lo relacionado al producto y mantenemos una estetica de colores
        printf("        * Producto: %s\n", actual->nombre);
        printf("          * Costo: $%.2f\n", actual->costo);
        printf("          * Existencia en tienda: %d\n", actual->cantidad);
        printf("          * Categoría: %s\n", actual->categoria);
        printf("          * Marca: %s\n", actual->marca);
        printf("          * Voltaje: %.2f\n", actual->voltaje);
        printf("          * Descripción: %s\n", actual->descripcion);
        printf("          * Características: %s\n", actual->caracteristicas);
    } else {
        // Si el apuntador es NULL, le indicamos al usuario que hubo un error
        printf("     Error: El producto es NULL.\n");
    }
}


// Función que permite avanzar al siguiente producto
Producto* avanzarProducto(Producto* actual) {
    if (actual == NULL) { //si la lista está vacía
        printf("     Error: El producto actual es NULL.\n"); //le indicamos al usuario que hubo un error
        return actual; // si la lista está vacía no cambiamos el apuntador
    }
    // Eliminado mensaje redundante aquí
    if (actual->siguiente == NULL) { //sii no hay más productos, es decir, llegamos al final de la lista
        return actual; //y mantenemos al apuntador en el último producto
    }
    return actual->siguiente; //en caso contrario, devolvemos el siguiente producto
}


// Función que retrocede al producto anterior
Producto* retrocederProducto(Producto* cabeza, Producto* actual) {
    if (actual == NULL) { //si la lista está vacía
        printf("     Error: El producto actual es NULL.\n");
        return actual; //no cambia apuntador si esta vacia.
    }
    // Eliminado mensaje redundante aquí
    if (actual == cabeza) { //si estamos en el primer producto
        return actual; //se mantiene al apuntador en el primer producto
    }

    //busca el nodo anterior
    Producto* temp = cabeza;
    while (temp != NULL && temp->siguiente != actual) { //mientras no lleguemos al final de la lista y el siguiente nodo no sea el actual
        temp = temp->siguiente; // puede avanzar al siguiente nodo
    }

    return temp; // devolvemos el nodo anterior al producto actual
}


// MENSAJE EN ASCII PARA INDICAR QUE ESTAMOS EN EL MENU DE NAVEGACION DE PRODUCTOS
void mostrarMenuNavegacionProductos() {
    printf("\n%s        _____            ____   ____   ____    ______          ____       ____    ___    ____    ____            ___   ____  ___   ____\n",NEON_PURPLE);
    printf("%s       ||___|  ||   ||  ||__   ||  |  ||  ||     ||   ||   ||  ||__      ||  ||  ||__|  ||  ||  ||   |  ||  ||  ||  |   ||  || ||  ||__\n",NEON_PURPLE);
    printf("%s       ||   |  ||   ||     ||  ||     ||__|| *   ||   ||   ||     ||  *  ||__||  ||  |  ||  ||  ||   |  ||  ||  ||      ||  || ||     ||\n",NEON_PURPLE);
    printf("%s       ||___|  ||___||  ___||  ||__|  ||  ||     ||   ||___||  ___||     ||      ||  |  ||__||  ||___|  ||__||  ||__|   ||  ||_||   __||",NEON_PURPLE);
 


    printf(PY" \n\n\n    S --Siguiente producto    ");
    printf(PY"       A --Producto anterior    ");
    printf(PY"       C --Agregar producto al carrito    ");
    printf(PY"       Q --Volver al menú principal \n");
    printf(PY"   __________________________________________________________________________________________________________________________________________  \n\n  ");
    
}

// función para copiar un producto
Producto* copiarProducto(Producto* original) { // La función recibe un apuntador a un producto original y devuelve un apuntador a un nuevo producto
    if (original == NULL) { //si el producto original es NULL
        return NULL; // No podemos copiar nada
    }


    Producto* nuevo = (Producto*)malloc(sizeof(Producto)); //reservamos memoria para un nuevo nodo de producto
    if (nuevo == NULL) { //si no se pudo reservar memoria
        printf("Error de memoria al copiar el producto.\n"); //le indicamos al usuario que hubo un error
        return NULL; //rgresamos NULL
    }


    // copiamos los datos del producto original
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