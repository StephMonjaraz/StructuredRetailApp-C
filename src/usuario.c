#include <stdio.h>
#include "usuario.h"
#include "carrito.h"  
#include "estilos.h"

void mostrarUsuario(const Usuario* usuario) {
    


printf("%s\n\n", DARK_NEON_YELLOW);
printf("                             ██████   ██  ███████ ███    ██ ██    ██  ██████  ███    ██  ██  ██████  ██████\n");
printf("                             ██   ██  ██  ██      ████   ██ ██    ██  ██      ████   ██  ██  ██   █  ██   ██\n");
printf("                             ██████   ██  █████   ██ ██  ██ ██    ██  ████    ██  ██ ██  ██  ██   █  ██   ██\n");
printf("                             ██   ██  ██  ██      ██  ██ ██  ██  ██   ██      ██  ██ ██  ██  ██   █  ██   ██\n");
printf("                             ██████   ██  █████   ██   ██     ███     █████   ██   ██    ██  ██████  ██████  \n");



    printf("\n\n               === INFORMACIÓN DEL USUARIO ===\n");
    printf("               Nombre: %s\n", usuario->nombre);
    printf("               Número de celular: %s\n", usuario->numeroCelular);
    printf("               Total a pagar: $%.2f\n", usuario->totalPagar);

    if (usuario->carrito == NULL) {
        printf("\n          Carrito vacío. ¡Agrega productos desde el menú principal!\n");
    } else {
        printf("\n          Productos en el carrito:\n");

        Carrito* actual = usuario->carrito;
        int index = 1;
        while (actual != NULL) {
            printf("          %d. %s (Cantidad: %d, Precio: $%.2f)\n", index,
                   actual->producto.nombre,
                   actual->cantidad,
                   actual->producto.costo);
            actual = actual->siguiente;
            index++;
        }
    }
}
