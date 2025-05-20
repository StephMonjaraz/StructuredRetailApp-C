#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carrito.h"
#include "producto.h"
#include "usuario.h"
#include "estilos.h"

// Muestra los productos en el carrito
void mostrarCarrito(const Usuario* usuario) {
    printf("\n\n\n%s                          ██  ██  ██  ██  ██  ██",DARK_NEON_YELLOW);
    printf("%s  ██  ██  ██  ██  ██  ██",DARK_NEON_YELLOW);
    printf("%s  ██  ██  ██  ██  ██  ██",DARK_NEON_YELLOW);
    printf("%s  ██  ██  ██  ██  ██  ██\n\n",DARK_NEON_YELLOW);

    printf("%s                                          _____   _____   ____   ____  ____   _____    ___                \n",CB2);
    printf("%s                                         ||   |  ||  ||  ||__|  ||__|   ||     ||    ||  ||                          \n",CB2);
    printf("%s                                         ||      ||__||  ||  |  ||  |   ||     ||    ||  ||                              \n",CB2);
    printf("%s                                         ||___|  ||  ||  ||  |  ||  |  _||_    ||    ||__||                                \n\n\n",CB2);
     

    if (usuario->carrito == NULL) {
        printf("\n     El carrito está vacío.\n");
        return;
    }

    Carrito* actual = usuario->carrito;
    float total = 0.0f;
    int index = 1;

    while (actual != NULL) {
        printf("     %d. Producto: %s\n", index, actual->producto.nombre);
        printf("     Precio unitario: $%.2f\n", actual->producto.costo);
        printf("     Cantidad: %d\n", actual->cantidad);
        printf("        Subtotal: $%.2f\n", actual->producto.costo * actual->cantidad);
        printf("     ________________________________________\n");

        total += actual->producto.costo * actual->cantidad;
        actual = actual->siguiente;
        index++;
    }

    printf("     Total a pagar: $%.2f\n", total);
}


// Calcula el total a pagar
void actualizarTotal(Usuario* usuario) {
    float total = 0.0f;
    Carrito* actual = usuario->carrito;

    while (actual != NULL) {
        total += actual->producto.costo * actual->cantidad;
        actual = actual->siguiente;
    }

    usuario->totalPagar = total;
}

// Agrega un producto al carrito
void agregarProductoAlCarrito(Usuario* usuario, Producto* producto) {
    // Buscar si el producto ya está en el carrito
    Carrito* temp = usuario->carrito;
    while (temp != NULL) {
        if (strcmp(temp->producto.nombre, producto->nombre) == 0) {
            // Si ya existe, solo suma la cantidad
            temp->cantidad += producto->cantidad;
            actualizarTotal(usuario);
            return;
        }
        temp = temp->siguiente;
    }

    // Si no existe, agregarlo como nuevo nodo
    Carrito* nuevo = (Carrito*)malloc(sizeof(Carrito));
    if (nuevo == NULL) {
        printf("     Error de memoria al agregar el producto al carrito.\n");
        return;
    }

    nuevo->producto = *producto;  // copia todos los campos
    nuevo->cantidad = producto->cantidad;  // cantidad deseada
    nuevo->siguiente = NULL;

    if (usuario->carrito == NULL) {
        usuario->carrito = nuevo;
    } else {
        temp = usuario->carrito;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }

    actualizarTotal(usuario);
}


// Elimina un producto del carrito por número (para submenú interactivo)
void eliminarProductoDelCarritoPorNumero(Usuario* usuario, int numero) {
    if (usuario->carrito == NULL) {
        printf("     El carrito está vacío. No hay productos para eliminar.\n");
        return;
    }
    Carrito* actual = usuario->carrito;
    Carrito* anterior = NULL;
    int contador = 1;
    while (actual != NULL) {
        if (contador == numero) {
            if (anterior == NULL) {
                usuario->carrito = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            printf("     Producto '%s' eliminado del carrito.\n", actual->producto.nombre);
            free(actual);
            actualizarTotal(usuario);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
        contador++;
    }
    printf("     No existe un producto con ese número en el carrito.\n");
}

// Elimina un producto del carrito (versión original, para compatibilidad)
void eliminarProductoDelCarrito(Usuario* usuario) {
    if (usuario->carrito == NULL) {
        printf("     El carrito está vacío. No hay productos para eliminar.\n");
        return;
    }

    printf("\n     Productos en tu carrito:\n");
    Carrito* temp = usuario->carrito;
    int index = 1;

    while (temp != NULL) {
        printf("     %d. %s (Cantidad: %d, Precio: $%.2f)\n",
               index, temp->producto.nombre, temp->cantidad, temp->producto.costo);
        temp = temp->siguiente;
        index++;
    }

    int opcion;
    printf("     Selecciona el número del producto que deseas eliminar: ");
    if (scanf("     %d", &opcion) != 1 || opcion <= 0 || opcion >= index) {
        printf("     Opción no válida.\n");
        while (getchar() != '\n');
        return;
    }

    Carrito* actual = usuario->carrito;
    Carrito* anterior = NULL;
    int contador = 1;

    while (actual != NULL) {
        if (contador == opcion) {
            if (anterior == NULL) {
                usuario->carrito = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            printf("     Producto '%s' eliminado del carrito.\n", actual->producto.nombre);
            free(actual);
            actualizarTotal(usuario);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
        contador++;
    }
}