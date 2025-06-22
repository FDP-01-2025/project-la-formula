#include "game.h"
#include <iostream>
#include <windows.h>
#include "rlutil.h"
#include <limits>
#include <cstdlib>
#include <ctime>
#include "mapa.h"

using namespace std;

Personaje jugador = {100, 100, 10, 1};   //hp, hpMax, dano, nivel
int playerX = 10;
int playerY = 10;
bool keyHeld = false;
unsigned long lastMoveTime = 0;
const unsigned long repeatDelay = 80;

int enemigosDerrotados = 0;      
const int TOTAL_ENEMIGOS = 4;

bool puertaDesbloqueada = false;      //para desbloquear al boss
bool jefeDerrotado = false;

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


bool iniciarCombateJefe();

bool iniciarCombate() {
    Enemigo enemigo = {
        "CYBER UNIT-X",
        50,
        50,
        8,
       R"(    
                   <((((((\\\
                   /      . }\
                   ;--..--._|}
(\                 '--/\--'  )
 \\                | '-'  :'|
  \\               . -==- .-|
   \\               \.__.'   \--._
   [\\          __.--|       //  _/'--.
   \ \\       .'-._ ('-----'/ __/      \
    \ \\     /   __>|      | '--.       |
     \ \\   |   \   |     /    /       /
      \ '\ /     \  |     |  _/       /
       \  \       \ |     | /        /
        \  \      \        /        / )"
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

        int y = 6;
        string ascii = enemigo.ascii;
        size_t pos = 0;

        while ((pos = ascii.find('\n')) != string::npos) {
            rlutil::locate(40, y++);
            cout << ascii.substr(0, pos);
            ascii.erase(0, pos + 1);
        }
        rlutil::locate(40, y);
        cout << ascii;

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
            rlutil::locate (1,17);
            cout << "Atacaste al enemigo por " << dmg << " de dano.\n";
        } else if (opcion == 2) {
            int heal = rand() % 10 + 5;
            jugador.hp += heal;
            if (jugador.hp > jugador.hpMax) jugador.hp = jugador.hpMax;
            rlutil::locate (1,17);
            cout << "Te curaste " << heal << " puntos.\n";
        } else {
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
    enemigosDerrotados++;

    cout << "Enemigos restantes: " << TOTAL_ENEMIGOS - enemigosDerrotados << endl;
    Sleep(2000); // para poder ver el mensaje antes de que se limpie

    if (!puertaDesbloqueada && enemigosDerrotados >= TOTAL_ENEMIGOS) {
        puertaDesbloqueada = true;
        rlutil::locate(1,VIEW_HEIGHT + 3);
        rlutil::setColor(rlutil::YELLOW);
        cout << "\n¡Has derrotado a todos los enemigos! Una puerta secreta se ha abierto...\n";
        rlutil::setColor(rlutil::WHITE);
        Sleep(2500);   

        //Limpiar la linea del mensaje 
        rlutil::locate(1, VIEW_HEIGHT + 3);
        cout << string(80, ' ');

         // abrir la puerta: cambiar los 'O' por 'P'
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (mapa[y][x] == 'O') {
                mapa[y][x] = 'P';
            }
        }
    }
}
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
        if (destino == 'P') {

            if (!puertaDesbloqueada) {
        // Puerta bloqueada, no dejar pasar
        rlutil::locate(1, VIEW_HEIGHT + 3);
        cout << "La puerta esta cerrada. Derrota a todos los enemigos primero.";
        Sleep(1500);
        rlutil::locate(1, VIEW_HEIGHT + 3);
        cout << string(80, ' ');
        return;
    } else if (!jefeDerrotado) {
        // Puerta abierta y aún no luchaste contra el jefe
        jefeDerrotado = true;
        iniciarCombateJefe();
        mapa[newY][newX] = '.';  // Si quieres que desaparezca después
    }
}

       else if (destino == 'P') {
            if (!puertaDesbloqueada) {
              rlutil::locate(1, VIEW_HEIGHT + 3);
              cout << "La puerta esta cerrada. Derrota a todos los enemigos primero.";
              Sleep(800);
        
    } else if (!jefeDerrotado) {
        jefeDerrotado = true;
        iniciarCombateJefe();
        // Si quieres que todas las P desaparezcan:
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (mapa[y][x] == 'P') mapa[y][x] = '.';
            }
        }
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
                
            } 

         else {
        char tile = mapa[mapY][mapX];

        switch (tile) {
        case '#': rlutil::setColor(rlutil::GREY); break;
        case '~': rlutil::setColor(rlutil::CYAN); break;
        case 'T': rlutil::setColor(rlutil::GREEN); break;
        case '.': rlutil::setColor(rlutil::BROWN); break;
        case 'E': rlutil::setColor(rlutil::LIGHTBLUE); break;
        case 'P':
        if (puertaDesbloqueada)
        rlutil::setColor(rlutil::MAGENTA);

        else
        rlutil::setColor(rlutil::RED);
        break;

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

bool iniciarCombateJefe() {
    rlutil::cls();
    cout << "\n\n¡El jefe final aparece entre las sombras!\n";
    Sleep(2000);
    cout << "Pero aún no se ha implementado el combate con el jefe.\n";
    Sleep(2000);
    return true;
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
