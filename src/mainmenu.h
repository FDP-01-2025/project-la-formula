#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>       // Para PlaySound
#include "Level1/Archi_h/rlutil.h"

using namespace std;

// Declaraciones de funciones y variables globales
extern bool loadGame();  // Función global definida en loadGame.h
extern int actualLevel;  // Variable global definida en main.cpp

namespace MainMenu {

// Variable global para almacenar el nombre del jugador (extern para acceso global)
extern string playerName;

// Función para configurar la ventana de consola con dimensiones óptimas
void setupConsoleWindow() {
    // Configurar título de la ventana
    SetConsoleTitleA("LA FORMULA - The Game");
    
    // Configurar el tamaño de la ventana de consola (opcional)
    system("mode 120,40");
}

// Función para que el jugador ingrese su nombre
string getPlayerName()
{
    rlutil::cls();
    rlutil::setColor(rlutil::LIGHTCYAN);
    
    // Dibujar un marco decorativo
    rlutil::locate(30, 10);
    cout << "╔════════════════════════════════════════╗";
    rlutil::locate(30, 11);
    cout << "║                                        ║";
    rlutil::locate(30, 12);
    cout << "║          ENTER YOUR NAME               ║";
    rlutil::locate(30, 13);
    cout << "║                                        ║";
    rlutil::locate(30, 14);
    cout << "║  Name: ____________________________    ║";
    rlutil::locate(30, 15);
    cout << "║                                        ║";
    rlutil::locate(30, 16);
    cout << "║  Press ENTER when finished             ║";
    rlutil::locate(30, 17);
    cout << "║                                        ║";
    rlutil::locate(30, 18);
    cout << "╚════════════════════════════════════════╝";
    
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(39, 14);
    rlutil::showcursor();
    
    string name;
    char ch;
    
    while (true)
    {
        ch = rlutil::getkey();
        
        if (ch == rlutil::KEY_ENTER)
        {
            break;
        }
        else if (ch == 8) // Backspace
        {
            if (!name.empty())
            {
                name.pop_back();
                rlutil::locate(39 + name.length(), 14);
                cout << "_";
                rlutil::locate(39 + name.length(), 14);
            }
        }
        else if (ch >= 32 && ch <= 126 && name.length() < 25) // Caracteres imprimibles
        {
            name += ch;
            rlutil::locate(39 + name.length() - 1, 14);
            cout << ch;
        }
    }
    
    rlutil::hidecursor();
    
    // Si no ingresó nombre, usar "Player" por defecto
    if (name.empty())
    {
        name = "Player";
    }
    
    // Mensaje de confirmación
    rlutil::cls();
    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(35, 12);
    cout << "Welcome, " << name << "!";
    rlutil::locate(30, 14);
    cout << "Your adventure is about to begin...";
    rlutil::resetColor();
    rlutil::msleep(2000);
    
    return name;
}

// Devuelve el color adecuado para cada caracter del arte ASCII
int colorear(char c)
{
    switch (c)
    {
    case ':':
        return rlutil::LIGHTCYAN;
    case '_':
        return rlutil::LIGHTGREEN;
    case '#':
        return rlutil::MAGENTA;
    case '*':
        return rlutil::LIGHTMAGENTA;
    case '+':
        return rlutil::LIGHTCYAN;
    case '=':
        return rlutil::LIGHTCYAN;
    case '%':
        return rlutil::GREY;
    case '@':
        return rlutil::LIGHTGREEN;
    case '-':
        return rlutil::DARKGREY;
    case '/':
        return rlutil::BLUE;
    case '\\':
        return rlutil::BLUE;
    case '|':
        return rlutil::WHITE;
    default:
        return rlutil::DARKGREY;
    }
}

// Calcula el ancho visual de una cadena UTF-8 (para centrar el logo)
int visualWidth(const char *str)
{
    int width = 0;
    for (int i = 0; str[i] != '\0';)
    {
        width++;
        // Avanza al siguiente caracter UTF-8
        if ((str[i] & 0x80) == 0)
        {
            i += 1;
        }
        else if ((str[i] & 0xE0) == 0xC0)
        {
            i += 2;
        }
        else if ((str[i] & 0xF0) == 0xE0)
        {
            i += 3;
        }
        else if ((str[i] & 0xF8) == 0xF0)
        {
            i += 4;
        }
        else
        {
            i += 1; // Fallback
        }
    }
    return width;
}

// Muestra el logo animado del juego
void mostrarLogo()
{
    // Logo en arte ASCII
    const char *logo[] = {
        " █████╗     ███████╗    ████████╗    ███████╗    ██████╗     ███╗   ███╗     █████╗     ████████╗    ██╗  ██╗",
        "██╔══██╗    ██╔════╝    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ████╗ ████║    ██╔══██╗    ╚══██╔══╝    ██║  ██║",
        "███████║    █████╗         ██║       █████╗      ██████╔╝    ██╔████╔██║    ███████║       ██║       ███████║",
        "██╔══██║    ██╔══╝         ██║       ██╔══╝      ██╔══██╗    ██║╚██╔╝██║    ██╔══██║       ██║       ██╔══██║",
        "██║  ██║    ██║            ██║       ███████╗    ██║  ██║    ██║ ╚═╝ ██║    ██║  ██║       ██║       ██║  ██║",
        "╚═╝  ╚═╝    ╚═╝            ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝     ╚═╝    ╚═╝  ╚═╝       ╚═╝       ╚═╝  ╚═╝"};
    int num_lines = sizeof(logo) / sizeof(logo[0]);
    int max_len = visualWidth(logo[0]);
    int startY = 15;                              // Fila inicial para el logo
    int startX = (rlutil::tcols() - max_len) / 2; // Centrado horizontal

    // Animación de aparición del logo
    for (int i = 0; i < num_lines; ++i)
    {
        rlutil::locate(startX, startY + i);
        const char *line = logo[i];
        for (int j = 0; line[j] != '\0';)
        {
            int char_bytes = 1;
            if ((line[j] & 0x80) == 0)
            {
                char_bytes = 1;
            }
            else if ((line[j] & 0xE0) == 0xC0)
            {
                char_bytes = 2;
            }
            else if ((line[j] & 0xF0) == 0xE0)
            {
                char_bytes = 3;
            }
            else if ((line[j] & 0xF8) == 0xF0)
            {
                char_bytes = 4;
            }
            // Imprime el caracter (todos sus bytes)
            for (int k = 0; k < char_bytes; ++k)
            {
                cout << line[j + k];
            }
            cout.flush();
            j += char_bytes;
            rlutil::msleep(5); // Velocidad de animación
        }
    }
}

// Muestra archivo con arte coloreado línea por línea
void mostrarArchivo(const char *nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo)
        return;
    string linea;
    while (getline(archivo, linea))
    {
        int longitud = linea.length();
        for (int i = 0; i < longitud; ++i)
        {
            rlutil::setColor(colorear(linea[i]));
            cout << linea[i];
        }
        for (int i = longitud; i < 100; ++i)
        {
            cout << ' ';
        }
        rlutil::resetColor();
        cout << endl;
    }
    archivo.close();
}

