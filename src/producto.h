#ifndef PRODUCTO_H
#define PRODUCTO_H

typedef struct Producto {
    char nombre[100];
    float costo;
    struct Producto* siguiente;
} Producto;

Producto* cargarProductosDesdeArchivo(const char* nombreArchivo);

void mostrarListaProductos(Producto* lista);

#endif
