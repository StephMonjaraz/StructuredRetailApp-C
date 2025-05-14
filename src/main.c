#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "producto.h"
#include "usuario.h"
#include "carrito.h"

// Función para mostrar el menú principal
void mostrarMenu() {
    printf("\n=== MENÚ PRINCIPAL ===\n");
    printf("1. Navegar por la lista de productos\n");
    printf("2. Ver información del usuario\n");
    printf("3. Ver carrito de compras\n");
    printf("4. Eliminar producto del carrito\n");
    printf("5. Salir\n");
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

    // Cargar productos desde el archivo
    Producto* listaProductos = cargarProductosDesdeArchivo("../data/productos.txt");
    if (listaProductos == NULL) {
        printf("No se pudieron cargar los productos.\n");
        return 1;
    }

    Producto* actual = listaProductos; // Inicializamos 'actual' como el primer producto de la lista
    int opcion;
    int seguir = 1;

    while (seguir) {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: {
                // Navegación interactiva por la lista de productos
                char opcionNavegacion;
                int primeraEjecucion = 1;
                do {
                    if (primeraEjecucion) {
                        printf("Producto actual:\n");
                        mostrarProductoActual(actual);
                        primeraEjecucion = 0;
                    }

                    printf("\nSeleccione una opción para navegar por la lista de productos:\n");
                    printf("S - Avanzar al siguiente producto\n");
                    printf("A - Retroceder al producto anterior\n");
                    printf("C - Agregar producto al carrito\n");
                    printf("Q - Salir de la navegación\n");
                    printf("Ingrese su opción (S, A, C, Q): ");

                    scanf(" %c", &opcionNavegacion);

                    switch (opcionNavegacion) {
                        case 'S':
                        case 's':
                            if (actual->siguiente != NULL) {
                                actual = avanzarProducto(actual);
                                mostrarProductoActual(actual);
                            } else {
                                printf("No hay más productos. Estás en el último producto.\n");
                            }
                            break;

                        case 'A':
                        case 'a':
                            if (actual != listaProductos) {
                                actual = retrocederProducto(listaProductos, actual);
                                mostrarProductoActual(actual);
                            } else {
                                printf("No hay producto anterior. Estás en el primer producto.\n");
                            }
                            break;

                        case 'C':
                        case 'c': {
                            int cantidad;
                            printf("¿Cuántos de este producto deseas agregar al carrito? ");
                            if (scanf("%d", &cantidad) != 1 || cantidad < 0) {
                                printf("Cantidad inválida. Por favor ingresa un número entero positivo.\n");
                                while (getchar() != '\n'); // Limpiar el buffer de entrada
                            } else if (cantidad == 0) {
                                printf("No se agregó el producto al carrito.\n");
                            } else {
                                Producto* productoCopia = copiarProducto(actual);
                                productoCopia->cantidad = cantidad; // Asignar la cantidad deseada
                                agregarProductoAlCarrito(&usuario1, productoCopia);
                                printf("Se agregaron %d unidades de '%s' al carrito.\n", cantidad, actual->nombre);
                            }
                            break;
                        }

                        case 'Q':
                        case 'q':
                            printf("Saliendo de la navegación de productos...\n");
                            break;

                        default:
                            printf("Opción no válida. Por favor ingrese S, A, C o Q.\n");
                            break;
                    }
                } while (opcionNavegacion != 'Q' && opcionNavegacion != 'q');
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
                eliminarProductoDelCarrito(&usuario1);
                break;
            }

            case 5: {
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

    // Liberar memoria de la lista de productos
    Producto* temp;
    while (listaProductos != NULL) {
        temp = listaProductos;
        listaProductos = listaProductos->siguiente;
        free(temp);
    }

    // Liberar memoria del carrito
    Producto* tempCarrito;
    while (usuario1.carrito != NULL) {
        tempCarrito = usuario1.carrito;
        usuario1.carrito = usuario1.carrito->siguiente;
        free(tempCarrito);
    }

    return 0;
}