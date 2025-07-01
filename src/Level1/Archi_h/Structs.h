#pragma once
#include <iostream>
#include <string>
#include "rlutil.h"

using namespace std;
using namespace rlutil;

struct Character {
    int hp;
    int hpMax;
    int dmg;
    int level;
};

struct Enemy {
    std::string name;
    int hp;
    int hpMax;
    int dmg;
    std::string ascii;
};


  string HPbar(int x, int y, int hpActual, int hpMax, string name){
    locate(x, y);
    cout << name << " HP: ";
    int barWidth = 20;
    int filled = (hpActual * barWidth) / hpMax;
    setColor(rlutil::GREEN);
    for (int i = 0; i < filled; i++) cout << "#";
    setColor(rlutil::RED);
    for (int i = filled; i < barWidth; i++) cout << "-";
    setColor(rlutil::WHITE);
    cout << " " << hpActual << "/" << hpMax;
}      



