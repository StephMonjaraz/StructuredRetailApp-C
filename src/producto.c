#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h>  // strcpy
#include "producto.h" // Definición de la estructura Producto

/* --------------------------- FUNCIONES ----------------------*/
Producto* cargarProductosDesdeArchivo(const char* nombreArchivo);
void mostrarProductoActual(Producto* actual);


//prueba 2
int main() {
    // 1. Llamamos a la función cargarProductosDesdeArchivo con el nombre del archivo.
    Producto* lista = cargarProductosDesdeArchivo("../data/productos.txt"); 

    // 2. Verificamos si se cargaron los productos correctamente.
    if (lista == NULL) {
        printf("No se pudieron cargar los productos.\n");
        return 1;  // Salir si no se cargaron productos.
    }

    // 3. Inicializamos 'actual' como el primer producto de la lista.
    Producto* actual = lista;  // La cabeza de la lista es el primer producto

    // 4. Mostramos el primer producto con la función mostrarProductoActual.
    mostrarProductoActual(actual);  // Muestra el primer producto (cabeza de la lista)

    // 5. Avanzamos al siguiente producto
    printf("\nAvanzando al siguiente producto:\n");
    actual = avanzarProducto(actual);  // Avanzamos al siguiente
    mostrarProductoActual(actual);  // Muestra el siguiente

    // 6. Retrocedemos al producto anterior
    printf("\nRetrocediendo al producto anterior:\n");
    actual = retrocederProducto(lista, actual);  // Retrocedemos al anterior
    mostrarProductoActual(actual);  // Moestra el producto anterior

    return 0;
}




