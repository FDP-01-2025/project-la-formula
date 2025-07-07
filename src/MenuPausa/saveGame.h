#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <iostream>
#include <fstream>
#include <string>
#include "../Level1/Archi_h/Structs.h"  // Para la definición de Character
#include "../MenuStart_End/finalscreen.h"
#include "../MenuStart_End/mainmenu.h"

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

// Función global de guardado - versión con archivos de texto
inline bool saveGame()
{
    ofstream file("savegame.txt");
    if (!file) {
        cout << "Error: Could not create save file." << endl;
        return false;
    }

    // Guardar datos básicos
    file << actualLevel << endl;
    file << MainMenu::playerName << endl;
    
    // Guardar datos según el nivel actual
    if (actualLevel == 1) {
        file << Nivel1::playerX << " " << Nivel1::playerY << endl;
        file << Nivel1::player.hp << " " << Nivel1::player.hpMax << " " 
             << Nivel1::player.dmg << " " << Nivel1::player.level << endl;
        file << Nivel1::unlockGate << " " << Nivel1::bossDefeated << " " << Nivel1::defeatedEnemies << endl;
        
        // Guardar el mapa línea por línea
        for (int y = 0; y < 20; y++) {
            file << Nivel1::map[y] << endl;
        }
    }
    else if (actualLevel == 2) {
        file << Nivel2::playerX2 << " " << Nivel2::playerY2 << endl;
        file << Nivel2::player2.hp << " " << Nivel2::player2.hpMax << " " 
             << Nivel2::player2.dmg << " " << Nivel2::player2.level << endl;
        file << Nivel2::unlockGate2 << " " << Nivel2::bossDefeated2 << " " << Nivel2::defeatedEnemies2 << endl;
        
        // Guardar el mapa línea por línea
        for (int y = 0; y < 20; y++) {
            file << Nivel2::map[y] << endl;
        }
    }
    else if (actualLevel == 3) {
        file << Nivel3::playerX3 << " " << Nivel3::playerY3 << endl;
        file << Nivel3::player3.hp << " " << Nivel3::player3.hpMax << " " 
             << Nivel3::player3.dmg << " " << Nivel3::player3.level << endl;
        file << Nivel3::unlockGate3 << " " << Nivel3::bossDefeated3 << " " << Nivel3::defeatedEnemies3 << endl;
        
        // Guardar el mapa línea por línea
        for (int y = 0; y < 20; y++) {
            file << Nivel3::map[y] << endl;
        }
    }

    file.close();
    cout << "Game saved successfully!" << endl;
    return true;
}

#endif
