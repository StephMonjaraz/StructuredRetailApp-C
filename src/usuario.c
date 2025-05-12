#include <stdio.h>
#include "usuario.h"

void mostrarUsuario(const Usuario* usuario) {
    printf("\n=== INFORMACIÓN DEL USUARIO ===\n");
    printf("Nombre: %s\n", usuario->nombre);
    printf("Número de celular: %s\n", usuario->numeroCelular);
    printf("Total a pagar: $%.2f\n", usuario->totalPagar);

    // Verificar si el carrito está vacío
    if (usuario->carrito == NULL) {
        printf("\nCarrito vacío. ¡Agrega productos desde el menú principal!\n");
    }
}