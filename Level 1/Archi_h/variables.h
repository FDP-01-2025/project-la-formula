#ifndef VARIABLES_H
#define VARIABLES_H

#include "boss.h"
#include "Structs.h"

//variables gobales

extern const int MAP_WIDTH;    //ancho de mapa
extern const int MAP_HEIGHT;   //alto de mapa
extern const int VIEW_WIDTH;   //vista de ancho de mapa
extern const int VIEW_HEIGHT;  //vista de alto de mapa

extern Personaje jugador;      
extern int playerX, playerY;

extern int enemigosDerrotados;
extern const int TOTAL_ENEMIGOS;

extern bool keyHeld;
extern unsigned long lastMoveTime;          //guarda el momento en que se movió por última vez el jugador.
extern const unsigned long repeatDelay;

extern bool puertaDesbloqueada;
extern bool jefeDerrotado;

extern Boss jefeFinal;

#endif
