#ifndef GAME_H
#define GAME_H

#include <iostream>   //para entrada y salida de datos.
#include <windows.h>  //para sleep y GetAsyncKeyState() para detectar teclas presionadas sin bloqueo (lectura de teclas en tiempo real).
#include <limits>     //Usas para limpiar el buffer de entrada cuando hay error en cin: cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include <cstdlib>    //rand(), srand() para inicializar la semilla de aleatoriedad y exit(0)  y size_t
#include <ctime>      //time(0) para obtener tiempo actual como semilla para srand.
#include <string>

#include "mapa.h"
#include "rlutil.h"


using namespace std;

struct Personaje {
    int hp;
    int hpMax;
    int dano;
    int nivel;
};

struct Enemigo {
    std::string nombre;
    int hp;
    int hpMax;
    int dano;
    std::string ascii;
};

struct Boss {
    std::string nombre;
    int hp;
    int hpMax;
    int dano;
    std::string ascii;
};

// Variables globales (extern para que no se definan múltiples veces)
extern Personaje jugador;
extern int playerX;
extern int playerY;


Personaje jugador = {100, 100, 10, 1};   //hp, hpMax, dano, nivel
int playerX = 10;                        //el mapa es una matriz de texto, esto ubica al jugador en la posición (10,10).
int playerY = 10;
bool keyHeld = false;                    //Indica si una tecla está mantenida presionada.

unsigned long lastMoveTime = 0;          //guarda el momento en que se movió por última vez el jugador.
const unsigned long repeatDelay = 80;    //cantidad mínima de tiempo (80 ms) entre movimientos si se deja la tecla presionada.

int enemigosDerrotados = 0;      
const int TOTAL_ENEMIGOS = 4;

bool puertaDesbloqueada = false;      //para desbloquear al boss
bool jefeDerrotado = false;


// Funciones
void mostrarHUD(){
    rlutil::locate(1, 1);
    rlutil::setColor(rlutil::WHITE);
    cout << "Nivel: " << jugador.nivel << "   Dano: " << jugador.dano << "   HP: " << jugador.hp << "    ";
}

    string barraHP(int hpActual, int hpMax, int largo = 15){
    if (hpActual < 0) hpActual = 0;                  // Asegura que no haya vida negativa. Si el personaje tiene -5 de vida, se corrige a 0 para que la barra no salga mal.
    int llenos = (hpActual * largo) / hpMax;         // Calcula cuántos caracteres deben estar "llenos" (con #)
    int vacios = largo - llenos;                     // Calcula cuántos caracteres deben estar "vacíos" (con `-`) para completar el tamaño total de la barra.

    //string(n, char) crea una cadena con n repeticiones del carácter char.
    return "[" + string(llenos, '#') + string(vacios, '-') + "]";           
}

bool iniciarCombate(){
 Enemigo enemigo = {
        "CYBER UNIT-X",      //Name
        50,                  //Hp
        50,                  //hpMax   
        8,                   //dano
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
    };                                                      //ascii

    rlutil::cls();
    cout << enemigo.nombre << " aparece!\n";
    Sleep(2000);
    
    
    //Limpiar entrada previa 
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    

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
        cout << ascii;

        rlutil::locate(1, 10);
        cout << "1. Atacar\n2. Curarse\n> ";
        int opcion;
        cin >> opcion;

        //Limpia un buffer (Zona temporal donde se almacena lo que el usuario escribe) 
        if (cin.fail()) {                 //Verifica si ocurrió un **error en la entrada** con cin
            cin.clear();                  //Limpia el estado de error del flujo de entrada (cin).
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    //**descarta los caracteres restantes** en la línea de entrada para "limpiar" el búfer
            cout << "Entrada invalida.";
            Sleep(1000);
            rlutil::cls();
            continue;        //Salta al **inicio del bucle** donde estás pidiendo la entrada, y **vuelve a intentarlo**.
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
            if (jugador.hp > jugador.hpMax) jugador.hp = jugador.hpMax;     //Si la vida del jugador se pasa del máximo, la limita al máximo. 
                                                                            //Evita que el jugador tenga más vida de la permitida.
            rlutil::locate (1,17);
            cout << "Te curaste " << heal << " puntos.\n";

        }
         else {
            rlutil::locate (1,14);
            cout << "Opción invalida.";
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
        cout << "\nHas derrotado a todos los enemigos! Una puerta secreta se ha abierto...\n";
        rlutil::setColor(rlutil::WHITE);
        Sleep(2500);   

        //Limpiar la linea del mensaje 
        rlutil::locate(1, VIEW_HEIGHT + 3);
        cout << string(80, ' ');        //Crea una cadena de 80 espacios en blanco (' '). (para borrar el mensaje)
}

        return true; //importante pq si no los enemigos no se eliminan del mapa y tambien se pone abajo pq si es arriba no se abre la puerta 
}

