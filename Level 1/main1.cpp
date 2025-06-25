#include <iostream>   //para entrada y salida de datos.
#include <windows.h>  //para sleep y GetAsyncKeyState() para detectar teclas presionadas sin bloqueo (lectura de teclas en tiempo real).
#include <limits>     //Usas para limpiar el buffer de entrada cuando hay error en cin: cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include <cstdlib>    //rand(), srand() para inicializar la semilla de aleatoriedad y exit(0)  y size_t
#include <ctime>      //time(0) para obtener tiempo actual como semilla para srand.

#include "Archi_h/game.h"
#include "Archi_h/mapa.h"
#include "Archi_h/rlutil.h"

using namespace std;

int main() {
    
    srand(time(0));       //inicializa el generador de números aleatorios con la hora actual como semilla. Esto para los ataques/curaciones
    rlutil::hidecursor(); //inicializa el generador de números aleatorios con la hora actual como semilla.
    system("cls");        //Limpia toda la consola al iniciar el juego.

    while (true) {        //bucle principal del juego, se repite para siempre hasta que el juego termine o el jugador muera (true nunca cambia, a no ser que haya un break dentro del while)
        mostrarHUD();     
        dibujarVista();         //Mandar a llamar las funciones void.
        chequearMovimiento();
        Sleep(30);        //Espera 30 milisegundos para que la CPU no se sobrecargue y los movimientos sean suaves
    }

    return 0;
}
