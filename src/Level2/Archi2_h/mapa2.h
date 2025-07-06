#ifndef MAPA_H2
#define MAPA_H2

#include "../../Level1/Archi_h/Structs.h"
#include "combate2.h"
#include "temporal2.h"

namespace Nivel2{

const int MAP_WIDTH2 = 80;
const int MAP_HEIGHT2 = 20;
const int VIEW_WIDTH2 = 50;
const int VIEW_HEIGHT2 = 20;

char map[MAP_HEIGHT2][MAP_WIDTH2 + 1] = {
    "################################################################################",
    "#......................~~~~~~.........T............######~~~~~~~~~~~~~~~~~~~~~#",
    "#...######..............~~~~~.............######...######~~~~~~~~~~~~~~~~~~~~~#",
    "#...######.........#......~~~...........##.....##..######~~~~~~~~~~~~~~~~~~~~~#",
    "#...######........##.....TTT............E...N..##..######....................##",
    "#...######.......#.#............#.......##.....##..######..................####",
    "#...............#..#...........#.#........######...######...............####..#",
    "#....T...........#.#..........#...#................######.............####..PPP#",
    "#.................##............#..........T.........................####..P...#",
    "#.......~~~........#....TTT................T.........H....................P..PP#",
    "#.......~~~................................T..............................P..PP#",
    "#..........................................T.........................####..P...#",
    "#.............TTT..................................######.............####..PPP#",
    "#............................#####.................######...............####..#",
    "#....#####....................#T#.......######.....######..................####",
    "#....#T.#...............T.....###.......#....#.....######....................##",
    "#....###................................#....#.....######~~~~~~~~~~~~~~~~~~~~~#",
    "#............E...............TTTT.......######.....######~~~~~~~~~~~~~~~~~~~~~#",
    "#..................................................######~~~~~~~~~~~~~~~~~~~~~#",
    "################################################################################"
};

Character player2 = {100, 100, 20, 6};  //hp, hpMax, dano, nivel
int playerX2 = 10, playerY2 = 10;         //el mapa es una matriz de texto, esto ubica al jugador en la posición (10,10).
bool unlockGate2 = false;        //para desbloquear al boss
bool bossDefeated2 = false;

void movePlayer(int dx, int dy){

    int newX = playerX2 + dx;
    int newY = playerY2 + dy;

    if (newX < 0 || newX >= MAP_WIDTH2 || newY < 0 || newY >= MAP_HEIGHT2)
        return;       //Evita que el jugador salga de los límites.

        char destiny = map[newY][newX];  //Se obtiene el carácter que hay en el mapa en la posición nueva.

        if (destiny == '#') return;

        if (destiny == '~') return;  //No se puede mover al agua

        if(destiny == 'N'){
            // Limpiar el buffer de teclas antes de entrar al menú
            while (kbhit()) getch();
            
            rlutil::cls(); // Limpiar toda la pantalla
            rlutil::setColor(rlutil::CYAN);
            rlutil::locate(10, 5);
            cout << "==================== NPC CONVERSATION ====================";
            rlutil::setColor(rlutil::WHITE);
            
            rlutil::locate(10, 7);
            cout << "Mysterious NPC: \"Have you ever heard about Draven?\"";
            
            string options[] = {"Yes, I know him.", "No, who is he?"};
            int select = 0;
            
            while (true) {
                // Mostrar menú
                for (int i = 0; i < 2; i++) {
                    rlutil::locate(10, 9 + i);
                    if (i == select) {
                        rlutil::setColor(rlutil::YELLOW);
                        cout << "> " << options[i];
                    } else {
                        rlutil::setColor(rlutil::WHITE);
                        cout << "  " << options[i];
                    }
                }
                
                int key = getkey();
                while (kbhit()) getch(); // Limpiar teclas residuales
                
                if (key == rlutil::KEY_UP)
                    select = (select - 1 + 2) % 2;
                else if (key == rlutil::KEY_DOWN)
                    select = (select + 1) % 2;
                else if (key == rlutil::KEY_ENTER)
                    break;
            }
            
            rlutil::cls(); // Limpiar para mostrar respuesta
            rlutil::setColor(rlutil::CYAN);
            rlutil::locate(10, 5);
            cout << "==================== NPC CONVERSATION ====================";
            rlutil::setColor(rlutil::WHITE);
            
            if (select == 0) { // "Yes, I know him."
                rlutil::locate(10, 7);
                cout << "Mysterious NPC: \"Good! Then you know how dangerous he is.\"";
                rlutil::locate(10, 9);
                cout << "\"You must defeat him to save our city from destruction!\"";
            } else { // "No, who is he?"
                rlutil::locate(10, 7);
                cout << "Mysterious NPC: \"Draven is the leader of ZORG PRIME corporation,\"";
                rlutil::locate(10, 9);
                cout << "\"a powerful and dangerous organization that controls this zone.\"";
                rlutil::locate(10, 11);
                cout << "\"He is responsible for the destruction of our city.\"";
                rlutil::locate(10, 13);
                cout << "\"You must defeat him to save everyone!\"";
            }
            
            rlutil::locate(10, 16);
            rlutil::setColor(rlutil::YELLOW);
            cout << "Press any key to continue...";
            rlutil::setColor(rlutil::WHITE);
            
            // Limpiar teclas residuales antes de esperar
            while (kbhit()) getch();
            getch(); // Esperar a que el jugador presione una tecla
            
            // Limpiar completamente la pantalla antes de volver al juego
            rlutil::cls();
            
            return; // No mover al jugador a la posición del NPC
        }


        if (destiny == 'H')
        {
            player2.hp += player2.hpMax / 2;  //Curar al jugador
            map[newY][newX] = '.';      //Eliminar el punto de curación
            if (player2.hp > player2.hpMax) player2.hp = player2.hpMax; //No curar más de lo máximo
        }

        if (destiny == 'E') {
            if (startCombat()) {
                map[newY][newX] = '.';\
            }
            return;      //Si no se pone ese return el jugador se estaria moviendo en la pelea 
        } 

    if (destiny == 'P') {

        if (!unlockGate2) {
            rlutil::locate(1, VIEW_HEIGHT2 + 3);
            cout << "The door is locked. Defeat all the enemies first.";
            Sleep(1500);
            rlutil::locate(1, VIEW_HEIGHT2 + 3);
            cout << string(80, ' ');  // limpia el mensaje
            return;

    } else if (!bossDefeated2) {
        bossFight(secondBoss);
        
        // Solo marcar como derrotado si realmente cambió de nivel
        if (::actualLevel == 3) {
            bossDefeated2 = true;
        }
        
        return;
        }
    }

    playerX2 = newX;
    playerY2 = newY;
    

}


void drawView_L2(){

    int offsetX = playerX2 - VIEW_WIDTH2 / 2;      //Calcula la **esquina superior izquierda** de la "vista"
    int offsetY = playerY2 - VIEW_HEIGHT2 / 2;

    for (int y = 0; y < VIEW_HEIGHT2; y++) {      //Bucle doble que recorre cada celda de la vista, desde (0,0) hasta (VIEW_WIDTH, VIEW_HEIGHT).
        for (int x = 0; x < VIEW_WIDTH2; x++) {
            int mapX = offsetX + x;              //Calcula la posición real del mapa que corresponde a la celda `(x, y)` dentro de la vista.
            int mapY = offsetY + y;

            rlutil::locate(x + 1, y + 2);

            if (mapX < 0 || mapX >= MAP_WIDTH2 || mapY < 0 || mapY >= MAP_HEIGHT2) {
                rlutil::setColor(rlutil::WHITE);
                cout << ' ';
            } else if (mapX == playerX2 && mapY == playerY2) {
                rlutil::setColor(rlutil::LIGHTRED);
                cout << '&';
                
            } 

        else {
        char tile = map[mapY][mapX];

        switch (tile) {
        case '#': rlutil::setColor(rlutil::GREY); break;
        case '~': rlutil::setColor(rlutil::CYAN); break;
        case 'T': rlutil::setColor(rlutil::GREEN); break;
        case '.': rlutil::setColor(rlutil::BROWN); break;
        case 'E': rlutil::setColor(rlutil::LIGHTBLUE); break;
        case 'H': rlutil::setColor(rlutil::YELLOW); break;
        case 'P':
        if (unlockGate2)
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


void checkMovement_L2(){

    static int lastDir = 0;         //Se usa para recordar la última dirección presionada entre llamadas.
    unsigned long now = GetTickCount();  //Guarda el tiempo actual en milisegundos. (es de windows)

    auto move = [&](int dir, int dx, int dy) {       //función lambda que toma una tecla (dir) Y un desplazamiento dx, dy (para mover al jugador)
        if (GetAsyncKeyState(dir) & 0x8000) {     //Verifica si la tecla **está siendo presionada** en este instante y 0x8000 es un flag que indica si la tecla está físicamente abajo.
        
            if (!keyHeld || lastDir != dir || now - lastMoveTime > repeatDelay) {   //controla si ya puedes mover al jugador de nuevo
                movePlayer(dx, dy);   //mueve al jugador en esa dirección
                lastMoveTime = now;     //actualiza el tiempo del último movimiento
                keyHeld = true;         //marca que la tecla está siendo mantenida
                lastDir = dir;          //guarda la dirección actual
            }
        } else if (lastDir == dir) {    //Si esa era la tecla que se estaba presionando antes, pero ahora ya no, se reinicia keyHeld.
            keyHeld = false;
        }
    };

    move('W', 0, -1);
    move('S', 0, 1);
    move('A', -1, 0);
    move('D', 1, 0);
}


void showHUD_L2(){

    rlutil::locate(1, 1);
    rlutil::setColor(rlutil::WHITE);
    cout << "XP Level: " << player2.level << "   Damage: " << player2.dmg << "   HP: " << player2.hp << "    ";

    }

}

#endif