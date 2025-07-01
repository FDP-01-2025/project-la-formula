#ifndef VARIABLES2_H
#define VARIABLES2_H

#include "../../Level1/Archi_h/boss.h"
#include "../../Level1/Archi_h/Structs.h"

namespace Nivel2{

//variables globales del Nivel 2

extern const int MAP_WIDTH2;    //ancho de mapa
extern const int MAP_HEIGHT2;   //alto de mapa
extern const int VIEW_WIDTH2;   //vista de ancho de mapa
extern const int VIEW_HEIGHT2;  //vista de alto de mapa

extern Character player2;      
extern int playerX2, playerY2;

extern int defeatedEnemies2;
extern const int TOTAL_ENEMIES2;

extern bool keyHeld;
extern unsigned long lastMoveTime;          //guarda el momento en que se movió por última vez el jugador.
extern const unsigned long repeatDelay;

extern bool unlockGate2;
extern bool bossDefeated2;

extern Boss secondBoss;

}

#endif