// Crea el archivo arte2.txt con el menú y arte decorativo
void crearArchivoArte2()
{
    ofstream archivo("arte2.txt");
    if (!archivo)
        return;
    const char *lineas[] = {
        " .   `-._.-*   /    `-*'  `*-.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+++----------------------------+++",
        "-._.*        _.-'        .-.    `-.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |          M E N U           | |",
        "          .-'         _.'   `-._   `-.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |----------------------------| |",
        "\\       .'                      `*-.__`-._%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "    _.._    /       -.                \"\"\\;%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |   [1] New game             | |",
        ".'-._ `. :   :      `.         :      `+.    ;%%%%%%%%%%%%%%%%%%%%%%%%| |   [2] Continue game        | |",
        "/     `. \\:    \\           `-.   \\ `-.    \\%%%%%%%%%%%%%%%%%%%%%%%%%%%| |   [3] Exit                 | |",
        ":        \\ ;  \\  ;    `. `.    \\   `.__\\;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "          ;;   ;     `-.  \\ _.-:*\"'   `:`._:%%%%%%%%%%%%%%%%%%%%%%%%%%| |----------------------------| |",
        "       .-*:  ' :   \\    ;;-*'\"*.       .-,%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "      '   :  ; ;   /:.-'        `        ;%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |    Use W S to move         | |",
        "          ; /     :     _.--s+.        .s:%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        ":        / :  :   ;    \\   dPT$b.    \\d$PTb%%%%%%%%%%%%%%%%%%%%%%%%%%%| |    ENTER to confirm        | |",
        "\\     .'  ;  ;   ;     `.:$bd$$$b    `Tbd$%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " `._.'   /  /    :       `*^^^^*' ,    `T$%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " .-'    : .'      \\                      `-._%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "/      .+'         \\                         \\%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        ":      /            \\`._                       ;%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "      :          `.  ;                        /%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "              ;    \\ :              ;  ,s*' .'%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "        '    /      :;              `. '   (%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "       /   .'       :                   .-*-*.%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "  .'   /      /    /            ._.'   _.---(%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " /    :    .-'   .'         '      *--*\"      :%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        ":         /     /`.                `-.__.--._.'%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "               :   `.                       ;%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "         '     ;     `-.                    :%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "        /;     :        `---..._______...--*'%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " ;  ;         ;   ;        :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+++----------------------------+++",
    };
    
    const int num_lineas = sizeof(lineas) / sizeof(lineas[0]);
    for (int i = 0; i < num_lineas; ++i)
    {
        archivo << lineas[i] << endl;
    }
    archivo.close();
}

