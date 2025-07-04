#ifndef COMBATE_H
#define COMBATE_H

#include <limits> //Usas para limpiar el buffer de entrada cuando hay error en cin: cin.ignore(numeric_limits<streamsize>::max(), '\n');

#include "variables.h"
#include "rlutil.h"
#include "Structs.h"
#include "boss.h"
#include "temporal.h"

using namespace rlutil;

namespace Nivel1{

int defeatedEnemies = 0;
const int TOTAL_ENEMIES = 4;


int attackRoulette() {
    int position = 0;
    const int max = 30;

    while (!kbhit()) {
        rlutil::locate(6, 12);
        cout << "[";
        for (int i = 0; i < max; i++) {
            if (i == position)
                setColor(rlutil::YELLOW), cout << "|";
            else if (i >= 13 && i <= 16)
                setColor(rlutil::GREEN), cout << "=";
            else if ((i >= 10 && i <= 12) || (i >= 17 && i <= 19))
                setColor(rlutil::YELLOW), cout << "=";
            else
                setColor(rlutil::RED), cout << "-";
        }
        setColor(rlutil::WHITE);
        cout << "]";

        Sleep(50);
        position = (position + 1) % max;
    }

        getch(); // solo consume la tecla sin esperar más

    //DANO

    if (position >= 13 && position <= 16)
        return rand() % player.dmg + 25; // verde
    else if ((position >= 10 && position <= 12) || (position >= 17 && position <= 19))
        return rand() % player.dmg + 15; // amarillo
    else
        return rand() % player.dmg + 5;  // rojo
}



bool startCombat()
{

    Enemy enemy = {
        "CYBER UNIT-X", // Name
        50,             // Hp
        50,             // hpMax
        8,              // dano
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
        \  \      \        /        / )"}; // ascii

    rlutil::cls();
    cout << enemy.name << " appears!\n";
    Sleep(2000);


    while (player.hp > 0 && enemy.hp > 0)
    {
        cls();
        setColor(rlutil::WHITE);
        rlutil::locate(1, 1);
        cout << "=============================================";
        HPbar(2, 2, player.hp, player.hpMax, "player");
        HPbar(2, 3, enemy.hp, enemy.hpMax, enemy.name);
        rlutil::locate(1, 4);
        cout << "=============================================";

        int y = 6;                    // El ascii se imprimira en la linea 6 en el eje y
        string ascii = enemy.ascii; // mandar a llamar la variable de ascii
        size_t pos = 0;               // variable pos que se usará para encontrar las posiciones de los saltos de línea (\n)

        // npos se usa para indicar que no se encontró nada durante una operación de búsqueda en un std::string

        while ((pos = ascii.find('\n')) != string::npos)
        {                                 // ascii.find('\n') busca la posición del primer salto de línea.
            rlutil::locate(50, y++);      // rlutil::locate(40, y++) posiciona el cursor en la columna 40 y fila y, e imprime esa línea.
            cout << ascii.substr(0, pos); // ascii.substr(0, pos) obtiene el contenido antes del salto de línea (una línea de dibujo).
            ascii.erase(0, pos + 1);      // borra esa parte impresa más el \n con ascii.erase(0, pos + 1); para seguir con la siguiente línea.
        }

        rlutil::locate(50, y);
        cout << ascii;

        string options[] = {"Atack", "Defend", "Run"};
        int select = 0;

        while (kbhit()) getch();   //  Limpiar teclas residuales ANTES de entrar al menú

        while (true) {
            // Mostrar menú
            for (int i = 0; i < 3; i++) {
                locate(10, 16 + i);
                if (i == select) {
                    setColor(rlutil::YELLOW);
                    cout << "> " << options[i];
                } else {
                    setColor(rlutil::WHITE);
                    cout << "  " << options[i];
                }
            }

            int key = getkey();       // Captura la tecla
            while (kbhit()) getch();  // Esto previene repeticiones al mantener presionada una tecla
            Sleep(150); // da tiempo a que se suelte la tecla

            if (key == rlutil::KEY_UP)
                select = (select + 2) % 3;
            else if (key == rlutil::KEY_DOWN)
                select = (select + 1) % 3;
            else if (key == rlutil::KEY_ENTER)
                break;
        }

         if (select == 0) { // Atacar
            
            locate(10, 10);
            cout << "Press ENTER!!";
            int damage = attackRoulette();
            enemy.hp -= damage;
            if (enemy.hp < 0) enemy.hp = 0;
            locate(10, 14);
            cout << "You made " << damage << " damage!";
            Sleep(2000);
        } 
        else if (select == 1) { // Defender
            
            locate(10, 12);
            cout << "You defend yourself!";
            int reduced = (rand() % 15 + 5) / 2;
            player.hp -= reduced;
            Sleep(1500);
        } 
        else if (select == 2) { // Huir
            
            locate(5, 12);
            cout << "You try to run...";
            if (rand() % 100 < 40) {
                cout << " And you made it!";
                Sleep(1500);
                break;
            } else {
                cout << " But you fail!";
                Sleep(1500);
            }
        }
        
        if (enemy.hp > 0)
        {
            int edmg = rand() % enemy.dmg + 3;
            player.hp -= edmg;
            rlutil::locate(4, 14);
            cout << "The enemy hits you for " << edmg << " damage.";
        }

        Sleep(1500);
        rlutil::cls();
    }

    if (player.hp <= 0)
    {
        rlutil::cls();
        setColor(rlutil::RED);
        cout << "You have been defeated. GAME OVER.\n";
        system("pause"); // Espera a que el jugador presione una tecla
        exit(0);         // Este se usa para terminar el programa de un solo, puede ser utilizado para una opcion salir del juego
    }

    else if (enemy.hp<= 0){
    setColor(rlutil::GREEN);
    cout << "\nYou defeated the enemy!\n";
    player.level++;
    player.dmg += 2;
    player.hp += 10;

    if (player.hp > player.hpMax)
        player.hp = player.hpMax;
    defeatedEnemies++;

    cout << "Remaining enemies: " << TOTAL_ENEMIES - defeatedEnemies << endl;
    Sleep(2000); // para poder ver el mensaje antes de que se limpie

    unlockGate;

    if (!unlockGate && defeatedEnemies >= TOTAL_ENEMIES)
    {
        unlockGate = true;

        rlutil::locate(1, VIEW_HEIGHT + 3);
        rlutil::setColor(rlutil::YELLOW);
        cout << "\nYou've defeated all the enemies! A secret door has opened...\n";
        rlutil::setColor(rlutil::WHITE);
        Sleep(2500);

        // Limpiar la linea del mensaje
        rlutil::locate(1, VIEW_HEIGHT + 3);
        cout << string(80, ' '); // Crea una cadena de 80 espacios en blanco (' '). (para borrar el mensaje)
    }

    return true; // importante pq si no los enemigos no se eliminan del mapa y tambien se pone abajo pq si es arriba no se abre la puerta
    }

    else {
        cls();
        setColor(rlutil::CYAN);
        cout << "You escaped from combat.";
        Sleep(1500); // para que se vea el mensaje
        return false; // ← IMPORTANTE para que el mapa sepa que no se derrotó al enemigo
    }

}


void bossFight(Boss boss)
{

    Boss finalBoss;

    rlutil::cls();
    cout << boss.name << " appears!\n\n";
    Sleep(2000);

    bool showMessage = false;

    while (player.hp > 0 && boss.hp > 0)
    {

        rlutil::cls();
        rlutil::locate(1, 1);
        cout << "==================== BOSS FIGHT ===================\n";
        HPbar(2, 2, player.hp, player.hpMax, "player");
        HPbar(2, 3, boss.hp, boss.hpMax, boss.name);
        rlutil::locate(1, 4);
        cout << "===================================================\n";

        // Mostrar ASCII del jefe
        int y = 6;
        string ascii = boss.ascii;
        size_t pos = 0;

        while ((pos = ascii.find('\n')) != string::npos)
        {
            rlutil::locate(50, y++);
            cout << ascii.substr(0, pos);
            ascii.erase(0, pos + 1);
        }
        rlutil::locate(50, y);
        cout << ascii;

        string options[] = {"Atack", "Defend", "Run"};
        int select = 0;

        while (true) {
            // Mostrar menú
            for (int i = 0; i < 3; i++) {
                locate(10, 16 + i);
                if (i == select) {
                    setColor(rlutil::YELLOW);
                    cout << "> " << options[i];
                } else {
                    setColor(rlutil::WHITE);
                    cout << "  " << options[i];
                }
            }

            int key = getkey();
            if (key == rlutil::KEY_UP)
                select = (select + 2) % 3;
            else if (key == rlutil::KEY_DOWN)
                select = (select + 1) % 3;
            else if (key == rlutil::KEY_ENTER)
                break;
        }

         if (select == 0) { // Atacar
            
            locate(10, 10);
            cout << "Press ENTER!";
            int damage = attackRoulette();
            boss.hp -= damage;
            if (boss.hp < 0) boss.hp = 0;
            locate(10, 14);
            cout << "You made " << damage << " damage!";
            Sleep(2000);
        } 
        else if (select == 1) { // Defender
            
            locate(10, 12);
            cout << "You defend yourself!";
            int reduced = (rand() % 15 + 5) / 2;
            player.hp -= reduced;
            Sleep(1500);
        } 
        else if (select == 2) { // Huir
            
            locate(10, 12);
            cout << "You try to run...";
            if (rand() % 100 < 40) {
                cout << " And you made it!";
                Sleep(1500);
                break;
            } else {
                cout << " But you fail!";
                Sleep(1500);
            }
        }

        if (boss.hp > 0)
        {
            int edmg = rand() % boss.dmg + 5;
            player.hp -= edmg;
            rlutil::locate(4, 14);
            cout << "The boss hits you for " << edmg << " damage.\n";
        }

        Sleep(1500);

        if (!showMessage && boss.hp <= boss.hpMax / 2)
        {
            rlutil::locate(62, 4); // Línea adecuada que no tape nada
            cout << boss.name << ": \"I will kill you!!!\"";
            showMessage = true;

            Sleep(3000); // para dar tiempo a leerlo
        }
    }

    if (player.hp <= 0)
    {
        rlutil::cls();
        setColor(rlutil::RED);
        cout << "You have been defeated by the boss. GAME OVER.\n";
        system("pause");
        exit(0);
    }

    rlutil::cls(); // LIMPIA toda la consola (para que no se vea el combate más)
    cout << "\n\n=====================================================\n";
    cout << "CONGRATULATIONS! You've defeated the final boss.\n";
    cout << "Redirecting you to the second level...\n";
    cout << "=====================================================\n";
    ::actualLevel = 2;
    player.level++;
    player.dmg += 2;
    player.hp = player.hpMax;
    Sleep(4000);
    system("pause");
}

}

#endif