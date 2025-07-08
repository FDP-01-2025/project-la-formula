#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>       // Para PlaySound
#include "../Level1/Archi_h/rlutil.h"

using namespace std;

// Declaraciones externas (definidas fuera)
extern bool loadGame();      // Función global en loadGame.h
extern int actualLevel;      // Variable global definida en main.cpp

namespace MainMenu {

    void displayPlainFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "No se pudo abrir el archivo: " << fileName << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}

// Variable global para el nombre del jugador
extern string playerName;

// Configura la ventana de la consola
inline void setupConsoleWindow() {
    SetConsoleTitleA("LA FORMULA - The Game");
    system("mode 120,40");
}

// Obtiene el nombre del jugador con input y diseño bonito
inline string getPlayerName()
{
    rlutil::cls();
    rlutil::setColor(rlutil::LIGHTCYAN);

    // Marco decorativo
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
            break;

        if (ch == 8) // Backspace
        {
            if (!name.empty())
            {
                name.pop_back();
                rlutil::locate(39 + (int)name.length(), 14);
                cout << "_";
                rlutil::locate(39 + (int)name.length(), 14);
            }
        }
        else if (ch >= 32 && ch <= 126 && name.length() < 25) // Caracteres imprimibles
        {
            name += ch;
            rlutil::locate(39 + (int)name.length() - 1, 14);
            cout << ch;
        }
    }

    rlutil::hidecursor();

    if (name.empty())
        name = "Player";

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

// Devuelve el color para cada carácter del arte ASCII
inline int getAsciiColor(char c)
{
    switch (c)
    {
    case ':': return rlutil::LIGHTCYAN;
    case '_': return rlutil::LIGHTGREEN;
    case '#': return rlutil::MAGENTA;
    case '*': return rlutil::LIGHTMAGENTA;
    case '+': return rlutil::LIGHTCYAN;
    case '=': return rlutil::LIGHTCYAN;
    case '%': return rlutil::GREY;
    case '@': return rlutil::LIGHTGREEN;
    case '-': return rlutil::DARKGREY;
    case '/': return rlutil::BLUE;
    case '\\': return rlutil::BLUE;
    case '|': return rlutil::WHITE;
    default: return rlutil::DARKGREY;
    }
}

// Calcula el ancho visual para centrar logos UTF-8
inline int visualWidth(const string& str)
{
    int width = 0;
    for (size_t i = 0; i < str.length(); )
    {
        width++;
        if ((str[i] & 0x80) == 0)
            i += 1;
        else if ((str[i] & 0xE0) == 0xC0)
            i += 2;
        else if ((str[i] & 0xF0) == 0xE0)
            i += 3;
        else if ((str[i] & 0xF8) == 0xF0)
            i += 4;
        else
            i += 1;
    }
    return width;
}

// Displays a file with colored ASCII art
void displayFile(const string& fileName)
{
    ifstream file(fileName);
    if (!file)
        return;

    string line;
    int lineNumber = 0;
    while (getline(file, line))
    {
        rlutil::locate(1, lineNumber);
        for (char c : line)
        {
            rlutil::setColor(getAsciiColor(c));
            cout << c;
        }
        cout << endl;
        lineNumber++;
    }

    file.close();
    rlutil::resetColor();
}

// Muestra el logo animado
inline void showLogo()
{
    string logo[] = {
        " █████╗     ███████╗    ████████╗    ███████╗    ██████╗     ███╗   ███╗     █████╗     ████████╗    ██╗  ██╗",
        "██╔══██╗    ██╔════╝    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ████╗ ████║    ██╔══██╗    ╚══██╔══╝    ██║  ██║",
        "███████║    █████╗         ██║       █████╗      ██████╔╝    ██╔████╔██║    ███████║       ██║       ███████║",
        "██╔══██║    ██╔══╝         ██║       ██╔══╝      ██╔══██╗    ██║╚██╔╝██║    ██╔══██║       ██║       ██╔══██║",
        "██║  ██║    ██║            ██║       ███████╗    ██║  ██║    ██║ ╚═╝ ██║    ██║  ██║       ██║       ██║  ██║",
        "╚═╝  ╚═╝    ╚═╝            ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝     ╚═╝    ╚═╝  ╚═╝       ╚═╝       ╚═╝  ╚═╝"
    };
    int numLines = sizeof(logo) / sizeof(logo[0]);
    int maxLen = visualWidth(logo[0]);
    int startY = 15;
    int startX = (rlutil::tcols() - maxLen) / 2;

    for (int i = 0; i < numLines; ++i)
    {
        rlutil::locate(startX, startY + i);
        string line = logo[i];

        for (size_t j = 0; j < line.length(); )
        {
            int charBytes = 1;
            if ((line[j] & 0x80) == 0) charBytes = 1;
            else if ((line[j] & 0xE0) == 0xC0) charBytes = 2;
            else if ((line[j] & 0xF0) == 0xE0) charBytes = 3;
            else if ((line[j] & 0xF8) == 0xF0) charBytes = 4;

            for (int k = 0; k < charBytes; ++k)
                cout << line[j + k];
            cout.flush();
            j += charBytes;
            rlutil::msleep(5);
        }
    }
}