// Función para manejar la carga de juego guardado
// Retorna true si se cargó exitosamente, false si hay que empezar juego nuevo
bool handleContinueGame() {
    rlutil::cls();
    rlutil::locate(30, 12);
    cout << "Loading saved game...";
    rlutil::msleep(1000);
    
    if (::loadGame()) {
        // El juego se cargó exitosamente
        rlutil::locate(30, 14);
        cout << "Game loaded! Returning to level " << ::actualLevel;
        rlutil::msleep(2000);
        return true;
    } else {
        // No hay archivo de guardado, empezar juego nuevo
        rlutil::locate(30, 14);
        cout << "No saved game found. Starting new game...";
        rlutil::msleep(2000);
        playerName = getPlayerName();
        return false;  // Indica que hay que empezar desde nivel 1
    }
}

// Muestra el menú interactivo y permite seleccionar una opción con W/S
// Retorna: 0 = New Game, 1 = Continue, 2 = Exit
int menuInteractivo(const char *nombreArchivo)
{
    int i = 0; // Opción seleccionada
    int key;
    rlutil::hidecursor();
    mostrarArchivo(nombreArchivo);
    
    // Posición inicial del selector
    rlutil::locate(75, 5 + i);
    cout << '>'; // Selector visible
    do
    {
        key = rlutil::getkey();
        // Borra el selector anterior
        rlutil::locate(75, 5 + i);
        cout << " ";
        switch (key)
        {
        case 'w':
        case 'W':
            i--;
            if (i < 0)
                i = 0;
            break;
        case 's':
        case 'S':
            i++;
            if (i > 2)
                i = 2;
            break;
        }
        // Dibuja el nuevo selector
        rlutil::locate(75, 5 + i);
        cout << '>';
    } while (key != rlutil::KEY_ENTER);
    
    // Mostrar mensaje según la opción elegida
    rlutil::locate(75, 5 + i);
    cout << " "; // Borra el selector
    rlutil::locate(77, 5);
    
    switch (i)
    {
    case 2:
        cout << "The adventure can wait...";
        rlutil::msleep(1500);
        break;
    case 1:
        cout << "Loading game...";
        rlutil::msleep(1500);
        break;
    case 0:
        cout << "The adventure begins!...";
        rlutil::msleep(1500);
        break;
    default:
        break;
    }
    rlutil::resetColor();
    rlutil::cls();
    return i;
}

// Función principal del menú que maneja todo el flujo
// Retorna: 0 = New Game, 1 = Continue, 2 = Exit
int showMainMenu()
{
    SetConsoleOutputCP(CP_UTF8); // Soporte UTF-8 en consola
    
    // 🔊 Inicia la música de fondo en loop
    if (!PlaySoundA("MenuSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP))
    {
        // No mostrar error si no encuentra el archivo de música
    }
    
    mostrarLogo();                // Muestra el logo animado
    rlutil::msleep(3000);         // Espera 3 segundos
    rlutil::cls();                // Limpia pantalla
    crearArchivoArte2();          // Crea el menú arte2.txt
    int selection = menuInteractivo("arte2.txt"); // Muestra menú interactivo
    remove("arte2.txt");          // Borra archivo temporal
    
    return selection;
}

// Función para detener la música al salir del juego
void stopMusic()
{
    PlaySoundA(NULL, NULL, 0);
}

} // namespace MainMenu

#endif // MAINMENU_H
