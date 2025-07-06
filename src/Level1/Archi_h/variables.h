#ifndef VARIABLES_H
#define VARIABLES_H

#include "boss.h"
#include "Structs.h"

//variables gobales - estas son para uso dentro del namespace Nivel1

namespace Nivel1 {
    extern const int MAP_WIDTH;    //ancho de mapa
    extern const int MAP_HEIGHT;   //alto de mapa
    extern const int VIEW_WIDTH;   //vista de ancho de mapa
    extern const int VIEW_HEIGHT;  //vista de alto de mapa

    extern Character player;      
    extern int playerX, playerY;

    extern int defeatedEnemies;
    extern const int TOTAL_ENEMIES;

    extern bool keyHeld;
    extern unsigned long lastMoveTime;          //guarda el momento en que se movió por última vez el jugador.
    extern const unsigned long repeatDelay;

    extern bool unlockGate;
    extern bool bossDefeated;

    extern Boss firstBoss;
}

// Variable global compartida entre niveles
extern int actualLevel;

#endif
