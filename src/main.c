#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "producto.h"
#include "usuario.h"
#include "carrito.h"
#include "estilos.h"

// Función del menú principal
void mostrarMenu() {

    printf("\n\n\n%s                          ██ %s ██%s  ██  %s██%s  ██%s  ██",DN,R,PY,DN,R,PY);
    printf("%s  ██ %s ██%s  ██  %s██%s  ██%s  ██",DN,R,PY,DN,R,PY);
    printf("%s  ██ %s ██%s  ██  %s██%s  ██%s  ██",DN,R,PY,DN,R,PY);
    printf("%s  ██ %s ██%s  ██  %s██%s  ██%s  ██\n\n",DN,R,PY,DN,R,PY);
    printf("%s                                     _____                ____       ___   ___    ____   ___                                      \n",DARK_NEON_RED);
    printf("%s                                    ||   |  ||___||  ||  ||  ||     ||  |_|  ||  ||___  ||  |   ||   ||   ||                        \n",DARK_NEON_RED);
    printf("%s                                    ||      ||   ||  ||  ||__||  *  ||       ||  ||     ||   |  ||   ||   ||                         \n",DARK_NEON_RED);
    printf("%s                                    ||___|  ||   ||  ||  ||         ||       ||  ||___  ||    |_||   ||___||                             \n",DARK_NEON_RED);
    
    // le damos estilo al menu de la tienda
    printf(DN" \n\n\n     -- 1. Navegar por la lista de productos\n" RESET);
    
    printf(DN" \n     -- 2. Ver información del usuario\n" );
    printf(DN" \n     -- 3. Ver carrito de compras\n");
    printf(DN" \n     -- 4. Eliminar producto del carrito\n");
    printf(DN" \n     -- 5. Salir\n");
    printf(DN" \n     -- Elige una opción: ");
}

