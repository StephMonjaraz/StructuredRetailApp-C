#ifndef USUARIO_H
#define USUARIO_H

#include "producto.h"  // para el apuntador a Producto

typedef struct Usuario {
    char nombre[100];
    char numeroCelular[10];  
    float totalPagar;
    struct Carrito* carrito;       // ahora es un apuntador a la estructura Carrito
} Usuario;

// Declaraciones de funciones
void mostrarUsuario(const Usuario* usuario);

#endif
