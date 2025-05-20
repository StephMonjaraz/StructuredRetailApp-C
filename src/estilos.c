#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // llibreria para poder usar usleep
#include "estilos.h" // Librería personalizada de los estilos para la tienda


void mostrarBienvenida() {
    
    printf("\033[H\033[J");  //limpia la pantalla


    printf(Y"\n       █████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████       ");
    usleep(10000); 
    printf("%s      ██                                                                                                                             %s██       ",Y,Y);
    usleep(10000); 
    printf("%s      ██                                                                                                                             %s██       ",Y,Y);
    usleep(10000); 
  
    

   // * ---------------------- ARCADE CON MARCO ----------------------------*

    printf("%s      ██                         %s███████      ██████        █████      ██████       █████        ██████                              %s██\n",Y,PP,Y);
    usleep(10000);
    printf("%s       ██                        %s███    ██    ███    ██    ██     █    ███    ██    ██    ██     █                                    %s██\n",Y,PP,Y);
    usleep(10000);
    printf("%s       ██                        %s███    ██    ███    ██    ██          ███    ██    ██     ██    ██████%s                               ██\n",Y,PP,Y);
    usleep(11000);
    printf("%s       ██                        %s█████████    ███████      ██          █████████    ██     ██    ██%s                                   ██\n",Y,PP,Y);
    usleep(11000);
    printf("%s       ██                        %s███    ██    ███    █     ██     █    ███    ██    ██    ██     ██%s                                   ██\n",Y,PP,Y);
    usleep(11000);
    printf("%s       ██                        %s███    ██    ███     █      █████     ███    ██     █████       ███████%s                              ██\n",Y,PP,Y);
    usleep(11000);
    printf("%s       ██                                                                                                                             %s██       ",Y,Y);
    usleep(13000);
    printf("%s      ██                                                                                                                             %s██       ",Y,Y);
    usleep(13000);
    printf("%s      ██                                                                                                                             %s██       ",Y,Y);
    usleep(13000);
    
    printf("%s      ██                                                                                                                             %s██       ",Y,Y);
    usleep(13000);
    printf("%s      ██                                                                                                                             %s██       \n",Y,Y);
    



 // * ---------------------- BYTE AND CHIPS ----------------------------*
    usleep(15000);
    printf("%s     ██████      ███    ███    ████████     ██████           █████                ██████     ███    ███    ████████    ████████      ██████ \n",CB2);
    usleep(15000);
    printf("%s    ███    ██    ███    ███    ████████    ███              █     ██            ██      █    ███    ███    ████████    ███    ██    ███   ██ \n",DB);
    usleep(15000);
    printf("%s    ███    ██    ███    ███       ██       ███              █     ██            ██           ███    ███       ██       ███    ██    ███    \n",CB2);
    usleep(16000);
    printf("%s    ███████       ███████         ██       ██████            █████    █         ██           ██████████       ██       ███    ██    ███\n",CB);
    usleep(16000);
    printf("%s    ███    ██       ███           ██       ██               ██    █  █          ██           ███    ███       ██       ███████        ████\n",DB);
    usleep(16000);
    printf("%s    ███    ██       ███           ██       ██               ██     ██           ██      █    ███    ███       ██       ██                 ██\n",CB);
    usleep(16000);
    printf("%s     ██████         ███           ██       ███████            █████  █            ██████     ███    ███    ████████    ██           ███████\n",DB);
    usleep(16000);    
    printf("\n%s       ██                                                                                                                             %s██       ",Y,Y);
    usleep(17000);
    printf("%s      ██                                                                                                                             %s██       ",Y,Y);
    usleep(17000);
    printf("%s      ██                                                                                                                             %s██       ",Y,Y);
    usleep(17000);
    printf("%s      ██                                                                     __     __    ___        ___    __                       %s██       ",Y,Y);
    usleep(17000);
    printf("%s      ██                                                              |     |  |   |__|   |  |   |   | |   | __                      %s██       ",Y,Y);
    usleep(17000);
    printf("%s      ██                                                              |__   |__|   |  |   |__|   |   | |   |__|  ....                %s██       ",Y,Y);
    usleep(20000);
    printf("%s      ██                                                                                                                             %s██       ",Y,Y);
    usleep(20000);
    printf("%s      ██                                                                  ___________________________________                        %s██       ",Y,Y);
    usleep(20000);
    printf("%s      ██                                                                  █                                  █                       %s██       ",Y,Y);
    usleep(20000);
    printf("%s      ██                                                                  █ ████████████████████   █   █     █                       %s██       ",Y,Y);
    usleep(20000);
    printf("%s      ██████████████████████████████████████████████████████████████████  █__________________________________█ ██████████████████████%s██       ",Y,Y);


    

}

void simulacionCargaBienvenida() {
    for (int i = 0; i < 3; i++) { //repetimos la animacion 3 veces para simular un efecto de carga
        printf("\033[H\033[J"); //limpiamos pantalla
        usleep(300000);     // y se muestra vacía por 0.3 segundos
        mostrarBienvenida();
        usleep(350000);   //mostramos bienvenida por 0.35 segundos
    }
    usleep(700000);    // se mantiene la bienvenida 1 segundo
    printf("\033[H\033[J");  // limpia la pantalla para continuar con el siguiente menú
}

/*

int main() {
    // Limpiar la pantalla
    printf("\033[H\033[J");  // ANSI escape code to clear the screen

    // Llamada a la función de bienvenida
    //mostrarBienvenida();
      
    simulacionCargaBienvenida();
     

    return 0;
}
*/
    
