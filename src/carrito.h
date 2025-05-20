#ifndef CARRITO_H
#define CARRITO_H

#include "producto.h"  // Necesario para la estructura Producto

struct Usuario; // Declaración adelantada para usar struct Usuario*

typedef struct Carrito {
    Producto producto;             // El producto agregado al carrito
    int cantidad;                  // Cantidad de ese producto
    struct Carrito* siguiente;     // Apuntador al siguiente nodo
} Carrito;

// Función para mostrar el carrito de compras
void mostrarCarrito(const struct Usuario* usuario);

// Función para calcular el total a pagar
void actualizarTotal(struct Usuario* usuario);

// Función para agregar un producto al carrito
void agregarProductoAlCarrito(struct Usuario* usuario, Producto* producto);

// Función para eliminar un producto del carrito
void eliminarProductoDelCarrito(struct Usuario* usuario);

void eliminarProductoDelCarritoPorNumero(struct Usuario* usuario, int numero);

#endif
