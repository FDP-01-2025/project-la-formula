#include <windows.h>
#include <iostream>



using namespace std;

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 40;

const int VIEW_WIDTH = 30;
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

void drawFrame(HANDLE hBuffer) {
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hBuffer, pos);

    int offsetX = playerX - VIEW_WIDTH / 2;
    int offsetY = playerY - VIEW_HEIGHT / 2;

    for (int y = 0; y < VIEW_HEIGHT; y++) {
        for (int x = 0; x < VIEW_WIDTH; x++) {
            int mapX = offsetX + x;
            int mapY = offsetY + y;

            if (mapX == playerX && mapY == playerY) {
                cout << '@';
            } else if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
                cout << ' ';
            } else {
                cout << mapa[mapY][mapX];
            }
        }
        cout << '\n';
    }
}

int main() {
    // Crear dos buffers
    HANDLE hOut[2];
    hOut[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    hOut[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    int current = 0;
    SetConsoleActiveScreenBuffer(hOut[current]);

    while (true) {
        // Dibuja en el buffer inactivo
        drawFrame(hOut[current]);
        SetConsoleActiveScreenBuffer(hOut[current]);

        // Movimiento
        if (GetAsyncKeyState('W') & 0x8000) playerY--;
        if (GetAsyncKeyState('S') & 0x8000) playerY++;
        if (GetAsyncKeyState('A') & 0x8000) playerX--;
        if (GetAsyncKeyState('D') & 0x8000) playerX++;

        // Limita los bordes
        if (playerX < 0) playerX = 0;
        if (playerY < 0) playerY = 0;
        if (playerX >= MAP_WIDTH) playerX = MAP_WIDTH - 1;
        if (playerY >= MAP_HEIGHT) playerY = MAP_HEIGHT - 1;

        Sleep(80);

        // Cambia al otro buffer
        current = 1 - current;
    }

    return 0;
}
