# 🛒 BYTE & CHIPS — Tiendita Electrónica Retro (Proyecto Final en C)

Simulación de una tienda interactiva retro de productos electrónicos, implementada en **lenguaje C**   
(Mayo 2025).

## 👥 Autores

- Jessica Stephanie García Monjaraz  
- Eduardo Yael Jiménez Sánchez  

## 📌 Descripción del Proyecto

BYTE & CHIPS es una aplicación en consola que simula una tienda de productos electrónicos retro. El usuario puede navegar por productos, agregarlos a su carrito, ver su información personal y modificar sus compras. Este sistema se desarrolló para aplicar conceptos fundamentales de la programación estructurada como:

- Estructuras y listas ligadas
- Manejo de memoria dinámica
- Lectura desde archivos `.txt`
- Modularidad y documentación del código
- Estilos visuales en consola (ANSI)


## 🧪 Funcionalidades principales

### 👤 Usuario
- Ver información personal
- Consultar total acumulado
- Visualizar carrito

### 🛍️ Productos
- Cargar desde archivo (`productos.txt`)
- Mostrar datos completos
- Navegación interactiva (avanzar, retroceder)
- Copiar productos para agregar al carrito

### 🧺 Carrito
- Agregar productos con cantidad
- Eliminar productos seleccionados
- Calcular total a pagar
- Mostrar productos con subtotales

## 🖥️ Ejecución

Puedes compilar el programa con:

```bash
gcc -o tiendita src/main.c src/producto.c src/usuario.c src/carrito.c src/utils.c -I. && ./tiendita
```

## 🚧 En Desarrollo Activo

**BYTE & CHIPS** sigue creciendo. Aunque fue concebido como un proyecto académico, planeamos seguir mejorándolo con nuevas funcionalidades como:

- Guardado y carga del carrito
- Interfaz gráfica (GTK o ncurses)
- Autenticación de usuarios
- Sistema de historial de compras

💙 **Aceptamos sugerencias, ideas y mejoras.**  
Si tienes propuestas, ¡no dudes en abrir un *issue* o contactarnos!




