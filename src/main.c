#include <stdio.h>
#include "usuario.h"

int main() {
    Usuario usuario1 = {
        .nombre = "Juan Pérez",
        .numeroCelular = "5512345678",
        .totalPagar = 0.0f,
        .carrito = NULL  // carrito vacío inicialmente
    };

    // mostrar información del usuario
    mostrarUsuario(&usuario1);

    return 0;
}