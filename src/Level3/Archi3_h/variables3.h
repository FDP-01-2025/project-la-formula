#ifndef VARIABLES3_H
#define VARIABLES3_H

#include "../../Level1/Archi_h/boss.h"
#include "../../Level1/Archi_h/Structs.h"

namespace Nivel3{

//variables globales del Nivel 2

extern const int MAP_WIDTH3;    //ancho de mapa
extern const int MAP_HEIGHT3;   //alto de mapa
extern const int VIEW_WIDTH3;   //vista de ancho de mapa
extern const int VIEW_HEIGHT3;  //vista de alto de mapa

extern Character player3;      
extern int playerX3, playerY3;

extern int defeatedEnemies3;
extern const int TOTAL_ENEMIES3;

extern bool keyHeld;
extern unsigned long lastMoveTime;          //guarda el momento en que se movió por última vez el jugador.
extern const unsigned long repeatDelay;

extern bool unlockGate3;
extern bool bossDefeated3;

extern Boss thirdBoss;

}

#endif
