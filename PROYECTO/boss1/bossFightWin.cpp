#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "boss.h"
using namespace std;


// Variables
int playerHP = 100;
int bossHP = 200;

// Mover cursor
void gotoxy(int x, int y) {
    COORD coord{(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Ocultar cursor para que no parpadee
void ocultarCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}

// Barra de vida visual
string barraHP(int hpActual, int hpMax, int largo = 15) {
    if(hpActual < 0) hpActual = 0;
    int llenos = (hpActual * largo) / hpMax;
    int vacios = largo - llenos;
    return "[" + string(llenos, '#') + string(vacios, '-') + "]";
}

// Mostrar HP en pantalla con barras
void printStatus() {
    gotoxy(0, 0);
    cout << "================================       ";
    gotoxy(40, 0); cout << "   BOSS APARECE!";
    gotoxy(0, 1);
    cout << "Player HP: " << playerHP << "  " << barraHP(playerHP, 100) << "     ";
    gotoxy(0, 2);
    cout << "Boss   HP: " << bossHP << "  " << barraHP(bossHP, 200) << "     ";
    gotoxy(0, 3);
    cout << "================================        ";
}

// Mostrar el ASCII del jefe a la derecha
void showBossASCII() {
    int startX = 40, startY = 2;
    int line = 0;
    string art = bossASCII;
    size_t pos = 0;
    while ((pos = art.find('\n')) != string::npos) {
        gotoxy(startX, startY + line);
        cout << art.substr(0, pos);
        art.erase(0, pos + 1);
        line++;
    }
}

// Mensaje de daño o curación
void showMessage(string msg) {
    gotoxy(0, 5);
    cout << "                                         ";  // limpiar línea
    gotoxy(0, 5);
    cout << msg;
}

// Turno del jugador
void playerTurn() {
    gotoxy(0, 7);
    cout << "Tu turno:\n1. Atacar\n2. Curarte\n> ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int dmg = rand() % 20 + 10;
        bossHP -= dmg;
        showMessage("Atacaste al jefe por " + to_string(dmg) + " de dano!");
    } else if (choice == 2) {
        int heal = rand() % 15 + 10;
        playerHP += heal;
        if (playerHP > 100) playerHP = 100;
        showMessage("Te curaste " + to_string(heal) + " puntos de vida.");
    } else {
        showMessage("Acción invalida! Perdiste el turno.");
    }
}

// Turno del jefe
void bossTurn() {
    int attack = rand() % 25 + 5;
    playerHP -= attack;
    showMessage("El jefe te ataca con " + to_string(attack) + " de dano!");
}

// MAIN
int main() {
    srand(time(0));
    ocultarCursor();
    system("cls");
    showBossASCII();

    while (playerHP > 0 && bossHP > 0) {
        printStatus();
        playerTurn();
        Sleep(1000);
        if (bossHP <= 0) break;
        printStatus();
        bossTurn();
        Sleep(1000);
    }

    gotoxy(0, 10);
    if (playerHP <= 0)
        cout << "Has sido derrotado... GAME OVER.\n";
    else
        cout << "¡Has vencido al jefe! ¡VICTORIA!\n";

    gotoxy(0, 13);
    return 0;
}
