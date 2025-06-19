#include <iostream>
#include <windows.h>
#include "rlutil.h"
using namespace std;

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 40;
const int VIEW_WIDTH = 40;
const int VIEW_HEIGHT = 20;

char mapa[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "################################################################################",
    "#......................~~~~~~.........T.............~~~~~...............~~~~~..#",
    "#...######..............~~~~~.............######..........######..............#",
    "#...#....#................~~~............##....##..............#..............#",
    "#...#....#...............TTT............##....##..............#..............T#",
    "#...######.........................#####..........####........#.........#####.#",
    "#.....................................T..........#..#........#..............T.#",
    "#....T..........####...................######.....#..#........####.............#",
    "#...............#..#.......................#.......................TTT........#",
    "#.......~~~.....####....TTT................#......................#####........#",
    "#.......~~~................................#.........TTT..................######",
    "#..........................................#.................................T#",
    "#.............TTT.........................##..............................#####",
    "#............................#####............................................#",
    "#....#####....................#T#.............................................#",
    "#....#T.#...............T.....###..................######.....................#",
    "#....###...........................................#....#.....................#",
    "#............................TTTT..................#....#.....................#",
    "#..................................................######.....................#",
    "################################################################################"
};

int playerX = 10;
int playerY = 10;

// Control de repetición
bool keyHeld = false;
DWORD lastMoveTime = 0;
const DWORD initialDelay = 200;  // Tiempo para la primera repetición (ms)
const DWORD repeatDelay = 80;    // Tiempo entre repeticiones

void moverJugador(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;
    if (newX >= 0 && newX < MAP_WIDTH &&
        newY >= 0 && newY < MAP_HEIGHT &&
        mapa[newY][newX] != '#') {
        playerX = newX;
        playerY = newY;
    }
}

void dibujarVista() {
    int offsetX = playerX - VIEW_WIDTH / 2;
    int offsetY = playerY - VIEW_HEIGHT / 2;

    for (int y = 0; y < VIEW_HEIGHT; y++) {
        for (int x = 0; x < VIEW_WIDTH; x++) {
            int mapX = offsetX + x;
            int mapY = offsetY + y;

            rlutil::locate(x + 1, y + 1);

            if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
                rlutil::setColor(rlutil::WHITE);
                cout << ' ';
            } else if (mapX == playerX && mapY == playerY) {
                rlutil::setColor(rlutil::LIGHTRED);
                cout << '@';
            } else {
                char tile = mapa[mapY][mapX];
                switch (tile) {
                    case '#': rlutil::setColor(rlutil::GREY); break;
                    case '~': rlutil::setColor(rlutil::CYAN); break;
                    case 'T': rlutil::setColor(rlutil::GREEN); break;
                    case '.': rlutil::setColor(rlutil::BROWN); break;
                    default: rlutil::setColor(rlutil::WHITE); break;
                }
                cout << tile;
            }
        }
    }

    rlutil::setColor(rlutil::WHITE);
}

void chequearMovimiento() {
    static int lastDir = 0; // 1=W, 2=S, 3=A, 4=D
    DWORD now = GetTickCount();

    auto mover = [&](int dir, int dx, int dy) {
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

    while (true) {
        dibujarVista();
        chequearMovimiento();
        Sleep(30); // Bucle rápido pero controlado
    }

    return 0;
}
