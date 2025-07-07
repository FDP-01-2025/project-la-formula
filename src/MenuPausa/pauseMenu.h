#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <iostream>
#include "saveGame.h"  // Para llamar saveGame()
#include "../Level1/Archi_h/rlutil.h"  // Ruta corregida

using namespace std;

namespace PauseMenu {

// Muestra el menú de pausa y permite guardar partida o salir sin guardar
// Retorna true si el jugador decide salir del juego, false si quiere continuar
inline bool showPauseMenu()
{
    rlutil::cls();
    rlutil::hidecursor();

    const char* opciones[] = {
        "Resume Game",
        "Save and Exit",
        "Exit without Saving"
    };
    int seleccion = 0;
    int key;

    while (true)
    {
        rlutil::cls();
        cout << "=== PAUSE MENU ===" << endl << endl;

        for (int i = 0; i < 3; i++)
        {
            if (i == seleccion)
                cout << "> ";
            else
                cout << "  ";

            cout << opciones[i] << endl;
        }

        key = rlutil::getkey();

        if (key == 'w' || key == 'W') {
            seleccion--;
            if (seleccion < 0) seleccion = 0;
        }
        else if (key == 's' || key == 'S') {
            seleccion++;
            if (seleccion > 2) seleccion = 2;
        }
        else if (key == rlutil::KEY_ENTER) {
            switch (seleccion)
            {
            case 0: // Resume Game
                return false; // No salir, continuar juego
            case 1: // Save and Exit
                if (saveGame()) {
                    cout << "Game saved successfully!" << endl;
                    rlutil::msleep(1500);
                    
                    // Reiniciar el programa para volver al menú principal
                    system("cls");
                    exit(0); // Salir del programa completamente
                } else {
                    cout << "Error saving game." << endl;
                    rlutil::msleep(1500);
                    return false; // Volver al juego si no se pudo guardar
                }
                break;
            case 2: // Exit without Saving
                system("cls");
                exit(0); // Salir del programa completamente
            }
        }
    }
}

} // namespace PauseMenu

#endif
