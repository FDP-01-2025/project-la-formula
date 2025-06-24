#include "Archi_h/boss.h"
#include "Archi_h/game.h"
#include "Archi_h/rlutil.h"
#include <iostream>
#include <windows.h>
#include <limits>

using namespace std;


void iniciarCombateJefe(Boss jefe) {

    rlutil::cls();
    cout << jefe.nombre << " aparece entre las sombras!\n\n";
    Sleep(2000);


    bool mensajeMitadMostrado = false; 


    while (jugador.hp > 0 && jefe.hp > 0) {

        rlutil::cls();
        rlutil::locate(1, 1);
        cout << "================== COMBATE FINAL ==================\n";
        rlutil::locate(1, 2);
        cout << "Jugador HP: " << jugador.hp << " " << barraHP(jugador.hp, jugador.hpMax) << "\n";
        rlutil::locate(1, 3);
        cout << jefe.nombre << " HP: " << jefe.hp << " " << barraHP(jefe.hp, jefe.hpMax) << "\n";
        rlutil::locate(1, 4);
        cout << "===================================================\n";

        // Mostrar ASCII del jefe
        int y = 6;
        string ascii = jefe.ascii;
        size_t pos = 0;

        while ((pos = ascii.find('\n')) != string::npos) {
            rlutil::locate(40, y++);
            cout << ascii.substr(0, pos);
            ascii.erase(0, pos + 1);
        }
        rlutil::locate(40, y);
        cout << ascii;

        // Opciones de jugador
        rlutil::locate(1,10);
        cout << "1. Atacar\n2. Curarse\n> ";
        int opcion;
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida.";
            Sleep(1000);
            continue;
        }

        rlutil::locate(1, 13);
        cout << "                                               ";

        if (opcion == 1) {
            int dmg = rand() % 10 + jugador.dano;
            jefe.hp -= dmg;
            rlutil::locate(1, 17);
            cout << "Le hiciste " << dmg << " de daño al jefe.\n";

        } 
        else if (opcion == 2) {
            int heal = rand() % 10 + 5;
            jugador.hp += heal;
            if (jugador.hp > jugador.hpMax) jugador.hp = jugador.hpMax;
            rlutil::locate(1, 17);
            cout << "Te curaste " << heal << " puntos.\n";

        }
        else {
            rlutil::locate(1, 14);
            cout << "Opción inválida.";
            Sleep(1000);
            continue;
        }

        Sleep(1000);

        if (jefe.hp > 0) {
            int edmg = rand() % jefe.dano + 5;
            jugador.hp -= edmg;
            rlutil::locate(1, 14);
            cout << "El jefe te golpea con " << edmg << " de dano.\n";
        }

        Sleep(1500);

        if (!mensajeMitadMostrado && jefe.hp <= jefe.hpMax / 2) {
            rlutil::locate(60, 3);  // Línea adecuada que no tape nada
            cout << jefe.nombre << ": \"!\"";
            mensajeMitadMostrado = true;

            Sleep(3000); // para dar tiempo a leerlo
        }

    }

    if (jugador.hp <= 0) {
        rlutil::cls();
        cout << "Has sido derrotado por el jefe. GAME OVER.\n";
        system("pause");
        exit(0);
    }

    rlutil::cls();  // LIMPIA toda la consola (para que no se vea el combate más)
    cout << "\n\n=====================================\n";
    cout << "FELICIDADES! Has derrotado al jefe final.\n";
    cout << "Redirigiendote al segundo nivel...\n";
    cout << "=====================================\n";
    Sleep(4000);   
    system("pause");
}
