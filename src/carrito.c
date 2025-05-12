#include <stdio.h>
#include <stdlib.h>
#include "carrito.h"
#include "producto.h"
#include "usuario.h"

// Muestra los productos en el carrito
void mostrarCarrito(const Usuario* usuario) {
    printf("\n=== CARRITO DE COMPRAS ===\n");

    if (usuario->carrito == NULL) {
        printf("El carrito está vacío.\n");
        return;
    }

    Producto* actual = usuario->carrito;
    while (actual != NULL) {
        printf("Producto: %s - Precio: $%.2f\n", actual->nombre, actual->costo);
        actual = actual->siguiente;
    }
    printf("Total a pagar: $%.2f\n", usuario->totalPagar);
}

// Calcula el total a pagar
void actualizarTotal(Usuario* usuario) {
    float total = 0.0f;
    Producto* actual = usuario->carrito;

    while (actual != NULL) {
        total += actual->costo;
        actual = actual->siguiente;
    }

    usuario->totalPagar = total;
}