
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

void dibujarVista() {
    int offsetX = playerX - VIEW_WIDTH / 2;
    int offsetY = playerY - VIEW_HEIGHT / 2;

    for (int y = 0; y < VIEW_HEIGHT; y++) {
        for (int x = 0; x < VIEW_WIDTH; x++) {
            int mapX = offsetX + x;
            int mapY = offsetY + y;

            rlutil::locate(x + 1, y + 1);  // Terminal: (1,1) es la esquina

            if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
                rlutil::setColor(rlutil::WHITE);
                cout << ' ';
            } else if (mapX == playerX && mapY == playerY) {
                rlutil::setColor(rlutil::LIGHTRED);
                cout << '@';
            } else {
                char tile = mapa[mapY][mapX];
                switch (tile) {
                    case '#': rlutil::setColor(rlutil::GREY); break;     // Pared
                    case '~': rlutil::setColor(rlutil::CYAN); break;     // Agua
                    case 'T': rlutil::setColor(rlutil::GREEN); break;    // Árbol
                    case '.': rlutil::setColor(rlutil::BROWN); break;    // Tierra
                    default: rlutil::setColor(rlutil::WHITE); break;
                }
                cout << tile;
            }
        }
    }

    rlutil::setColor(rlutil::WHITE);  // Restaurar color
}

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

int main() {
    rlutil::hidecursor();

    while (true) {
        dibujarVista();

        if (GetAsyncKeyState('W') & 0x8000) moverJugador(0, -1);
        if (GetAsyncKeyState('S') & 0x8000) moverJugador(0, 1);
        if (GetAsyncKeyState('A') & 0x8000) moverJugador(-1, 0);
        if (GetAsyncKeyState('D') & 0x8000) moverJugador(1, 0);

        Sleep(80);
    }

    return 0;
}
