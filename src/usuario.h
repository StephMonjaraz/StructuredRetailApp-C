#ifndef USUARIO_H
#define USUARIO_H

#include "producto.h"  // apuntador a Producto

typedef struct Usuario {
    char nombre[100];
    char numeroCelular[10];  
    float totalPagar;
    Producto* carrito;       // apuntador al inicio del carrito de compras (lista ligada)
} Usuario;

// Declaraciones de funciones
void mostrarUsuario(const Usuario* usuario);

#endif