int main() {

    printf("\033[H\033[J");

    simulacionCargaBienvenida();
    usleep(3000000); // 3 segundos de carga
    printf("\033[H\033[J"); //limpiamos la pantalla
   
    //crear un usuario vacío
    Usuario usuario1 = {
        .nombre = "Juan Pérez",
        .numeroCelular = "5512345678",
        .totalPagar = 0.0f,
        .carrito = NULL  // carrito vacío inicialmente
    };

    // Cargamos los productos desde el archivo
    Producto* listaProductos = cargarProductosDesdeArchivo("../data/productos.txt");
    if (listaProductos == NULL) {
        printf("No se pudieron cargar los productos.\n");
        return 1;
    }

    Producto* actual = listaProductos; //inicializamos 'actual' como el primer producto de la lista
    int opcion;
    int seguir = 1;
    char buffer[16];

    while (seguir) { //mientras el usuario no quiera salir se mantiene en el menu
        printf("\033[H\033[J"); // LIMPIA LA PANTALLA ANTES DE MOSTRAR EL MENÚ PRINCIPAL
        mostrarMenu();

        if (!fgets(buffer, sizeof(buffer), stdin)) { //si fgets no puede leer la entrada
            printf("Error al leer la entrada.\n"); // le indicamos al usuario que hubo un error
            continue;
        }
        if (sscanf(buffer, "%d", &opcion) != 1) { // si el usuario ingresa un valor que no es valido
            printf("  Opción no válida. Por favor ingresa un número del 1 al 5.\n"); //le indicamos que solo puede elegir entre 1-5
            continue;
        }

        switch (opcion) { // switch para controlar las opciones del menú
                        case 1: { // corresponde a navegar por la lista de productos
                printf("\033[H\033[J"); // LIMPIA LA PANTALLA ANTES DE ENTRAR AL MENÚ DE PRODUCTOS
                char opcionNavegacion;
                int salirNavegacion = 0;
                do { //mientras el usuario no quiera salir del menú de navegación, le recordamos las opciones de navegación
                    // Limpiamos solo la parte inferior, no toda la pantalla, para mantener el menú visible
                    printf("\033[H\033[J"); // LIMPIA LA PANTALLA DEL SUBMENÚ SOLO UNA VEZ POR VUELTA
                    mostrarMenuNavegacionProductos();
                    mostrarProductoActual(actual);

                    printf("\n    Seleccione una opción (S, A, C, Q): ");
                    scanf(" %c", &opcionNavegacion);
                    while (getchar() != '\n'); 

                    switch (opcionNavegacion) { // otro switch para controlar las opciones de navegación
                        case 'S':
                        case 's':
                            if (actual->siguiente != NULL) { // si hay un siguiente producto
                                actual = avanzarProducto(actual);
                            } else { //si no hay siguiente producto
                                printf("   No hay más productos. Estás en el último producto.\n");
                                usleep(1200000);
                            }
                            break;

                        case 'A':
                        case 'a':
                            if (actual != listaProductos) { //si no estamos en el primer producto
                                actual = retrocederProducto(listaProductos, actual);
                            } else { //si estamos en el primer producto
                                printf("   No hay producto anterior. Estás en el primer producto.\n");
                                usleep(1200000);// espera 1.2 segundos para que el usuario pueda ver el mensaje
                            }
                            break;

                        case 'C':
                        case 'c': {
                            int cantidad;
                            printf("   ¿Cuántos de este producto deseas agregar al carrito? ");
                            if (scanf("%d", &cantidad) != 1 || cantidad < 0) { //si la entrada no es un número entero positivo
                                printf("   Cantidad inválida. Por favor ingresa un número entero positivo.\n"); //indicamos al usuario que hubo un error
                                while (getchar() != '\n'); // Limpiar el buffer de entrada
                            } else if (cantidad == 0) {// si la cantidad es 0
                                printf("   No se agregó el producto al carrito.\n");//simplemente no agregamos nada
                            } else { // si la cantidad es válida, creamos una copia del producto y lo agregamos al carrito
                                Producto* productoCopia = copiarProducto(actual);
                                productoCopia->cantidad = cantidad; // Asignar la cantidad deseada
                                agregarProductoAlCarrito(&usuario1, productoCopia);
                                printf("   Se agregaron %d unidades de '%s' al carrito.\n", cantidad, actual->nombre);
                            }
                            break;
                        }

                        case 'Q':
                        case 'q':
                            printf("   Saliendo de la navegación de productos...\n");
                            salirNavegacion = 1;
                            break;

                        default:
                            printf("   Opción no válida. Por favor ingrese S, A, C o Q.\n");
                            break;
                    }
                    // Aquí NO limpias la pantalla, así el menú y el producto actual siempre quedan arriba,
                    // solo se actualiza la información y mensajes debajo del menú.
                } while (!salirNavegacion);
                break;
            }
            

            case 2: {//mostramos la información del usuario
                printf("\033[H\033[J"); // LIMPIA LA PANTALLA ANTES DE MOSTRAR USUARIO
                mostrarUsuario(&usuario1);
                printf("\n   Presiona ENTER para continuar...");
                while (getchar() != '\n');
                break;
            }

            case 3: {//para poder ver el carrito de compras
                printf("\033[H\033[J"); // LIMPIA LA PANTALLA ANTES DE MOSTRAR CARRITO
                mostrarCarrito(&usuario1);  // Mostrar el carrito y el total
                printf("\n   Presiona ENTER para continuar...");
                while (getchar() != '\n');
                break;
            }

            case 4: {
                printf("\033[H\033[J"); // LIMPIA LA PANTALLA ANTES DE ENTRAR AL SUBMENÚ DE ELIMINAR PRODUCTO
                int salirEliminar = 0;
                char opcionEliminar[16];
                do {
                    mostrarCarrito(&usuario1);
                    if (usuario1.carrito == NULL) {
                        printf("\n   El carrito está vacío. Presiona ENTER para regresar al menú principal...");
                        while (getchar() != '\n');
                        break;
                    }
                    printf("\n   Escribe el número del producto a eliminar o escribe 'salir' para regresar al menú principal: ");
                    if (!fgets(opcionEliminar, sizeof(opcionEliminar), stdin)) {
                        printf("   Error al leer la entrada.\n");
                        continue;
                    }
                    // Elimina salto de línea
                    opcionEliminar[strcspn(opcionEliminar, "\n")] = 0;

                    if (strcmp(opcionEliminar, "salir") == 0 || strcmp(opcionEliminar, "SALIR") == 0) {
                        salirEliminar = 1;
                    } else {
                        int num;
                        if (sscanf(opcionEliminar, "%d", &num) == 1) {
                            eliminarProductoDelCarritoPorNumero(&usuario1, num);
                        } else {
                            printf("   Entrada no válida. Ingresa un número o 'salir'.\n");
                            printf("\n   Presiona ENTER para continuar...");
                            while (getchar() != '\n');
                        }
                    }
                    printf("\033[H\033[J"); // LIMPIA LA PANTALLA PARA QUE EL SUBMENÚ SE MANTENGA LIMPIO
                } while (!salirEliminar);
                break;
            }

            case 5: {
                printf("\033[H\033[J");
                // Salir
                seguir = 0;
                printf("   Saliendo del programa...\n");
                break;
            }

            default:
                printf("   Opción no válida. Intenta de nuevo.\n");
                break;
        }
    }

    // liberamos memoria de la lista de productos
    Producto* temp;
    while (listaProductos != NULL) {
        temp = listaProductos;
        listaProductos = listaProductos->siguiente;
        free(temp);
    }

    // Liberamos la memoria del carrito
    Carrito* tempCarrito;
    while (usuario1.carrito != NULL) {
        tempCarrito = usuario1.carrito;
        usuario1.carrito = usuario1.carrito->siguiente;
        free(tempCarrito);
    }

    return 0;
}