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
    // Crear un usuario vacío
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
    Producto* actual = listaProductos;  // Empezamos desde el primer producto
    int seguir = 1;
    int primeraEjecucion = 1;  // Bandera para mostrar el primer producto al inicio

    while (seguir) {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: {
                // Mostrar lista de productos
                printf("\n=== LISTA DE PRODUCTOS ===\n");

                // Si es la primera ejecución, mostramos el primer producto
                if (primeraEjecucion) {
                    mostrarProductoActual(actual);
                    primeraEjecucion = 0; // Desactivamos la bandera
                }

                // Navegación interactiva
                printf("\nSeleccione una opción para navegar por la lista de productos:\n");
                printf("S - Avanzar al siguiente producto\n");
                printf("A - Retroceder al producto anterior\n");
                printf("Q - Salir del programa\n");
                printf("Ingrese su opción (S, A, Q): ");

                char opcionNav;
                scanf(" %c", &opcionNav);  // Leemos la opción del usuario

                switch (opcionNav) {
                    case 'S':  // Avanzar al siguiente producto
                    case 's':
                        actual = avanzarProducto(actual);  // Avanzamos al siguiente nodo
                        if (actual != NULL) {
                            mostrarProductoActual(actual);  // Muestra el siguiente nodo
                        }
                        break;

                    case 'A':  // Retroceder al producto anterior
                    case 'a':
                        actual = retrocederProducto(listaProductos, actual);  // Retrocedemos al anterior
                        if (actual != NULL) {
                            mostrarProductoActual(actual);  // Mostramos el producto anterior
                        }
                        break;

                    case 'Q':  // Salir
                    case 'q':
                        seguir = 0;  // Salimos del programa
                        printf("Saliendo del programa...\n");
                        break;

                    default:
                        printf("Opción no válida. Por favor ingrese S, A o Q.\n");
                        break;
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
                mostrarCarrito(&usuario1);  // Mostrar el carrito y el total
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

    // Liberar memoria de los productos
    Producto* temp;
    while (listaProductos != NULL) {
        temp = listaProductos;
        listaProductos = listaProductos->siguiente;
        free(temp);
    }

    return 0;
}

