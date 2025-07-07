#include <ctime> //time(0) para obtener tiempo actual como semilla para srand.
//<ctime> incluye internamente <stdlib.h> que es la versión C de <cstdlib> (la que sirve para rand)

#include "src/mainmenu.h"
#include "src/finalscreen.h"
#include "src/Level1/Archi_h/mapa.h"
#include "src/Level2/Archi2_h/mapa2.h"
#include "src/Level3/Archi3_h/mapa3.h"

using namespace std;

// Declarar la variable global de nivel actual
int actualLevel = 1;

// Definir la variable global del nombre del jugador
string MainMenu::playerName = "Player";


int main()
{
    // Configurar la ventana de consola con dimensiones óptimas
    MainMenu::setupConsoleWindow();
    
    srand(time(0));       // inicializa el generador de números aleatorios con la hora actual como semilla. Esto para los ataques/curaciones
    rlutil::hidecursor(); // oculta el cursor
    system("cls");        // Limpia toda la consola al iniciar el juego.

    // Mostrar el menú principal
    int menuSelection = MainMenu::showMainMenu();
    
    // Manejar la selección del menú
    switch(menuSelection)
    {
        case 0: // New Game
            // Pedir al jugador que ingrese su nombre
            MainMenu::playerName = MainMenu::getPlayerName();
            break;
        case 1: // Continue Game
            // Por ahora, actuar como New Game (puede implementarse save/load después)
            rlutil::cls();
            rlutil::locate(40, 12);
            cout << "Continue feature not yet implemented. Starting new game...";
            rlutil::msleep(2000);
            // También pedir nombre para continue
            MainMenu::playerName = MainMenu::getPlayerName();
            break;
        case 2: // Exit
            MainMenu::stopMusic();
            return 0;
        default:
            return 0;
    }

    // Comenzar el juego principal
    while (true)
    { // bucle principal del juego, se repite para siempre hasta que el juego termine o el jugador muera

        cls();

        if (actualLevel == 1)
        {
            // Usar las funciones del Nivel 1
            while (actualLevel == 1)
            {
                Nivel1::showHUD();
                Nivel1::drawView(); // Mandar a llamar las funciones void.
                Nivel1::checkMovement();
                Sleep(30); // Espera 30 milisegundos para que la CPU no se sobrecargue y los movimientos sean suaves
            }
        }

        if(actualLevel == 2)
        {
            // Usar las funciones del Nivel 2
            while(actualLevel == 2)
            {
                Nivel2::showHUD_L2();
                Nivel2::drawView_L2();
                Nivel2::checkMovement_L2();
                Sleep(30);
            }
        }

        // Si llegamos aquí, el juego ha terminado o se ha completado
        if (actualLevel == 3)
        {
            // Usar las funciones del Nivel 3
            while (actualLevel == 3)
            {
                Nivel3::showHUD_L3();
                Nivel3::drawView_L3();
                Nivel3::checkMovement_L3();
                Sleep(30);
            }
        }
        
        // ¡JUEGO COMPLETADO! Mostrar pantalla final
        if (actualLevel == 4)
        {
            FinalScreen::showFinalScreen();
            break; // Salir del bucle principal del juego
        }
    }
    
    // Detener la música al salir
    MainMenu::stopMusic();
    return 0;
}
