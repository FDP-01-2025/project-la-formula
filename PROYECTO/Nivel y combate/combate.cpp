#include <iostream>
#include <windows.h>
#include "rlutil.h"


using namespace std;

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 20;  // ajusté altura para que coincida con el mapa
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

// Dibuja un tile simple del mapa (sin jugador)
void dibujarTile(int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return;
    rlutil::locate(x + 1, y + 1);

    char tile = mapa[y][x];
    rlutil::setColor(rlutil::WHITE);

    switch (tile) {
        case '#': rlutil::setColor(rlutil::GREY); break;
        case '~': rlutil::setColor(rlutil::CYAN); break;
        case 'T': rlutil::setColor(rlutil::GREEN); break;
        case '.': rlutil::setColor(rlutil::BROWN); break;
        default: rlutil::setColor(rlutil::WHITE); break;
    }

    cout << tile;
}

// Dibuja al jugador en la posición dada
void dibujarJugador(int x, int y) {
    rlutil::locate(x + 1, y + 1);
    rlutil::setColor(rlutil::LIGHTRED);
    cout << '@';
}

// Dibuja la vista completa alrededor del jugador (solo al inicio)
void dibujarVistaCompleta() {
    int offsetX = playerX - VIEW_WIDTH / 2;
    int offsetY = playerY - VIEW_HEIGHT / 2;

    for (int y = 0; y < VIEW_HEIGHT; y++) {
        for (int x = 0; x < VIEW_WIDTH; x++) {
            int mapX = offsetX + x;
            int mapY = offsetY + y;
            dibujarTile(mapX, mapY);
        }
    }
}

// Actualiza la info arriba (HUD) sin borrar pantalla
void mostrarInfoJugador(int nivel, int dano) {
    rlutil::locate(1, 1);
    rlutil::setColor(rlutil::WHITE);
    cout << "Nivel: " << nivel << "    Dano: " << dano << "           ";  // Espacios para limpiar restos
}

void moverJugador(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;
    if (newX >= 0 && newX < MAP_WIDTH &&
        newY >= 0 && newY < MAP_HEIGHT &&
        mapa[newY][newX] != '#') {

        // Redibuja tile donde estaba el jugador (para "borrar" jugador viejo)
        dibujarTile(playerX, playerY);

        playerX = newX;
        playerY = newY;

        // Dibuja jugador en la nueva posición
        dibujarJugador(playerX, playerY);
    }
}

int main() {
    rlutil::hidecursor();

    int nivel = 1;
    int dano = 10;

    system("cls");
    dibujarVistaCompleta();
    dibujarJugador(playerX, playerY);
    mostrarInfoJugador(nivel, dano);

    while (true) {
        if (rlutil::kbhit()) {
            char tecla = rlutil::getkey();

            switch (tecla) {
                case 'w':
                case 'W':
                    moverJugador(0, -1);
                    break;
                case 's':
                case 'S':
                    moverJugador(0, 1);
                    break;
                case 'a':
                case 'A':
                    moverJugador(-1, 0);
                    break;
                case 'd':
                case 'D':
                    moverJugador(1, 0);
                    break;
                case 'q':
                case 'Q':
                    return 0;  // Salir
            }

            // Simular subir de nivel (por ejemplo, cada 5 movimientos)
            static int movimientos = 0;
            movimientos++;
            if (movimientos % 5 == 0) {
                nivel++;
                dano += 2;
                mostrarInfoJugador(nivel, dano);
            }
        }
        Sleep(30);
    }

    return 0;
}
