#ifndef COMBATE3_H
#define COMBATE3_H

#include <limits>
#include <iostream>
#include <string>

#include "../../Level1/Archi_h/rlutil.h"
#include "../../Level1/Archi_h/Structs.h"
#include "../../Level1/Archi_h/boss.h"
#include "temporal3.h"

using namespace std;
using namespace rlutil;

namespace Nivel3{

// Declaraciones forward para evitar dependencias circulares
extern Character player3;
extern bool unlockGate3;
extern const int VIEW_HEIGHT3;

int defeatedEnemies3 = 0;
const int TOTAL_ENEMIES3 = 3;


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
        return rand() % player3.dmg + 25; // verde
    else if ((position >= 10 && position <= 12) || (position >= 17 && position <= 19))
        return rand() % player3.dmg + 15; // amarillo
    else
        return rand() % player3.dmg /2;  // rojo
}



bool startCombat()
{
    PlaySoundA(NULL, NULL, 0);
    PlaySoundA ("CombtSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);


    Enemy enemy3 = {
        "IRON PROTOCOL", // Name
        100,             // Hp
        100,             // hpMax
        20,              // dano
        R"(    
                     ,-~  - ^^~-.,
                 ,^        -,____ ^,         ,/\/\/\,
                /           (____)  |      S~        ~7
               ;  .---._    | | || _|     S  I AM THE  Z
               | |      ~-.,\ | |!/ |     /_   LAW!   _\
               ( |    ~<-.,_^\|_7^ ,|     _//_      _\
               | |      ", 77>   (T/|   _/'   \/\/\/
               |  \_      )/<,/^\)i(|
               (    ^~-,  |________||
               ^!,_    / /, ,'^~^',!!_,..---.
                \_ "-./ /   (-~^~-))' =,__,..>-,
                  ^-,__/#w,_  '^' /~-,_/^\      )
               /\  ( <_    ^~~--T^ ~=, \  \_,-=~^\
  .-==,    _,=^_,.-"_  ^~*.(_  /_)    \ \,=\      )
 /-~;  \,-~ .-~  _,/ \    ___[8]_      \ T_),--~^^)
   _/   \,,..==~^_,.=,\   _.-~O   ~     \_\_\_,.-=}
 ,{       _,.-<~^\  \ \\      ()  .=~^^~=. \_\_,./
,{ ^T^ _ /  \  \  \  \ \)    [|   \       >
  ^T~ ^ { \  \ _\.-|=-T~\\    () ()\<||>,' )
   +     \ |=~T  !       Y    [|()  \ ,'  /   )"}; // ascii

    rlutil::cls();
    cout << enemy3.name << " appears!\n";
    Sleep(2000);


    while (player3.hp > 0 && enemy3.hp > 0)
    {
        cls();
        setColor(rlutil::WHITE);
        rlutil::locate(1, 1);
        cout << "=============================================";
        HPbar(2, 2, player3.hp, player3.hpMax, "player");
        HPbar(2, 3, enemy3.hp, enemy3.hpMax, enemy3.name);
        rlutil::locate(1, 4);
        cout << "=============================================";

        int y = 6;                    // El ascii se imprimira en la linea 6 en el eje y
        string ascii = enemy3.ascii; // mandar a llamar la variable de ascii
        size_t pos = 0;               // variable pos que se usará para encontrar las posiciones de los saltos de línea (\n)

        // npos se usa para indicar que no se encontró nada durante una operación de búsqueda en un std::string

        while ((pos = ascii.find('\n')) != string::npos)
        {                                 // ascii.find('\n') busca la posición del primer salto de línea.
            rlutil::locate(65, y++);      // Posicionar ASCII art más a la derecha para ventana de 120 caracteres
            cout << ascii.substr(0, pos); // ascii.substr(0, pos) obtiene el contenido antes del salto de línea (una línea de dibujo).
            ascii.erase(0, pos + 1);      // borra esa parte impresa más el \n con ascii.erase(0, pos + 1); para seguir con la siguiente línea.
        }

        rlutil::locate(65, y);
        cout << ascii;

        string options[] = {"Atack", "Run"};
        int select = 0;

        while (kbhit()) getch();   //  Limpiar teclas residuales ANTES de entrar al menú

        while (true) {
            // Mostrar menú
            for (int i = 0; i < 2; i++) {
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
                select = (select - 1 + 2) % 2;
            else if (key == rlutil::KEY_DOWN)
                select = (select + 1) % 2;
            else if (key == rlutil::KEY_ENTER)
                break;
        }

         if (select == 0) {                 // Atacar
            
            locate(10, 10);
            cout << "Press ENTER!!";
            int damage = attackRoulette();
            enemy3.hp -= damage;
            if (enemy3.hp < 0) enemy3.hp = 0;
            locate(10, 14);
            cout << "You made " << damage << " damage!";
            Sleep(2000);
        } 
       
        else if (select == 1) {             // Huir
            
            locate(10, 12);
            cout << "You try to run...";
            if (rand() % 100 < 40) {
                cout << " And you made it!";
                Sleep(1500);
                cls();
                setColor(rlutil::WHITE); // Restaurar color blanco
                setColor(rlutil::CYAN);
                cout << "You escaped from combat.";
                Sleep(1500);
                setColor(rlutil::WHITE); // Asegurar que quede en blanco
                return false; // Retorna false para que el enemigo permanezca en el mapa
            } else {
                cout << " But you fail!";
                Sleep(1500);
            }
        }
        
        if (enemy3.hp > 0)
        {
            int edmg = rand() % enemy3.dmg + 3;
            player3.hp -= edmg;
            rlutil::locate(4, 14);
            cout << "The enemy hits you for " << edmg << " damage.";
        }

        Sleep(1500);
        rlutil::cls();
    }

    if (player3.hp <= 0)
    {
        rlutil::cls();
        setColor(rlutil::RED);
        cout << "You have been defeated. GAME OVER.\n";
        cout << "Press any key to exit...";
        getch();
        exit(0);         // Este se usa para terminar el programa de un solo, puede ser utilizado para una opcion salir del juego
    }

    else if (enemy3.hp<= 0){
    setColor(rlutil::GREEN);
    cout << "\nYou defeated the enemy!\n";
    player3.level++;
    player3.dmg += 2;
    player3.hp += 10;

    if (player3.hp > player3.hpMax)
        player3.hp = player3.hpMax;
    defeatedEnemies3++;

    cout << "Remaining enemies: " << TOTAL_ENEMIES3 - defeatedEnemies3 << endl;
    Sleep(2000); // para poder ver el mensaje antes de que se limpie

    PlaySoundA("LvlSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    unlockGate3;

    if (!unlockGate3 && defeatedEnemies3 >= TOTAL_ENEMIES3)
    {
        unlockGate3 = true;

        rlutil::locate(1, VIEW_HEIGHT3 + 3);
        rlutil::setColor(rlutil::YELLOW);
        cout << "\nYou've defeated all the enemies! A secret door has opened...\n";
        rlutil::setColor(rlutil::WHITE);
        Sleep(2500);

        // Limpiar la linea del mensaje
        rlutil::locate(1, VIEW_HEIGHT3 + 3);
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
    PlaySoundA(NULL, NULL, 0);
    PlaySoundA ("CombtSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);


    Boss finalBoss;

    rlutil::cls();
    cout << boss.name << " appears!\n\n";
    Sleep(2000);

    bool showMessage = false;

    while (player3.hp > 0 && boss.hp > 0)
    {

        rlutil::cls();
        rlutil::locate(1, 1);
        cout << "==================== BOSS FIGHT ===================\n";
        HPbar(2, 2, player3.hp, player3.hpMax, "player");
        HPbar(2, 3, boss.hp, boss.hpMax, boss.name);
        rlutil::locate(1, 4);
        cout << "===================================================\n";

        // Mostrar ASCII del jefe
        int y = 6;
        string ascii = boss.ascii;
        size_t pos = 0;

        while ((pos = ascii.find('\n')) != string::npos)
        {
            rlutil::locate(65, y++);
            cout << ascii.substr(0, pos);
            ascii.erase(0, pos + 1);
        }
        rlutil::locate(65, y);
        cout << ascii;

        string options[] = {"Atack", "Run"};
        int select = 0;

        while (true) {
            // Mostrar menú
            for (int i = 0; i < 2; i++) {
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
                select = (select - 1 + 2) % 2;
            else if (key == rlutil::KEY_DOWN)
                select = (select + 1) % 2;
            else if (key == rlutil::KEY_ENTER)
                break;
        }

         if (select == 0) {             // Atacar
            
            locate(10, 10);
            cout << "Press ENTER!";
            int damage = attackRoulette();
            boss.hp -= damage;
            if (boss.hp < 0) boss.hp = 0;
            locate(10, 14);
            cout << "You made " << damage << " damage!";
            Sleep(2000);
        } 
        
        else if (select == 1) {         // Huir
            
            locate(10, 12);
            cout << "You try to run...";
            if (rand() % 100 < 40) {
                cout << " And you made it!";
                Sleep(1500);
                rlutil::cls();
                setColor(rlutil::WHITE); // Restaurar color blanco
                setColor(rlutil::CYAN);
                cout << "You escaped from the boss fight.";
                Sleep(1500);
                setColor(rlutil::WHITE); // Asegurar que quede en blanco
                return; // Salir de la función sin cambiar de nivel
            } else {
                cout << " But you fail!";
                Sleep(1500);
            }
        }

        if (boss.hp > 0)
        {
            int edmg = rand() % boss.dmg + 5;
            player3.hp -= edmg;
            rlutil::locate(4, 14);
            cout << "The boss hits you for " << edmg << " damage.\n";
        }

        Sleep(1500);

        if (!showMessage && boss.hp <= boss.hpMax / 2)
        {
            rlutil::locate(72, 4); // Línea adecuada que no tape nada
            cout << boss.name << ": \"You cant kill me!!!\"";
            showMessage = true;

            Sleep(3000); // para dar tiempo a leerlo
        }
    }

    if (player3.hp <= 0)
    {
        rlutil::cls();
        setColor(rlutil::RED);
        cout << "You have been defeated by the boss. GAME OVER.\n";
        cout << "Press any key to exit...";
        getch();
        exit(0);
    }

    rlutil::cls(); // LIMPIA toda la consola (para que no se vea el combate más)
     
    cout << "\n\n=====================================================\n";
    cout << "CONGRATULATIONS! You've defeated the final boss.\n";
    cout << "Redirecting you to the final screen...\n";
    cout << "=====================================================\n";
    player3.level++;
    player3.dmg += 2;
    
    // Cambiar a nivel 4 para activar la pantalla final
    ::actualLevel = 4;
    
    Sleep(4000);

    PlaySoundA("LvlSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    cout << "Press any key to continue...";
    getch();
}

} // namespace Nivel3

#endif