// Crea el archivo arte2.txt con arte del menú
inline void createMenuArtFile()
{
    ofstream menuFile("arte2.txt");
    if (!menuFile) return;

    string lines[] = {
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
        " ;  ;         ;   ;        :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+++----------------------------+++"
    };

    int numLines = sizeof(lines) / sizeof(lines[0]);
    for (int i = 0; i < numLines; ++i)
        menuFile << lines[i] << endl;

    menuFile.close();
}

// Maneja la carga de partida guardada
inline bool handleContinueGame() {
    rlutil::cls();
    rlutil::locate(30, 12);
    cout << "Loading saved game...";
    rlutil::msleep(1000);

    if (::loadGame()) {
        rlutil::locate(30, 14);
        cout << "Game loaded! Returning to level " << ::actualLevel;
        rlutil::msleep(2000);
        return true;
    } else {
        rlutil::locate(30, 14);
        cout << "No saved game found. Starting new game...";
        rlutil::msleep(2000);
        playerName = getPlayerName();
        return false;
    }
}

// Muestra el menú interactivo con selector (W/S y ENTER)
// Retorna: 0 = New Game, 1 = Continue, 2 = Exit
inline int interactiveMenu(const char *fileName)
{
    int selectedOption = 0;
    int key;

    rlutil::hidecursor();
    displayFile(string(fileName)); // La función displayFile debe estar definida en algún lado para mostrar el arte

    rlutil::locate(75, 5 + selectedOption);
    cout << '>';

    do {
        key = rlutil::getkey();

        // Borra selector anterior
        rlutil::locate(75, 5 + selectedOption);
        cout << " ";

        switch (key) {
            case 'w': case 'W':
                if (selectedOption > 0) selectedOption--;
                break;
            case 's': case 'S':
                if (selectedOption < 2) selectedOption++;
                break;
        }

        rlutil::locate(75, 5 + selectedOption);
        cout << '>';

    } while (key != rlutil::KEY_ENTER);

    rlutil::locate(75, 5 + selectedOption);
    cout << " "; // Borra selector

    rlutil::locate(77, 5);
    switch (selectedOption)
    {
    case 0: cout << "The adventure begins!..."; break;
    case 1: cout << "Loading game..."; break;
    case 2: cout << "The adventure can wait..."; break;
    }
    rlutil::msleep(1500);
    rlutil::resetColor();
    rlutil::cls();

    return selectedOption;
}

// Función principal del menú que controla todo el flujo
// Retorna: 0 = New Game, 1 = Continue, 2 = Exit
inline int showMainMenu()
{
    SetConsoleOutputCP(CP_UTF8);

    if (!PlaySoundA("MenuSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP))
    {
        // No mostrar error si no encuentra el archivo de música
    }

    showLogo();
    rlutil::msleep(3000);
    rlutil::cls();

    createMenuArtFile();
    int selection = interactiveMenu("arte2.txt");
    remove("arte2.txt");

    switch(selection)
    {
        case 0: //new game
        PlaySoundA("LvlSong.wav", NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
        break;
        case 1: //continue game
        PlaySoundA("LvlSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        break;
        case 2: //exit
        PlaySoundA(NULL, NULL, 0); //detiene la musica
        break;
    }

    return selection;
}

inline void stopMusic()
{
    PlaySoundA(NULL, NULL, 0);
}

} 

#endif // MAINMENU_H
