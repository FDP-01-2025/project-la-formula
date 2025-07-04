#ifndef COMBATE2_H
#define COMBATE2_H

#include <limits>
#include <iostream>
#include <string>

#include "rlutil.h"
#include "../../Level1/Archi_h/Structs.h"
#include "../../Level1/Archi_h/boss.h"
#include "temporal2.h"

using namespace std;
using namespace rlutil;

namespace Nivel2 {

// Declaraciones forward para evitar dependencias circulares
extern Character player2;
extern bool unlockGate2;
extern const int VIEW_HEIGHT2;

int defeatedEnemies2 = 0;
const int TOTAL_ENEMIES2 = 2;


int attackRoulette() {
    int position = 0;
    const int max = 30;

    while (!kbhit()) {
        rlutil::locate(6, 12);
        cout << "[";
        for (int i = 0; i < max; i++) {
            if (i == position)
                rlutil::setColor(rlutil::YELLOW), cout << "|";
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
        return rand() % player2.dmg + 25; // verde
    else if ((position >= 10 && position <= 12) || (position >= 17 && position <= 19))
        return rand() % player2.dmg + 15; // amarillo
    else
        return rand() % player2.dmg + 5;  // rojo
}



bool startCombat()
{

    Enemy enemy2 = {
        "CYBER UNIT-X", // Name
        75,             // Hp
        75,             // hpMax
        15,              // dano
        R"(    
                 _..--'`;;`-..-';;'`--.._
                .';,    _   `;;'   _    ,;`.
               ;;'  `;;' `;.`;;'.;' `;;'  `;;
              .;;._.;'`;.   `;;'   .;'`;._.;;.
            ;'      '`;;`   `;;'   ';;'`      `;
           ;:     .:.  `;;. `--' .;;'  .:.     :;
            ;.   .:|:.     `;;;;'     .:|:.   .;
             `;  `:|:'    .;;'`;;.    `:|:'  ;'
              `;. `:'  .;;'.::::.`;;.  `:' .;'
                `;._.;;' .:`::::':. `;;._.;'
           .::::. `::   (:._.::._.:)   ::' .::::.
      .:::::'  `::.`:_.--.`:::::. .--._:'.::'  `:::::.
    .::'     `:.    `::-.:::"""":::.-::'   `::      `::.
  .::'      .::'      | /.^^^..^^^.\ |      `::        `:.
  :::      .:'::.     \( `;;;..;;;' )/     .::::       :::
  ::  :  .:':.  `::.   \            /   .::'  .:     .  ::
  :  ::  .   :     `::.              .::'     :  :   ::  :
 .:  :    `.::.       `:.          .:'       .::.'    :  :.
::  :  :   : :::.       `:.      .:'       .::: :   :  :  ::
::  :        :' `:.       :.    .:       .:' `:        :  ::
:::     :   ::    `:.      :.  .:      .:'    ::   :     :::
' :       :::'      :.      `::'      .:      `:::       : ` )"}; // ascii

    rlutil::cls();
    cout << enemy2.name << " appears!\n";
    Sleep(2000);


    while (player2.hp > 0 && enemy2.hp > 0)
    {
        cls();
        setColor(rlutil::WHITE);
        rlutil::locate(1, 1);
        cout << "=============================================";
        HPbar(2, 2, player2.hp, player2.hpMax, "player");
        HPbar(2, 3, enemy2.hp, enemy2.hpMax, enemy2.name);
        rlutil::locate(1, 4);
        cout << "=============================================";

        int y = 6;                    // El ascii se imprimira en la linea 6 en el eje y
        string ascii = enemy2.ascii; // mandar a llamar la variable de ascii
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
            enemy2.hp -= damage;
            if (enemy2.hp < 0) enemy2.hp = 0;
            locate(10, 14);
            cout << "You made " << damage << " damage!";
            Sleep(2000);
        } 
        else if (select == 1) { // Defender
            
            locate(10, 12);
            cout << "You defend yourself!";
            int reduced = (rand() % 15 + 5) / 2;
            player2.hp -= reduced;
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
        
        if (enemy2.hp > 0)
        {
            int edmg = rand() % enemy2.dmg + 3;
            player2.hp -= edmg;
            rlutil::locate(4, 14);
            cout << "The enemy hits you for " << edmg << " damage.";
        }

        Sleep(1500);
        rlutil::cls();
    }

    if (player2.hp <= 0)
    {
        rlutil::cls();
        setColor(rlutil::RED);
        cout << "You have been defeated. GAME OVER.\n";
        system("pause"); // Espera a que el jugador presione una tecla
        exit(0);         // Este se usa para terminar el programa de un solo, puede ser utilizado para una opcion salir del juego
    }

    else if (enemy2.hp<= 0){
    setColor(rlutil::GREEN);
    cout << "\nYou defeated the enemy!\n";
    player2.level++;
    player2.dmg += 2;
    player2.hp += 10;

    if (player2.hp > player2.hpMax)
        player2.hp = player2.hpMax;
    defeatedEnemies2++;

    cout << "Remaining enemies: " << TOTAL_ENEMIES2 - defeatedEnemies2 << endl;
    Sleep(2000); // para poder ver el mensaje antes de que se limpie

    unlockGate2;

    if (!unlockGate2 && defeatedEnemies2 >= TOTAL_ENEMIES2)
    {
        unlockGate2 = true;

        rlutil::locate(1, VIEW_HEIGHT2 + 3);
        rlutil::setColor(rlutil::YELLOW);
        cout << "\nYou've defeated all the enemies! A secret door has opened...\n";
        rlutil::setColor(rlutil::WHITE);
        Sleep(2500);

        // Limpiar la linea del mensaje
        rlutil::locate(1, VIEW_HEIGHT2 + 3);
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

    while (player2.hp > 0 && boss.hp > 0)
    {

        rlutil::cls();
        rlutil::locate(1, 1);
        cout << "==================== BOSS FIGHT ===================\n";
        HPbar(2, 2, player2.hp, player2.hpMax, "player");
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
            player2.hp -= reduced;
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
            player2.hp -= edmg;
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

    if (player2.hp <= 0)
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
    cout << "Redirecting you to the last level...\n";
    cout << "=====================================================\n";
    ::actualLevel = 3;
    player2.level++;
    player2.dmg += 2;
    player2.hp = player2.hpMax;
    Sleep(4000);
    system("pause");
}

} // namespace Nivel2

#endif