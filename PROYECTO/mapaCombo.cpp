#include <iostream>
#include <windows.h>
#include "rlutil.h"
#include <limits>

using namespace std;

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 20;
const int VIEW_WIDTH = 40;
const int VIEW_HEIGHT = 20;

// Mapa con enemigos (letra 'E')
char mapa[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "################################################################################",
    "#......................~~~~~~.........T.............~~~~~...............~~~~~..#",
    "#...######..............~~~~~.............######..........######..............#",
    "#...#....#................~~~............##....##..............#..............#",
    "#...#....#...............TTT............##....##..............#..............T#",
    "#...######.........................#####..........####........#.........#####.#",
    "#.....................................T..........#..#........#..............T.#",
    "#....T..........####...................######.....#..#........####......E......#",
    "#...............#..#.......................#.......................TTT........#",
    "#.......~~~.....####....TTT................#......................#####........#",
    "#.......~~~.......................E........#.........TTT..................######",
    "#..........................................#.................................T#",
    "#.............TTT.........................##..............................#####",
    "#............................#####............................................#",
    "#....#####....................#T#.............................................#",
    "#....#T.#...............T.....###..................######.....................#",
    "#....###...........................................#....#...........E.........#",
    "#............E...............TTTT..................#....#.....................#",
    "#..................................................######.....................#",
    "################################################################################"
};

// Struct para jugador
struct Personaje {
    int x;
    int y;
    int hp;
    int hpMax;
    int dano;
    int nivel;
};

Personaje jugador = {10, 10, 100, 100, 10, 1};

// Movimiento con delay (opcional)
bool keyHeld = false;
DWORD lastMoveTime = 0;
const DWORD repeatDelay = 80;

void mostrarHUD() {
    rlutil::locate(1, 1);
    rlutil::setColor(rlutil::WHITE);
    cout << "Nivel: " << jugador.nivel << "   Daño: " << jugador.dano << "   HP: " << jugador.hp << "    ";
}

bool iniciarCombate() {
    int enemyHP = 30;
    int enemyDano = 5;

    rlutil::cls();
    cout << "¡Un enemigo salvaje apareció!\n";

    // Limpiar buffer solo una vez al inicio del combate
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    while (jugador.hp > 0 && enemyHP > 0) {
        cout << "\nTu HP: " << jugador.hp << "   Enemigo HP: " << enemyHP << "\n";
        cout << "1. Atacar\n2. Curarse\n> ";

        int opcion;
        cin >> opcion;

        if (cin.fail()) {
            cin.clear(); // limpiar error si se ingresó letra
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Entrada inválida. Usa 1 o 2.\n";
            continue;
        }

        if (opcion == 1) {
            enemyHP -= jugador.dano;
            cout << "Atacaste al enemigo por " << jugador.dano << " de daño.\n";
        } else if (opcion == 2) {
            int heal = rand() % 10 + 5;
            jugador.hp += heal;
            if(jugador.hp > jugador.hpMax) jugador.hp = jugador.hpMax;
            cout << "Te curaste " << heal << " puntos.\n";
        } else {
            cout << "Opción inválida.\n";
            continue;
        }

        if (enemyHP > 0) {
            jugador.hp -= enemyDano;
            cout << "El enemigo te golpea por " << enemyDano << " de daño.\n";
        }

        Sleep(1000);
    }

    if (jugador.hp <= 0) {
        cout << "\nHas sido derrotado. GAME OVER.\n";
        exit(0);
    }

    cout << "\n¡Ganaste el combate!\n";
    jugador.nivel++;
    jugador.dano += 2;
    jugador.hp += 10;
    if (jugador.hp > jugador.hpMax) jugador.hp = jugador.hpMax;

    Sleep(1000);
    rlutil::cls();
    return true;
}

void moverJugador(int dx, int dy) {
    int newX = jugador.x + dx;
    int newY = jugador.y + dy;

    if (newX >= 0 && newX < MAP_WIDTH &&
        newY >= 0 && newY < MAP_HEIGHT) {
        
        char destino = mapa[newY][newX];
        if (destino == '#') return;

        if (destino == 'E') {
            if (iniciarCombate()) {
                mapa[newY][newX] = '.';
            }
        }

        jugador.x = newX;
        jugador.y = newY;
    }
}

void dibujarVista() {
    int offsetX = jugador.x - VIEW_WIDTH / 2;
    int offsetY = jugador.y - VIEW_HEIGHT / 2;

    for (int y = 0; y < VIEW_HEIGHT; y++) {
        for (int x = 0; x < VIEW_WIDTH; x++) {
            int mapX = offsetX + x;
            int mapY = offsetY + y;

            rlutil::locate(x + 1, y + 2); // línea 2 por el HUD

            if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
                rlutil::setColor(rlutil::WHITE);
                cout << ' ';
            } else if (mapX == jugador.x && mapY == jugador.y) {
                rlutil::setColor(rlutil::LIGHTRED);
                cout << '@';
            } else {
                char tile = mapa[mapY][mapX];
                switch (tile) {
                    case '#': rlutil::setColor(rlutil::GREY); break;
                    case '~': rlutil::setColor(rlutil::CYAN); break;
                    case 'T': rlutil::setColor(rlutil::GREEN); break;
                    case '.': rlutil::setColor(rlutil::BROWN); break;
                    case 'E': rlutil::setColor(rlutil::LIGHTBLUE); break;
                    default: rlutil::setColor(rlutil::WHITE); break;
                }
                cout << tile;
            }
        }
    }

    rlutil::setColor(rlutil::WHITE);
}

void chequearMovimiento() {
    static int lastDir = 0;
    DWORD now = GetTickCount();

    auto mover = [&](int dir, int dx, int dy) {          //Lambda, usada para no repetir cada caso de tecla 
        if (GetAsyncKeyState(dir) & 0x8000) {
            if (!keyHeld || lastDir != dir || now - lastMoveTime > repeatDelay) {
                moverJugador(dx, dy);
                lastMoveTime = now;
                keyHeld = true;
                lastDir = dir;
            }
        } else if (lastDir == dir) {
            keyHeld = false;
        }
    };

    mover('W', 0, -1);
    mover('S', 0, 1);
    mover('A', -1, 0);
    mover('D', 1, 0);
}

int main() {
    rlutil::hidecursor();
    system("cls");

    while (true) {
        mostrarHUD();
        dibujarVista();
        chequearMovimiento();
        Sleep(30);
    }

    return 0;
}
