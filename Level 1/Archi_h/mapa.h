#ifndef MAPA_H
#define MAPA_H
 
#include "Structs.h"
#include "combate.h"


const int MAP_WIDTH = 80;    //ancho de mapa
const int MAP_HEIGHT = 20;   //alto de mapa
const int VIEW_WIDTH = 50;   //vista de ancho de mapa
const int VIEW_HEIGHT = 20;  //vista de alto de mapa

char mapa[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "################################################################################",
    "#......................~~~~~~.........T.............~~~~~...............~~~~~..#",
    "#...######..............~~~~~.............######..........######..............#",
    "#...#....#................~~~............##....##..............#..............#",
    "#...#....#...............TTT............##....##..............#..............T#",
    "#...######........................................####........#.........#####.#",
    "#..................................PPPPPPPPP.....#..#........#..............T.#",
    "#....T..........####..............P.........P.....#..#........####......E......#",
    "#...............#..#..............P.........P......................TTT.........#",
    "#.......~~~.....####....TTT.......P.........P.....................#####........#",
    "#.......~~~.......................P.........P........TTT.....................###",
    "#.......................E..........PPPPPPPPP.................................T#",
    "#.............TTT.........................................................#####",
    "#............................#####............................................#",
    "#....#####....................#T#.............................................#",
    "#....#T.#...............T.....###..................######.....................#",
    "#....###...........................................#....#...........E.........#",
    "#............E...............TTTT..................#....#.....................#",
    "#..................................................######.....................#",
    "################################################################################"
};

Personaje jugador = {100, 100, 10, 1};  //hp, hpMax, dano, nivel
int playerX = 10, playerY = 10;         //el mapa es una matriz de texto, esto ubica al jugador en la posición (10,10).
bool puertaDesbloqueada = false;        //para desbloquear al boss
bool jefeDerrotado = false;

void moverJugador(int dx, int dy){

    int newX = playerX + dx;
    int newY = playerY + dy;

    if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT)
        return;       //Evita que el jugador salga de los límites.

        char destino = mapa[newY][newX];  //Se obtiene el carácter que hay en el mapa en la posición nueva.

        if (destino == '#') return;

        if (destino == 'E') {
            if (iniciarCombate()) {
                mapa[newY][newX] = '.';\
            }
            return;      //Si no se pone ese return el jugador se estaria moviendo en la pelea 
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

        iniciarCombateJefe(jefeFinal);

        // para que todas las P desaparezcan después de la pelea
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (mapa[y][x] == 'P') mapa[y][x] = '.';
            }
        }

        // que el jugador se mueva a la nueva posición
        playerX = newX;
        playerY = newY;

        return;

        }
    }

    playerX = newX;
    playerY = newY;
    

}


void dibujarVista(){

    int offsetX = playerX - VIEW_WIDTH / 2;      //Calcula la **esquina superior izquierda** de la "vista"
    int offsetY = playerY - VIEW_HEIGHT / 2;

    for (int y = 0; y < VIEW_HEIGHT; y++) {      //Bucle doble que recorre cada celda de la vista, desde (0,0) hasta (VIEW_WIDTH, VIEW_HEIGHT).
        for (int x = 0; x < VIEW_WIDTH; x++) {
            int mapX = offsetX + x;              //Calcula la posición real del mapa que corresponde a la celda `(x, y)` dentro de la vista.
            int mapY = offsetY + y;

            rlutil::locate(x + 1, y + 2);

            if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
                rlutil::setColor(rlutil::WHITE);
                cout << ' ';
            } else if (mapX == playerX && mapY == playerY) {
                rlutil::setColor(rlutil::LIGHTRED);
                cout << '&';
                
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

bool keyHeld = false;                    //Indica si una tecla está mantenida presionada.
unsigned long lastMoveTime = 0;          //guarda el momento en que se movió por última vez el jugador.
const unsigned long repeatDelay = 80;    ////cantidad mínima de tiempo (80 ms) entre movimientos si se deja la tecla presionada.


void chequearMovimiento(){

    static int lastDir = 0;         //Se usa para recordar la última dirección presionada entre llamadas.
    unsigned long now = GetTickCount();  //Guarda el tiempo actual en milisegundos. (es de windows)

    auto mover = [&](int dir, int dx, int dy) {       //función lambda que toma una tecla (dir) Y un desplazamiento dx, dy (para mover al jugador)
        if (GetAsyncKeyState(dir) & 0x8000) {     //Verifica si la tecla **está siendo presionada** en este instante y 0x8000 es un flag que indica si la tecla está físicamente abajo.
        
            if (!keyHeld || lastDir != dir || now - lastMoveTime > repeatDelay) {   //controla si ya puedes mover al jugador de nuevo
                moverJugador(dx, dy);   //mueve al jugador en esa dirección
                lastMoveTime = now;     //actualiza el tiempo del último movimiento
                keyHeld = true;         //marca que la tecla está siendo mantenida
                lastDir = dir;          //guarda la dirección actual
            }
        } else if (lastDir == dir) {    //Si esa era la tecla que se estaba presionando antes, pero ahora ya no, se reinicia keyHeld.
            keyHeld = false;
        }
    };

    mover('W', 0, -1);
    mover('S', 0, 1);
    mover('A', -1, 0);
    mover('D', 1, 0);
}


void mostrarHUD(){

    rlutil::locate(1, 1);
    rlutil::setColor(rlutil::WHITE);
    cout << "Nivel: " << jugador.nivel << "   Dano: " << jugador.dano << "   HP: " << jugador.hp << "    ";
}


#endif

