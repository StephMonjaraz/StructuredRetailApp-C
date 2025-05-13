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

    //bandera para controlar si es la primera ejecución
    int primeraEjecucion = 1;

    

    // 4.- Navegación interactiva: S se suará para avanzar, A para retroceder, Q para salir
    char opcion;
    do {

        // Si es la primera ejecución, mostramos el producto inicial
        if (primeraEjecucion) {
            printf("Producto actual:\n");
            mostrarProductoActual(actual);
            primeraEjecucion = 0; // Desactivamos la bandera
        }
        
        // Instrucciones al usuario
        printf("\nSeleccione una opción para navegar por la lista de productos:\n");
        printf("S - Avanzar al siguiente producto\n");
        printf("A - Retroceder al producto anterior\n");
        printf("Q - Salir del programa\n");
        printf("Ingrese su opción (S, A, Q): ");

        scanf(" %c", &opcion);  //leemos la opción del usuario

        switch (opcion) {
            case 'S':  // nos aseguramos que pueda ingresa tanto S ocmo s
            case 's':
                actual = avanzarProducto(actual);  // Avanzamos al siguiente nodo
                if (actual != NULL) {
                    mostrarProductoActual(actual);  // Muestra el siguiente nodo
                }
                break;

            case 'A':  // Retrocede al producto anterior
            case 'a':
                actual = retrocederProducto(lista, actual);  // Retrocedemos al anterior
                if (actual != NULL) {
                    mostrarProductoActual(actual);  // Mostramos el productos anterior
                }
                break;

            case 'Q':  //alimos de la lista
            case 'q':
                printf("Saliendo de la lista...\n");
                break;

            default: // cualquier cosa que no sea a, s o q (A, S o Q) le indicamos al usuario que no es valido.
                printf("Opción no válida. Por favor ingrese S, A o Q.\n");
                break;
        }
    } while (opcion != 'Q' && opcion != 'q');  // Continuamos hasta que se seleccione Q

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

    Producto* head = NULL; // apuntador a la cabeza de la lista, lo inicializamos en NULL porque pensamos que la lista esta vacia
    Producto* tail = NULL; // apuntador a la cola de la lista, lo inicializamos en NULL
    // variables temporales para almacenar los datos que leemos  del archivo
    char nombre[100]; 
    float costo;

    /* para leer el archivo linea por linea -> fscanf
    * int fscanf(FILE *stream, const char *format, ...);
    * stream -> apuntador al archivo que queremos leer -> f
    * format -> cadena de formato que indica el tipo de datos que queremos leer
    * La función 'fscanf' devuelve el número de elementos correctamente leídos. En este caso, esperamos que lea dos elementos:
    * 1. El nombre del producto (la cade de caracteres).
    * 2. El costo del producto (el número de tipo float).
    * 
    * Si se leen correctamente ambos valores (nombre y costo), 'fscanf' devuelve 2. Si no se puede leer correctamente 
    * (por ejemplo, si llega al final del archivo o si los datos no tienen el formato esperado), el ciclo termina.
    */
    while (fscanf(f, "%s %f", nombre, &costo) == 2) { // mientras se puedan leer dos elementos
        Producto* nuevo = (Producto*)malloc(sizeof(Producto)); // creamos un apuntador llamado nuevo que almacena
        // la direccion de memoria de un objeto de tipo Producto, luego le asignamos memoria mediante malloc 
        /* 
 * Asignamos memoria dinámica para un nuevo nodo de tipo Producto.
 * 
 * - malloc(sizeof(Producto)) indica la cantidad de memoria para almacenar un objeto de tipo Producto.
 *   El tamaño de la memoria es en funcion der la cantidad de bytes que ocupa la estructura Producto.
 * - malloc devuelve un apuntador genérico de tipo void* (apuntador a cualquier tipo de dato). 
 *   Usamos (Producto*) para convertir el apuntador genérico a un apuntador específico de tipo Producto*.
 *
 * - Producto* nuevo: Declara un apuntador a Producto llamado 'nuevo', que almacenará la dirección de memoria
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
        nuevo->siguiente = NULL; // inicializamos el apuntador siguiente en NULL porque no sabemos si esta vacia.

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
    if (actual == NULL) {// si la lista esta vacia  
        printf("Error: El producto actual es NULL.\n");
        return actual; // No cambia el apuntador si es NULL
    }
    if (actual->siguiente == NULL) { // Si no esta vacia pero no hay más productos
        printf("No hay más productos.\n");
        return actual; // Mantenemos el apuntador en el último producto
    }
    return actual->siguiente; // Avanzar al siguiente producto
}


// 4.- Retroceder al producto anterior.
Producto* retrocederProducto(Producto* cabeza, Producto* actual) {
    if (actual == NULL) { // si la lista esta vacia
        printf("Error: El producto actual es NULL.\n");
        return actual; // No cambiamos el apuntador si es NULL
    }
    if (actual == cabeza) { //si estamos en el primer producto
        printf("No hay producto anterior.\n");
        return actual; // Mantenemos el apuntador en el primer producto
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


// 5.- Copiar el producto actual para agregar al carrito
Producto* copiarProducto(Producto* original) {
    // Verificamos si el producto original es válido
    if (original == NULL) { // si el producto original es NULL
        return NULL;  // Si es NULL, no hay nada que copiar
    }

    // Reservamos memoria para un nuevo nodo de producto mediante malloc
    Producto* nuevo = (Producto*)malloc(sizeof(Producto));
    if (nuevo == NULL) { // si no se pudo reservar memoria
        printf("Error de memoria al copiar el producto.\n");
        return NULL;  //regresamos NULL
    }

    // Copiamos el nombre y costo del producto original
    strcpy(nuevo->nombre, original->nombre);
    nuevo->costo = original->costo;
    nuevo->siguiente = NULL;  // El nuevo producto no tiene siguiente (será el último del carrito)

    return nuevo;
}





