#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>       // Para PlaySound
#include "../Level1/Archi_h/rlutil.h"

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

// Returns the appropriate color for each character in the ASCII art
int getAsciiColor(char c)
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

// Calculates the visual width of a UTF-8 string (for logo centering)
int visualWidth(const string& str)
{
    int width = 0;
    for (size_t i = 0; i < str.length();)
    {
        width++;
        // Move to the next UTF-8 character
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

// Displays the animated game logo
void showLogo()
{
    // ASCII art logo using string 
    string logo[] = {
        " █████╗     ███████╗    ████████╗    ███████╗    ██████╗     ███╗   ███╗     █████╗     ████████╗    ██╗  ██╗",
        "██╔══██╗    ██╔════╝    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ████╗ ████║    ██╔══██╗    ╚══██╔══╝    ██║  ██║",
        "███████║    █████╗         ██║       █████╗      ██████╔╝    ██╔████╔██║    ███████║       ██║       ███████║",
        "██╔══██║    ██╔══╝         ██║       ██╔══╝      ██╔══██╗    ██║╚██╔╝██║    ██╔══██║       ██║       ██╔══██║",
        "██║  ██║    ██║            ██║       ███████╗    ██║  ██║    ██║ ╚═╝ ██║    ██║  ██║       ██║       ██║  ██║",
        "╚═╝  ╚═╝    ╚═╝            ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝     ╚═╝    ╚═╝  ╚═╝       ╚═╝       ╚═╝  ╚═╝"};
    int numLines = sizeof(logo) / sizeof(logo[0]);
    int maxLen = visualWidth(logo[0]);
    int startY = 15;                              // Initial row for the logo
    int startX = (rlutil::tcols() - maxLen) / 2;  // Horizontal centering

    // Logo reveal animation
    for (int i = 0; i < numLines; ++i)
    {
        rlutil::locate(startX, startY + i);
        string line = logo[i];
        
        // Process each character of the line using string indices
        for (size_t j = 0; j < line.length();)
        {
            int charBytes = 1;
            if ((line[j] & 0x80) == 0)
            {
                charBytes = 1;
            }
            else if ((line[j] & 0xE0) == 0xC0)
            {
                charBytes = 2;
            }
            else if ((line[j] & 0xF0) == 0xE0)
            {
                charBytes = 3;
            }
            else if ((line[j] & 0xF8) == 0xF0)
            {
                charBytes = 4;
            }
            
            // Print the character (all its bytes)
            for (int k = 0; k < charBytes; ++k)
            {
                cout << line[j + k];
            }
            cout.flush();
            j += charBytes;
            rlutil::msleep(5); // Animation speed
        }
    }
}



// Creates the arte2.txt file with the menu and decorative art
void createMenuArtFile()
{
    ofstream menuFile("arte2.txt");
    if (!menuFile)
        return;
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
        " ;  ;         ;   ;        :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+++----------------------------+++",
    };
    
    const int numLines = sizeof(lines) / sizeof(lines[0]);
    for (int i = 0; i < numLines; ++i)
    {
        menuFile << lines[i] << endl;
    }
    menuFile.close();
}

// Function to handle loading saved game
// Returns true if loaded successfully, false if should start new game
bool handleContinueGame() {
    rlutil::cls();
    rlutil::locate(30, 12);
    cout << "Loading saved game...";
    rlutil::msleep(1000);
    
    if (::loadGame()) {
        // Game loaded successfully
        rlutil::locate(30, 14);
        cout << "Game loaded! Returning to level " << ::actualLevel;
        rlutil::msleep(2000);
        return true;
    } else {
        // No save file found, start new game
        rlutil::locate(30, 14);
        cout << "No saved game found. Starting new game...";
        rlutil::msleep(2000);
        playerName = getPlayerName();
        return false;  // Indicates should start from level 1
    }
}

// Shows the interactive menu and allows selecting an option with W/S
// Returns: 0 = New Game, 1 = Continue, 2 = Exit
int interactiveMenu(const char *fileName)
{
    int selectedOption = 0; // Selected option
    int key;
    rlutil::hidecursor();
    displayFile(string(fileName)); // Convert const char* to string
    
    // Initial position of the selector
    rlutil::locate(75, 5 + selectedOption);
    cout << '>'; // Visible selector
    do
    {
        key = rlutil::getkey();
        // Erase previous selector
        rlutil::locate(75, 5 + selectedOption);
        cout << " ";
        switch (key)
        {
        case 'w':
        case 'W':
            selectedOption--;
            if (selectedOption < 0)
                selectedOption = 0;
            break;
        case 's':
        case 'S':
            selectedOption++;
            if (selectedOption > 2)
                selectedOption = 2;
            break;
        }
        // Draw new selector
        rlutil::locate(75, 5 + selectedOption);
        cout << '>';
    } while (key != rlutil::KEY_ENTER);
    
    // Show message based on the chosen option
    rlutil::locate(75, 5 + selectedOption);
    cout << " "; // Erase selector
    rlutil::locate(77, 5);
    
    switch (selectedOption)
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
    return selectedOption;
}

// Main menu function that handles the entire flow
// Returns: 0 = New Game, 1 = Continue, 2 = Exit
int showMainMenu()
{
    SetConsoleOutputCP(CP_UTF8); // UTF-8 console support
    
    // 🔊 Start background music in loop
    if (!PlaySoundA("MenuSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP))
    {
        // Don't show error if the music file is not found
    }
    
    showLogo();                   // Display the animated logo
    rlutil::msleep(3000);         // Wait 3 seconds
    rlutil::cls();                // Clear screen
    createMenuArtFile();          // Create the menu arte2.txt
    int selection = interactiveMenu("arte2.txt"); // Display interactive menu
    remove("arte2.txt");          // Delete temporary file
    
    return selection;
}

// Función para detener la música al salir del juego
void stopMusic()
{
    PlaySoundA(NULL, NULL, 0);
}

} // namespace MainMenu

#endif // MAINMENU_H
