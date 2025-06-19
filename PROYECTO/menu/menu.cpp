#include <iostream>
#include "rlutil.h"
using namespace std;

const int numOpciones = 3;
string opciones[numOpciones] = {"Iniciar Juego", "Cargar Partida", "Salir"};

void dibujarFondo() {
    rlutil::setColor(rlutil::DARKGREY);
    for (int y = 1; y <= 25; y++) {
        for (int x = 1; x <= 80; x++) {
            rlutil::locate(x, y);
            cout << ((x + y) % 2 == 0 ? '.' : ' ');
        }
    }
}

void mostrarOpcion(int i, bool seleccionada) {
    rlutil::locate(30, 10 + i);
    if (seleccionada) {
        rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
        rlutil::setColor(rlutil::BLACK);
    } else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
    }
    cout << opciones[i] << "     "; // espacio extra para borrar texto anterior
    rlutil::setBackgroundColor(rlutil::BLACK); // limpiar estado
}

int main() {
    int opcion = 0;
    int opcionAnterior = -1;
    rlutil::hidecursor();

    rlutil::cls();
    dibujarFondo();

    // Mostrar menú inicial
    for (int i = 0; i < numOpciones; i++) {
        mostrarOpcion(i, i == opcion);
    }

    while (true) {
        int tecla = rlutil::getkey();
        opcionAnterior = opcion;

        if (tecla == rlutil::KEY_DOWN)
            opcion = (opcion + 1) % numOpciones;
        else if (tecla == rlutil::KEY_UP)
            opcion = (opcion - 1 + numOpciones) % numOpciones;
        else if (tecla == rlutil::KEY_ENTER)
            break;

        if (opcion != opcionAnterior) {
            mostrarOpcion(opcionAnterior, false);  // quitar resaltado anterior
            mostrarOpcion(opcion, true);           // resaltar nueva opción
        }
    }

    rlutil::cls();
    cout << "Elegiste: " << opciones[opcion] << endl;
    return 0;
}