// Función que nos permite cargar productos desde un archivo (implementada en src/producto.h)
Producto* cargarProductosDesdeArchivo(const char* nombreArchivo) {
    
    FILE* f = fopen(nombreArchivo, "r"); // sintaxis de fopen -> fopen recibe el nombre del archivo y el modo de apertura
    // "r" significa que se abre el archivo en modo lectura
    if (f == NULL) { // si fopen devuelve NULL significa que no se pudo abrir el archivo/ no tiene permisos
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    Producto* head = NULL; // puntero a la cabeza de la lista, lo inicializamos en NULL porque pensamos que la lista esta vacia
    Producto* tail = NULL; // puntero a la cola de la lista, lo inicializamos en NULL
    // variables temporales para almacenar los datos que leemos  del archivo
    char nombre[100]; 
    float costo;

    /* para leer el archivo linea por linea -> fscanf
    * int fscanf(FILE *stream, const char *format, ...);
    * stream -> puntero al archivo que queremos leer -> f
    * format -> cadena de formato que indica el tipo de datos que queremos leer
    * La función 'fscanf' devuelve el número de elementos correctamente leídos. En este caso, esperamos que lea dos elementos:
    * 1. El nombre del producto (la cade de caracteres).
    * 2. El costo del producto (el número de tipo float).
    * 
    * Si se leen correctamente ambos valores (nombre y costo), 'fscanf' devuelve 2. Si no se puede leer correctamente 
    * (por ejemplo, si llega al final del archivo o si los datos no tienen el formato esperado), el ciclo termina.
    */
    while (fscanf(f, "%s %f", nombre, &costo) == 2) { // mientras se puedan leer dos elementos
        Producto* nuevo = (Producto*)malloc(sizeof(Producto)); // creamos un puntero llamado nuevo que almacena
        // la direccion de memoria de un objeto de tipo Producto, luego le asignamos memoria mediante malloc 
        /* 
 * Asignamos memoria dinámica para un nuevo nodo de tipo Producto.
 * 
 * - malloc(sizeof(Producto)) indica la cantidad de memoria para almacenar un objeto de tipo Producto.
 *   El tamaño de la memoria es en funcion der la cantidad de bytes que ocupa la estructura Producto.
 * - malloc devuelve un puntero genérico de tipo void* (puntero a cualquier tipo de dato). 
 *   Usamos (Producto*) para convertir el puntero genérico a un puntero específico de tipo Producto*.
 *
 * - Producto* nuevo: Declara un puntero a Producto llamado 'nuevo', que almacenará la dirección de memoria
 *   recién asignada para el nuevo nodo.
 *   
 * Esto es necesario porque estamos trabajando con una lista enlazada y necesitamos almacenar
 * dinámicamente los nodos (productos) que se irán agregando a la lista.
 */

        if (nuevo == NULL) { // si no se pudo asignar memoria, se indica el error.
            printf("Error de memoria.\n");
            fclose(f); // fclose cierra el archivo abierto
            return NULL; // retorna NULL para indicar que no se pudo cargar la lista
        }

        strcpy(nuevo->nombre, nombre);  // copaimos el nombre del producto (de la variable temporal nombre) a la estructura Producto
        nuevo->costo = costo; // asignamos el costo del producto (de la variable temporal costo) a la estructura Producto
        nuevo->siguiente = NULL; // inicializamos el puntero siguiente en NULL porque no sabemos si esta vacia.

        /*
        PAra enlazar el nuevo nodo a la lista:
        */
        if (head == NULL) { // si la lista esta vacia:
            head = nuevo; // la cabeza de la lista apunta al nuevo nodo
            tail = nuevo; // la cola de la lista apunta al nuevo nodo -> ya que es el unico nodo
        } else { // si  no esta vacia:
            tail->siguiente = nuevo; // la cola de la lista apunta al nuevo nodo (ya hay mas de un nodo)
            tail = nuevo; // la cola de la lista se actualiza para que apunte al nuevo nodo
        }
    } // cuando no se puedan leer dos elementos, el ciclo termina

    fclose(f); // cerramos el archivo abierto
    return head; // regresamos la cabeza de la lista (el primer nodo).
}



// 2.- Mostrar un producto
void mostrarProductoActual(Producto* actual) {
    // Verificamos que  el apuntador actual no sea NULL
    if (actual != NULL) {
        // Mostrar el nombre del producto
        printf("Producto: %s\n", actual->nombre);
        
        // Mostrar el costo del producto
        printf("Costo: $%.2f\n", actual->costo);
    } else {
        // Si el puntero es NULL, mostrar un mensaje de error
        printf("Error: El producto es NULL.\n");
    }
}


// 3.- Avanzar al siguiente producto
Producto* avanzarProducto(Producto* actual) {
    if (actual == NULL || actual->siguiente == NULL) { // si la lista esta vacia  o si no esta vacía
                                                       // pero el  el apuntador sigiente apunta a NULL.
        printf("No hay más productos.\n"); // le indicamos al usuairio que ya no hay mas productos.
        return NULL;  // No hay más productos
    } // si NO esta vacía:
    return actual->siguiente;  /*
                              * regresa el apuntador que ahora apunta al siguiente producto
                              * actual->siguiente obtiene el valor de siguiente, que es el apuntador al siguiente nodo en la lista.
                              * Entonces, return actual->siguiente devuelve la dirección de memoria del siguiente nodo
                              */
}


// 4.- Retroceder al producto anterior.
Producto* retrocederProducto(Producto* cabeza, Producto* actual) {
    if (actual == cabeza || actual == NULL) { /* si estamos en el primer nodo de la lista enlazada
                                              * o si la lista esta vacía
                                             */ 
        printf("No hay producto anterior.\n"); // indicamos al usuario que no hay producto anterior.
        return NULL;  // No hay producto anterior
    }
    // Si no estamos al inicio de la lista y la lista no está vacía, procedemos a encontrar el nodo anterior.
    Producto* temp = cabeza; // Asignamos la dirección de 'cabeza' a 'temp', el cual recorrerá la lista
    // Mientras 'temp' no sea NULL y 'temp->siguiente' no sea igual a 'actual',
    // avanzamos al siguiente nodo en la lista.
    while (temp != NULL && temp->siguiente != actual) { 
        temp = temp->siguiente;  // Avanzamos al siguiente nodo de la lista
    }

    return temp;  // Devolvemos el nodo anterior al producto actual
}






