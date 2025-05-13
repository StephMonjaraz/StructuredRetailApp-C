#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    float total = 0.0f;

    while (actual != NULL) {
        printf("Producto: %s\n", actual->nombre);
        printf("Precio unitario: $%.2f\n", actual->costo);
        printf("Cantidad: %d\n", actual->cantidad);
        printf("Subtotal: $%.2f\n", actual->costo * actual->cantidad);
        printf("----------------------\n");

        total += actual->costo * actual->cantidad; // Calcular subtotal por producto
        actual = actual->siguiente;
    }

    printf("Total a pagar: $%.2f\n", total);
}

// Calcula el total a pagar
void actualizarTotal(Usuario* usuario) {
    float total = 0.0f;
    Producto* actual = usuario->carrito;

    while (actual != NULL) {
        total += actual->costo * actual->cantidad; // Multiplicar precio por cantidad
        actual = actual->siguiente;
    }

    usuario->totalPagar = total;
}

// Agregar un producto al carrito
void agregarProductoAlCarrito(Usuario* usuario, Producto* producto) {
    Producto* nuevo = (Producto*)malloc(sizeof(Producto));
    if (nuevo == NULL) {
        printf("Error de memoria al agregar el producto al carrito.\n");
        return;
    }

    // Copiar los datos del producto al nuevo nodo
    strcpy(nuevo->nombre, producto->nombre);
    nuevo->costo = producto->costo;
    nuevo->cantidad = producto->cantidad; // Copiar la cantidad seleccionada
    strcpy(nuevo->categoria, producto->categoria);
    strcpy(nuevo->marca, producto->marca);
    nuevo->voltaje = producto->voltaje;
    strcpy(nuevo->descripcion, producto->descripcion);
    strcpy(nuevo->caracteristicas, producto->caracteristicas);
    nuevo->siguiente = NULL;

    // Agregar el producto al carrito del usuario
    if (usuario->carrito == NULL) {
        usuario->carrito = nuevo;
    } else {
        Producto* temp = usuario->carrito;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }

    // Actualizar el total
    actualizarTotal(usuario);
}