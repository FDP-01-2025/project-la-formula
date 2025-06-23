#include <iostream>   //para entrada y salida de datos.
#include <windows.h>  //para sleep y GetAsyncKeyState() para detectar teclas presionadas sin bloqueo (lectura de teclas en tiempo real).
#include <limits>     //Usas para limpiar el buffer de entrada cuando hay error en cin: cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include <cstdlib>    //rand(), srand() para inicializar la semilla de aleatoriedad y exit(0) 
#include <ctime>      //time(0) para obtener tiempo actual como semilla para srand.
#include "Archi_h/mapa.h"
#include "Archi_h/boss.h"
#include "Archi_h/game.h"
#include "Archi_h/rlutil.h"

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
    
    
    //Limpiar entrada previa 
   /* cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    */

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

        } 
        else if (opcion == 2) {
            int heal = rand() % 10 + 5;
            jugador.hp += heal;
            if (jugador.hp > jugador.hpMax) jugador.hp = jugador.hpMax;
            rlutil::locate (1,17);
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
        system("pause");  // Espera a que el jugador presione una tecla
        exit(0);     //Este se usa para terminar el programa de un solo, puede ser utilizado para una opcion salir del juego
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
}

        return true; //importante pq si no los enemigos no se eliminan del mapa y tambien se pone abajo pq si es arriba no se abre la puerta 
}

void moverJugador(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT)
        return;

        char destino = mapa[newY][newX];

        if (destino == '#') return;

        if (destino == 'E') {
            if (iniciarCombate()) {
                mapa[newY][newX] = '.';\
            }
            return;
        } 

    if (destino == 'P') {

        if (!puertaDesbloqueada) {
            rlutil::locate(1, VIEW_HEIGHT + 3);
            cout << "La puerta está cerrada. Derrota a todos los enemigos primero.";
            Sleep(1500);
            rlutil::locate(1, VIEW_HEIGHT + 3);
            cout << string(80, ' ');  // limpia el mensaje
            return;

    } else if (!jefeDerrotado) {
        jefeDerrotado = true;
        

     
        Boss jefeFinal = {     //declaracion de variable "jefefinal"
            "ZORG PRIME",
            120,
            120,
            15,
            R"(
                    dS$$S$S$S$S$S$S$$Sb                    
                   :$$S^S$S$S$S$S$S^S$$;                   
                   SSP   `^$S$S$^'   TSS                   
                   $$       `"'       $$                   
                  _SS ,-           -  SS_                  
                 :-.|  _    - .-   _  |.-;                 
                 :\(; ' "-._.'._.-" ` |)/;                 
                  \`|  , o       o .  |'/                  
                   ":     -'   `-     ;"                   
                     ;.              :                  
                     : `    ._.    ' ;                     
                   .sSb   ._____.   dSs.                   
                _.d8dSSb.   ._.   .SSbT8b._                
            _.oOPd88SSSS T.     .P SSSS888OOo.             
        _.mMMOOPd888SSSSb TSqqqSP dSSSS88OMOOOMm._         
     .oOMMMOMOOM8O8OSSSSSb TSSSP dSSSSS8OOMMOOMMOOOo._     
   .OOMMOOOMMOOMOOOO  "^SSSTSSP dSSS^"OOOOMMOOMMMOOMMMb.   
  dOOOMMMOMMOOOMOOOO      "^SSSS^"   :OOO8MMMOOMMOOMMOMMb  
 :MMMOOMMOMMOOMMO8OS         `P      8O8OPdMMOOMMOMMOMMMM; 
 MMMMOOMMMMMOOMbTO8S;               :8888MMMMMOMMOMMOMMMMM 
 OMMMMOOMMMMOOOMMOOOS        S     :O8OPdMOMMMOMOMMOOMMMMO 
:OMMMMOOMMOMMOOMbTObTb.     :S;   .PdOPdMOOMMMMMOMMOMMMMMO;
MOOMMMMOMMOMMOOMMMOObTSSg._.SSS._.PdOPdMOOMMMMOMMMMOMMMMOOM )"
        };


        iniciarCombateJefe(jefeFinal);

        // para que todas las P desaparezcan después de la pelea
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (mapa[y][x] == 'P') mapa[y][x] = '.';
            }
        }

        // Y que el jugador se mueva a la nueva posición si quieres
        playerX = newX;
        playerY = newY;

        return;

        }
    }

    playerX = newX;
    playerY = newY;
    
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



int main() {
    srand(time(0));       //inicializa el generador de números aleatorios con la hora actual como semilla. Esto para los ataques/curaciones
    rlutil::hidecursor(); //inicializa el generador de números aleatorios con la hora actual como semilla.
    system("cls");        //Limpia toda la consola al iniciar el juego.

    while (true) {        //bucle principal del juego, se repite para siempre hasta que el juego termine o el jugador muera (true nunca cambia, a no ser que haya un break dentro del while)
        mostrarHUD();     
        dibujarVista();         //Mandar a llamar las funciones void.
        chequearMovimiento();
        Sleep(30);        //Espera 30 milisegundos para que la CPU no se sobrecargue y los movimientos sean suaves
    }

    return 0;
}
