#pragma once
#include <iostream>
#include <string>

using namespace std;

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


  string barraHP(int hpActual, int hpMax, int largo = 15){
    if (hpActual < 0) hpActual = 0;                  // Asegura que no haya vida negativa. Si el personaje tiene -5 de vida, se corrige a 0 para que la barra no salga mal.
    int llenos = (hpActual * largo) / hpMax;         // Calcula cuántos caracteres deben estar "llenos" (con #)
    int vacios = largo - llenos;                     // Calcula cuántos caracteres deben estar "vacíos" (con `-`) para completar el tamaño total de la barra.

    //string(n, char) crea una cadena con n repeticiones del carácter char.
    return "[" + string(llenos, '#') + string(vacios, '-') + "]";           
}


