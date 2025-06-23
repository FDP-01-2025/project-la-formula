#ifndef GAME_H
#define GAME_H

#include <string>


struct Personaje {
    int hp;
    int hpMax;
    int dano;
    int nivel;
};

struct Enemigo {
    std::string nombre;
    int hp;
    int hpMax;
    int dano;
    std::string ascii;
};

// Variables globales (extern para que no se definan múltiples veces)
extern Personaje jugador;
extern int playerX;
extern int playerY;


// Funciones
void mostrarHUD();
std::string barraHP(int hpActual, int hpMax, int largo = 15);
bool iniciarCombate();
void moverJugador(int dx, int dy);
void dibujarVista();
void chequearMovimiento();

#endif
