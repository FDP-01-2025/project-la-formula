#ifndef COMBATE_H
#define COMBATE_H

#include <limits>  //Usas para limpiar el buffer de entrada cuando hay error en cin: cin.ignore(numeric_limits<streamsize>::max(), '\n');

#include "variables.h"
#include "rlutil.h"
#include "Structs.h"
#include "boss.h"
#include "mapa.h"
#include "temporal.h"

int enemigosDerrotados = 0;
const int TOTAL_ENEMIGOS = 4;


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
    /*cin.clear();
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

    puertaDesbloqueada;

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

    Boss jefeFinal;

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  //limits
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
            cout << jefe.nombre << ": \"Te matare!!!\"";
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


#endif