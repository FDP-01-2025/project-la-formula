#ifndef LOADGAME_H
#define LOADGAME_H

#include <fstream>
#include <iostream>
#include <string>
#include "../Level1/Archi_h/Structs.h"  // Para la definición de Character
#include "../MenuStart_End/finalscreen.h"
#include "../MenuStart_End/mainmenu.h"      // Para acceder al nombre del jugador

using namespace std;

// Variables globales que necesitamos (declaradas en main.cpp y en cada nivel)
extern int actualLevel;

// Declaraciones externas para variables de cada nivel
namespace Nivel1 {
    extern int playerX, playerY;
    extern Character player;
    extern bool unlockGate, bossDefeated;
    extern int defeatedEnemies;
    extern char map[20][81];
}

namespace Nivel2 {
    extern int playerX2, playerY2;
    extern Character player2;
    extern bool unlockGate2, bossDefeated2;
    extern int defeatedEnemies2;
    extern char map[20][81];
}

namespace Nivel3 {
    extern int playerX3, playerY3;
    extern Character player3;
    extern bool unlockGate3, bossDefeated3;
    extern int defeatedEnemies3;
    extern char map[20][81];
}

// Función global de carga - versión con archivos de texto
 bool loadGame() {
    ifstream file("savegame.txt");
    if (!file) {
        cout << "No save file found." << endl;
        return false;
    }

    // Cargar datos básicos
    file >> actualLevel;
    file.ignore(); // Ignorar el salto de línea después del número
    getline(file, MainMenu::playerName);
    
    // Cargar datos según el nivel guardado
    if (actualLevel == 1) {
        file >> Nivel1::playerX >> Nivel1::playerY;
        file >> Nivel1::player.hp >> Nivel1::player.hpMax 
             >> Nivel1::player.dmg >> Nivel1::player.level;
        file >> Nivel1::unlockGate >> Nivel1::bossDefeated >> Nivel1::defeatedEnemies;
        file.ignore(); // Ignorar el salto de línea
        
        // Cargar el mapa línea por línea
        for (int y = 0; y < 20; y++) {
            file.getline(Nivel1::map[y], 81);
        }
    }
    else if (actualLevel == 2) {
        file >> Nivel2::playerX2 >> Nivel2::playerY2;
        file >> Nivel2::player2.hp >> Nivel2::player2.hpMax 
             >> Nivel2::player2.dmg >> Nivel2::player2.level;
        file >> Nivel2::unlockGate2 >> Nivel2::bossDefeated2 >> Nivel2::defeatedEnemies2;
        file.ignore(); // Ignorar el salto de línea
        
        // Cargar el mapa línea por línea
        for (int y = 0; y < 20; y++) {
            file.getline(Nivel2::map[y], 81);
        }
    }
    else if (actualLevel == 3) {
        file >> Nivel3::playerX3 >> Nivel3::playerY3;
        file >> Nivel3::player3.hp >> Nivel3::player3.hpMax 
             >> Nivel3::player3.dmg >> Nivel3::player3.level;
        file >> Nivel3::unlockGate3 >> Nivel3::bossDefeated3 >> Nivel3::defeatedEnemies3;
        file.ignore(); // Ignorar el salto de línea
        
        // Cargar el mapa línea por línea
        for (int y = 0; y < 20; y++) {
            file.getline(Nivel3::map[y], 81);
        }
    }

    file.close();
    cout << "Game loaded successfully! Player: " << MainMenu::playerName << ", Level: " << actualLevel << endl;
    return true;
}

#endif
