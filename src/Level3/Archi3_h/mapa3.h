#ifndef MAPA_H3
#define MAPA_H3

#include "../../Level1/Archi_h/Structs.h"
#include "combate3.h"
#include "temporal3.h"
#include "../../mainmenu.h"

namespace Nivel3{

const int MAP_WIDTH3 = 80;
const int MAP_HEIGHT3 = 20;
const int VIEW_WIDTH3 = 50;
const int VIEW_HEIGHT3 = 20;

char map[MAP_HEIGHT3][MAP_WIDTH3 + 1] = {
    "################################################################################",
    ".##############################################################################",
    "#####~~~~~~~~~~~~~~##...##.TTTTTT.##.....##.....##.....##~~~~~~~~~~~~~~~~~~~~~#",
    "###~~~~~~~~~~~~~~~~##....##.TTTT.##......##.....##.....##~~~~~~~~~~~~~~~~~~~~~#",
    "#####################.....##.TT.##.......##..E..##......##############~~~~~~~~#",
    "#..................##......##..##........##.....##...................#~~~~~~~~#",
    "###................##....................###...###...................#~~~~~~~~#",
    "####...............##................................................#~~~~~~~~#",
    "#####..............##................................................###########",
    "#............................................................................PP#",
    "#...............................................................E............PP#",
    "#####..............##................................................###########",
    "####...............##................................................#~~~~~~~~#",
    "###................##....###....###......###...###...................#~~~~~~~~#",
    "#..................##...###......###.....##.....##...................#~~~~~~~~#",
    "#####################..##.....E....##....##..H..##......##############~~~~~~~~#",
    "###~~~~~~~~~~~~~~~~##..##..........##....##.....##..N..#~~~~~~~~~~~~~~~~~~~~~~#",
    "#####~~~~~~~~~~~~~~##..##..........##....##.....##.....#~~~~~~~~~~~~~~~~~~~~~~#",
    ".##############################################################################",
    "################################################################################"
};

Character player3 = {100, 100, 26, 9};  //hp, hpMax, dano, nivel
int playerX3 = 10, playerY3 = 10;         //el mapa es una matriz de texto, esto ubica al jugador en la posición (10,10).
bool unlockGate3 = false;        //para desbloquear al boss
bool bossDefeated3 = false;

void movePlayer(int dx, int dy){

    int newX = playerX3 + dx;
    int newY = playerY3 + dy;

    if (newX < 0 || newX >= MAP_WIDTH3 || newY < 0 || newY >= MAP_HEIGHT3)
        return;       //Evita que el jugador salga de los límites.

        char destiny = map[newY][newX];  //Se obtiene el carácter que hay en el mapa en la posición nueva.

        if (destiny == '#') return;

        if (destiny == '~') return;  //No se puede mover al agua

        if (destiny ==  'N'){
            // Limpiar el buffer de teclas antes de entrar al menú
            while (kbhit()) getch();
            
            rlutil::cls(); // Limpiar toda la pantalla
            rlutil::setColor(rlutil::CYAN);
            rlutil::locate(10, 5);
            cout << "==================== NPC CONVERSATION ====================";
            rlutil::setColor(rlutil::WHITE);
            
            rlutil::locate(10, 7);
            cout << "Mysterious NPC: \"Have you ever heard about Adam Smasher?\"";
            
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
                cout << "Mysterious NPC: \"Then... go somewhere else...\"";
                rlutil::locate(10, 9);
                cout << "\"You must defeat him to save our city from destruction!\"";
            } else { // "No, who is he?"
                rlutil::locate(10, 7);
                cout << "Mysterious NPC: \"He is the D-E-V-I-L,\"";
                rlutil::locate(10, 9);
                cout << "\"He is the leader of Arasaka, definitly he will kill you.\"";
                rlutil::locate(10, 11);
                cout << "\"No one can beat him, and someone like you cant fight with him.\"";
                rlutil::locate(10, 13);
                cout << "\"You must go somewhere else...\"";
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

        if (destiny == 'H') {
            player3.hp += player3.hpMax / 2;  //Curar al jugador
            map[newY][newX] = '.';      //Eliminar el punto de curación
            if (player3.hp > player3.hpMax) player3.hp = player3.hpMax; //No curar más de lo máximo
        }

        if (destiny == 'E') {
            if (startCombat()) {
                map[newY][newX] = '.';\
            }
            return;      //Si no se pone ese return el jugador se estaria moviendo en la pelea 
        } 

    if (destiny == 'P') {

        if (!unlockGate3) {
            rlutil::locate(1, VIEW_HEIGHT3 + 3);
            cout << "The door is locked. Defeat all the enemies first.";
            Sleep(1500);
            rlutil::locate(1, VIEW_HEIGHT3 + 3);
            cout << string(80, ' ');  // limpia el mensaje
            return;

    } else if (!bossDefeated3) {
        bossFight(thirdBoss);
        // Para el nivel 3, si llegamos aquí es porque el jugador huyó
        // El boss no se marca como derrotado
        return;
        }
    }

    playerX3 = newX;
    playerY3 = newY;
    

}


void drawView_L3(){

    int offsetX = playerX3 - VIEW_WIDTH3 / 2;      //Calcula la **esquina superior izquierda** de la "vista"
    int offsetY = playerY3 - VIEW_HEIGHT3 / 2;

    for (int y = 0; y < VIEW_HEIGHT3; y++) {      //Bucle doble que recorre cada celda de la vista, desde (0,0) hasta (VIEW_WIDTH, VIEW_HEIGHT).
        for (int x = 0; x < VIEW_WIDTH3; x++) {
            int mapX = offsetX + x;              //Calcula la posición real del mapa que corresponde a la celda `(x, y)` dentro de la vista.
            int mapY = offsetY + y;

            rlutil::locate(x + 1, y + 2);

            if (mapX < 0 || mapX >= MAP_WIDTH3 || mapY < 0 || mapY >= MAP_HEIGHT3) {
                rlutil::setColor(rlutil::WHITE);
                cout << ' ';
            } else if (mapX == playerX3 && mapY == playerY3) {
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
        case 'N': rlutil::setColor(rlutil::BLUE); break;
        case 'P':
        if (unlockGate3)
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


void checkMovement_L3(){

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


void showHUD_L3(){

    rlutil::locate(1, 1);
    rlutil::setColor(rlutil::LIGHTCYAN);
    cout << "Player: " << MainMenu::playerName << "  ";
    rlutil::setColor(rlutil::WHITE);
    cout << "XP Level: " << player3.level << "   Damage: " << player3.dmg << "   HP: " << player3.hp << "    ";

}

}

#endif