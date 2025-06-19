#include <iostream>
#include <windows.h>
#include "rlutil.h"
using namespace std;

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 20;  // Ajusté para que cuadre con tu mapa real
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

// Pongo enemigos en estas posiciones (pueden estar en mapa como 'E')
struct Pos { int x,y; };
Pos enemigos[] = { {20,5}, {60,8}, {15,14} };

int numEnemigos = sizeof(enemigos)/sizeof(enemigos[0]);

int playerX = 10;
int playerY = 10;

bool keyHeld = false;
DWORD lastMoveTime = 0;
const DWORD initialDelay = 200;
const DWORD repeatDelay = 80;

int nivelJugador = 1;
int danoJugador = 15;

int experiencia = 0;
int experienciaParaSubir = 100;

void mostrarInfoJugador() {
    rlutil::locate(1, 21);
    cout << "Nivel: " << nivelJugador << "  Daño: " << danoJugador << "  Experiencia: " << experiencia << "/" << experienciaParaSubir << "          ";
}

void subirNivel() {
    nivelJugador++;
    danoJugador += 5;
    experiencia -= experienciaParaSubir;
    experienciaParaSubir += 50;

    rlutil::locate(1, 21);
    cout << "¡¡Subiste al nivel " << nivelJugador << "! Daño aumentado a " << danoJugador << "!          ";
    Sleep(1500);
    rlutil::locate(1, 21);
    cout << "Nivel: " << nivelJugador << "  Daño: " << danoJugador << "  Experiencia: " << experiencia << "/" << experienciaParaSubir << "          ";
}

// Función para detectar si la posición tiene un enemigo
int enemigoEnPos(int x, int y) {
    for (int i = 0; i < numEnemigos; i++) {
        if (enemigos[i].x == x && enemigos[i].y == y) return i;
    }
    return -1;
}

// Combate muy simple
bool combate() {
    int vidaEnemigo = 50 + nivelJugador * 20;
    int danoEnemigo = 10 + nivelJugador * 5;
    int vidaJugador = 100 + nivelJugador * 20;

    while (vidaEnemigo > 0 && vidaJugador > 0) {
        system("cls");
        cout << "COMBATE!\n";
        cout << "Vida jugador: " << vidaJugador << "\n";
        cout << "Vida enemigo: " << vidaEnemigo << "\n";
        cout << "Atacar (1) o Curar (2)? > ";
        int op; cin >> op;

        if (op == 1) {
            vidaEnemigo -= danoJugador;
            cout << "Le diste " << danoJugador << " de daño!\n";
        } else if (op == 2) {
            vidaJugador += 20;
            if (vidaJugador > 100 + nivelJugador * 20) vidaJugador = 100 + nivelJugador * 20;
            cout << "Te curaste 20 puntos\n";
        } else {
            cout << "Opción inválida\n";
        }

        if (vidaEnemigo > 0) {
            vidaJugador -= danoEnemigo;
            cout << "El enemigo te golpea con " << danoEnemigo << " de daño!\n";
        }

        system("pause");
    }

    return vidaJugador > 0;
}

void moverJugador(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;
    if (newX >= 0 && newX < MAP_WIDTH &&
        newY >= 0 && newY < MAP_HEIGHT &&
        mapa[newY][newX] != '#') {
        // Antes de mover, chequeo enemigo
        int enemigoID = enemigoEnPos(newX, newY);
        if (enemigoID != -1) {
            cout << "\nTe encontraste con un enemigo!\n";
            Sleep(1000);
            bool gano = combate();
            if (gano) {
                cout << "Derrotaste al enemigo!\n";
                experiencia += 50 + nivelJugador * 20;
                if (experiencia >= experienciaParaSubir) subirNivel();

                // Quitar enemigo del mapa (fuera del array de enemigos para simplificar)
                enemigos[enemigoID].x = -1;
                enemigos[enemigoID].y = -1;
                Sleep(1000);
            } else {
                cout << "Has sido derrotado...\n";
                exit(0);
            }
        } else {
            playerX = newX;
            playerY = newY;
        }
    }
}

void dibujarVista() {
    int offsetX = playerX - VIEW_WIDTH / 2;
    int offsetY = playerY - VIEW_HEIGHT / 2;

    system("cls");

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
                // Mostrar enemigos
                bool dibujarEnemigo = false;
                for (int i = 0; i < numEnemigos; i++) {
                    if (enemigos[i].x == mapX && enemigos[i].y == mapY) {
                        rlutil::setColor(rlutil::LIGHTMAGENTA);
                        cout << 'E';
                        dibujarEnemigo = true;
                        break;
                    }
                }
                if (!dibujarEnemigo) {
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
    }

    mostrarInfoJugador();
}

void chequearMovimiento() {
    static int lastDir = 0;
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
        Sleep(30);
    }

    return 0;
}
