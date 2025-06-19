#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "boss.h"

using namespace std;
using namespace std :: chrono;
using namespace std :: this_thread;

int playerHP = 100;
int bossHP = 200;

void printStatus() {
    cout << "===========================\n";
    cout << "Player HP: " << playerHP << "\n";
    cout << "Boss   HP: " << bossHP << "\n";
    cout << "===========================\n";
}

void bossIntro() {
    system("cls"); // En Linux/macOS usar "clear"
    cout << bossASCII << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // ← Aquí corregido
}

void playerTurn() {
    int choice;
    cout << "\nTu turno:\n1. Atacar\n2. Curarte\n> ";
    cin >> choice;

    if (choice == 1) {
        int dmg = rand() % 20 + 10;
        cout << "¡Atacaste al jefe por " << dmg << " de daño!\n";
        bossHP -= dmg;
    } else if (choice == 2) {
        int heal = rand() % 15 + 10;
        cout << "Te curaste " << heal << " puntos de vida.\n";
        playerHP += heal;
        if (playerHP > 100) playerHP = 100;
    } else {
        cout << "¡Acción inválida! Perdiste el turno.\n";
    }
}

void bossTurn() {
    int attack = rand() % 25 + 5;
    cout << "El jefe te ataca con " << attack << " de daño!\n";
    playerHP -= attack;
}

int main() {
    srand(time(0));
    bossIntro();

    while (playerHP > 0 && bossHP > 0) {
        printStatus();
        playerTurn();
        if (bossHP <= 0) break;
        bossTurn();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    if (playerHP <= 0)
        cout << "\nHas sido derrotado... GAME OVER.\n";
    else
        cout << "\n¡Has vencido al jefe! ¡VICTORIA!\n";

    return 0;
}
