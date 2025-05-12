#ifndef CARRITO_H
#define CARRITO_H

#include "producto.h"  // Necesario para la estructura Producto
#include "usuario.h"    // necesario para la estructura USuario

// Función para mostrar el carrito de compras
void mostrarCarrito(const Usuario* usuario);

// Función para calcular el total a pagar
void actualizarTotal(Usuario* usuario);

// Función para liberar la memoria del carrito
void liberarCarrito(Usuario* usuario);

#endif