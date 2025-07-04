#include "game.h"
#include <iostream>
#include <windows.h>
#include "rlutil.h"
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

Personaje jugador = {100, 100, 10, 1};   //hp, hpMax, dano, nivel
int playerX = 10;
int playerY = 10;
bool keyHeld = false;
unsigned long lastMoveTime = 0;
const unsigned long repeatDelay = 80;

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

void mostrarHUD() {
    rlutil::locate(1, 1);
    rlutil::setColor(rlutil::WHITE);
    cout << "Nivel: " << jugador.nivel << "   Dano: " << jugador.dano << "   HP: " << jugador.hp << "    ";
}

string barraHP(int hpActual, int hpMax, int largo) {
    if (hpActual < 0) hpActual = 0;
    int llenos = (hpActual * largo) / hpMax;
    int vacios = largo - llenos;
    return "[" + string(llenos, '#') + string(vacios, '-') + "]";
}

bool iniciarCombate() {

    Enemigo enemigo = {    //primer enemigo es del struct  y el segundo enemigo es la variable que se esta creando
        "CYBER UNIT-X",  //nombre
        50,     // hp
        50,     // hpMax
        8,      //dano
       R"(          ____    
        .'* *.'
     __/_*___*_\
    / _________ \
   | /         \ |
   ||  0   0    || 
   ||     ^     ||     
   |  \___|___/ |/
    \  \_____/  /
     \_________/
     _|_____|_
  .-' ||||| ||`-.
 /    ||||| ||   \
|     ||||| ||    |
\     ||||| ||    /
 '-.__||||_|_.-'
      |  |  |
     [===[ ]===]
      |_| |_|
     (__) (__))"
    };


    rlutil::cls();
    cout << enemigo.nombre << " aparece!\n";

    while (jugador.hp > 0 && enemigo.hp > 0) {
        rlutil::locate(1, 1);
        cout << "=============================================";
        rlutil::locate(1, 2);
        cout << "Jugador HP: " << jugador.hp << " " << barraHP(jugador.hp, jugador.hpMax);
        rlutil::locate(1, 3);
        cout << enemigo.nombre << " HP: " << enemigo.hp << " " << barraHP(enemigo.hp, enemigo.hpMax);
        rlutil::locate(1, 4);
        cout << "=============================================";


        int y = 6;                                    //El ascii se imprimira en la linea 6 en el eje y
        string ascii = enemigo.ascii;                 //mandar a llamar la variable de ascii
        size_t pos = 0;                               //variable pos que se usará para encontrar las posiciones de los saltos de línea (\n)

        // npos se usa para indicar que no se encontró nada durante una operación de búsqueda en un std::string

        while ((pos = ascii.find('\n')) != string::npos) {    //ascii.find('\n') busca la posición del primer salto de línea.
            rlutil::locate(40, y++);                          //rlutil::locate(40, y++) posiciona el cursor en la columna 40 y fila y, e imprime esa línea.  
            cout << ascii.substr(0, pos);                     //ascii.substr(0, pos) obtiene el contenido antes del salto de línea (una línea de dibujo).  
            ascii.erase(0, pos + 1);                          //borra esa parte impresa más el \n con ascii.erase(0, pos + 1); para seguir con la siguiente línea.
  
        }
       
        rlutil::locate(40, y);                                
        cout << ascii;                                        //imprime la última línea restante del ASCII  

        rlutil::locate(1, 10);
        cout << "1. Atacar\n2. Curarse\n> ";
        int opcion;
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida.";
            Sleep(1000);
            rlutil::cls();
            continue;
        }

        rlutil::locate(1, 13);
        cout << "                                               ";

        if (opcion == 1) {
            int dmg = rand() % 10 + jugador.dano;
            enemigo.hp -= dmg;
            rlutil::locate (75,14);
            cout << "Atacaste al enemigo por " << dmg << " de dano.\n";

        } 
        else if (opcion == 2) {
            int heal = rand() % 10 + 5;
            jugador.hp += heal;
            if (jugador.hp > jugador.hpMax) jugador.hp = jugador.hpMax;
            rlutil::locate (75,14);
            cout << "Te curaste " << heal << " puntos.\n";
        }
         else {
            rlutil::locate (1,14);
            cout << "Opción inválida.";
            Sleep(1000);
            rlutil::cls();
            continue;
        }

        Sleep(1000);

        if (enemigo.hp > 0) {
            int edmg = rand() % enemigo.dano + 3;
            jugador.hp -= edmg;
            rlutil::locate(1, 14);
            cout << "El enemigo te golpea por " << edmg << " de dano.";
        }

        Sleep(1000);
        rlutil::cls();
    }

    if (jugador.hp <= 0) {
        rlutil::cls();
        cout << "Has sido derrotado. GAME OVER.\n";
        exit(0);
    }

    cout << "\nVenciste al enemigo!\n";
    jugador.nivel++;
    jugador.dano += 2;
    jugador.hp += 10;
    if (jugador.hp > jugador.hpMax) jugador.hp = jugador.hpMax;
    Sleep(1500);
    return true;
}

void moverJugador(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT) {
        char destino = mapa[newY][newX];
        if (destino == '#') return;

        if (destino == 'E') {
            if (iniciarCombate()) {
                mapa[newY][newX] = '.';
            }
        }

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

            rlutil::locate(x + 1, y + 2);

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
    unsigned long now = GetTickCount();

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


    
    srand(time(0));
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

