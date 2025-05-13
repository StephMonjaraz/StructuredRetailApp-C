#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include "producto.h"
#include "carrito.h"

void mostrarMenu() {
    printf("\n=== MENÚ PRINCIPAL ===\n");
    printf("1. Ver lista de productos\n");
    printf("2. Ver información del usuario\n");
    printf("3. Ver carrito de compras\n");
    printf("4. Salir\n");
    printf("Elige una opción: ");
}

int main() {
    Usuario usuario1 = {
        .nombre = "Juan Pérez",
        .numeroCelular = "5512345678",
        .totalPagar = 0.0f,
        .carrito = NULL  // carrito vacío inicialmente
    };

    // Cargar productos desde archivo
    Producto* listaProductos = cargarProductosDesdeArchivo("../data/productos.txt");
    if (listaProductos == NULL) {
        printf("No se cargaron productos.\n");
        return 1;
    }

    int opcion;
    int seguir = 1;
    while (seguir) {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: {
                // Mostrar lista de productos
                printf("\n=== LISTA DE PRODUCTOS ===\n");
                mostrarListaProductos(listaProductos);
                printf("\nSelecciona un producto para agregarlo al carrito (1 para agregar, 0 para cancelar): ");
                int agregar;
                scanf("%d", &agregar);
                if (agregar == 1) {
                    // Aquí el código para agregar el primer producto al carrito
                    if (listaProductos != NULL) {
                        agregarProductoAlCarrito(&usuario1, listaProductos);
                        printf("Producto agregado al carrito.\n");
                    }
                }
                break;
            }
            case 2: {
                // Mostrar información del usuario
                mostrarUsuario(&usuario1);
                break;
            }
            case 3: {
                // Mostrar carrito de compras
                mostrarCarrito(&usuario1);
                break;
            }
            case 4: {
                // Salir
                seguir = 0;
                printf("Saliendo del programa...\n");
                break;
            }
            default:
                printf("Opción no válida. Intenta de nuevo.\n");
                break;
        }
    }

    // Liberar memoria
    Producto* temp;
    while (listaProductos != NULL) {
        temp = listaProductos;
        listaProductos = listaProductos->siguiente;
        free(temp);
    }

    return 0;
}
