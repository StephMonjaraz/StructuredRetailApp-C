#ifndef PRODUCTO_H
#define PRODUCTO_H

typedef struct Producto {
    char nombre[100]; // Nombre del producto
    float costo;  // Precio del producto
    char descripcion[200];  // Descripción breve del producto
    int cantidad;  // Cantidad disponible en el inventario
    char categoria[50]; // Categoría del producto (ej. "Computadora")
    char marca[50]; // Marca del producto (ej. "Apple")
    float voltaje;  // Voltaje del producto (si aplica, ej. "220V")
    char caracteristicas[200]; // Características adicionales del producto
    struct Producto* siguiente; // Apuntador al siguiente producto
} Producto;

// Funciones declaradas


// Tipo de retorno -> Producto* (apuntador a la estructura Producto)
// nombre de la funcion -> cargarProductosDesdeArchivo
/*argumentos (lo que recibiremos en la funcion) -> const char* nombreArchivo -> const ya que solo lee el nombre del archivo
* y no lo modifica.
* recibiremos un apuntador a un char (una cadena de caracteres) que 
* es el nombre del archivo.  Lo llamamos productos.txt y esta en la carpeta data
*/
// 1.- Acceder al archivo y cargar los productos
Producto* cargarProductosDesdeArchivo(const char* nombreArchivo);


/*
* 2.- Mostrar un producto
* La función no devuelve ningún valor, ya que su único propósito es mostrar los datos del producto en pantalla.
* Como argumento, recibirá un parámetro "actual" que es un apuntador a la estructura Producto,
* el cual representa el producto que queremos mostrar.
*/
void mostrarProductoActual(Producto* actual);



/*
* 3.- avanza al siguiente producto -> Devuelve el siguiente producto de la lista. 
* La función a la que llamamos avanzarProducto devolverá el apuntador a la estructura producto 
* y tiene como parámetros "actual" que es un apuntador a la esctructura Producto.
*/
Producto* avanzarProducto(Producto* actual);



/*
* 4.- Busca el producto anterior recorriendo la lista desde la cabeza hasta el producto anterior al nodo actual.
* La función retrocederProducto devuelve un apuntador al producto anterior al nodo actual.
* Recibe como parámetros "cabeza" (el primer nodo de la lista) y "actual" (el nodo del cual queremos encontrar el anterior).
*/
Producto* retrocederProducto(Producto* cabeza, Producto* actual);

/*
* 5.- Crear una copia del producto actual para agregar al carrito
* La funcion a la que llamamos copiarProducto devuelve un apuntador a la estructura Producto
* y tiene como parámetros "original" que es un apuntador a la estructura Producto.
*/

Producto* copiarProducto(Producto* original);


void mostrarMenuNavegacionProductos();

#endif