void iniciarCombateJefe(Boss jefe){
    
    rlutil::cls();
    cout << jefe.nombre << " aparece entre las sombras!\n\n";
    Sleep(2000);


    bool mensajeMitadMostrado = false; 


    while (jugador.hp > 0 && jefe.hp > 0) {

        rlutil::cls();
        rlutil::locate(1, 1);
        cout << "================== COMBATE FINAL ==================\n";
        rlutil::locate(1, 2);
        cout << "Jugador HP: " << jugador.hp << " " << barraHP(jugador.hp, jugador.hpMax) << "\n";
        rlutil::locate(1, 3);
        cout << jefe.nombre << " HP: " << jefe.hp << " " << barraHP(jefe.hp, jefe.hpMax) << "\n";
        rlutil::locate(1, 4);
        cout << "===================================================\n";

        // Mostrar ASCII del jefe
        int y = 6;
        string ascii = jefe.ascii;
        size_t pos = 0;

        while ((pos = ascii.find('\n')) != string::npos) {
            rlutil::locate(40, y++);
            cout << ascii.substr(0, pos);
            ascii.erase(0, pos + 1);
        }
        rlutil::locate(40, y);
        cout << ascii;

        // Opciones de jugador
        rlutil::locate(1,10);
        cout << "1. Atacar\n2. Curarse\n> ";
        int opcion;
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida.";
            Sleep(1000);
            continue;
        }

        rlutil::locate(1, 13);
        cout << "                                               ";

        if (opcion == 1) {
            int dmg = rand() % 10 + jugador.dano;
            jefe.hp -= dmg;
            rlutil::locate(1, 17);
            cout << "Le hiciste " << dmg << " de daño al jefe.\n";

        } 
        else if (opcion == 2) {
            int heal = rand() % 10 + 5;
            jugador.hp += heal;
            if (jugador.hp > jugador.hpMax) jugador.hp = jugador.hpMax;
            rlutil::locate(1, 17);
            cout << "Te curaste " << heal << " puntos.\n";

        }
        else {
            rlutil::locate(1, 14);
            cout << "Opción inválida.";
            Sleep(1000);
            continue;
        }

        Sleep(1000);

        if (jefe.hp > 0) {
            int edmg = rand() % jefe.dano + 5;
            jugador.hp -= edmg;
            rlutil::locate(1, 14);
            cout << "El jefe te golpea con " << edmg << " de dano.\n";
        }

        Sleep(1500);

        if (!mensajeMitadMostrado && jefe.hp <= jefe.hpMax / 2) {
            rlutil::locate(60, 3);  // Línea adecuada que no tape nada
            cout << jefe.nombre << ": \"!\"";
            mensajeMitadMostrado = true;

            Sleep(3000); // para dar tiempo a leerlo
        }

    }

    if (jugador.hp <= 0) {
        rlutil::cls();
        cout << "Has sido derrotado por el jefe. GAME OVER.\n";
        system("pause");
        exit(0);
    }

    rlutil::cls();  // LIMPIA toda la consola (para que no se vea el combate más)
    cout << "\n\n=====================================\n";
    cout << "FELICIDADES! Has derrotado al jefe final.\n";
    cout << "Redirigiendote al segundo nivel...\n";
    cout << "=====================================\n";
    jugador.nivel++;
    jugador.dano += 2;
    jugador.hp = jugador.hpMax;
    Sleep(4000);   
    system("pause");

}



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


#endif
