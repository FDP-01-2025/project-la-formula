#pragma once      //Evita que el archivo se incluya más de una vez al compilar
#include <string>

struct Boss {
    std::string nombre;
    int hp;
    int hpMax;
    int dano;
    std::string ascii;
};

void iniciarCombateJefe(Boss jefe);
