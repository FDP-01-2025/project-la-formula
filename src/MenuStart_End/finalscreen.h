#ifndef FINALSCREEN_H
#define FINALSCREEN_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "../Level1/Archi_h/rlutil.h"
#include "mainmenu.h"

using namespace std;

namespace FinalScreen {

// Función para obtener el color según el carácter
inline int getCharColor(char c)
{
    switch (c)
    {
    case '.':
    case ':': return rlutil::YELLOW;
    case '#': return rlutil::MAGENTA;
    case '%':
    case '@': return rlutil::BLACK;
    case '=':
    case '|':
    case '+':
    case '-': return rlutil::WHITE;
    default:  return rlutil::DARKGREY;
    }
}

// Crea el archivo de arte final
inline void createArtFile()
{
    ofstream artFile("arte.txt");
    if (!artFile) return;

    const string lines[] = {
        "####::::################################################################################################################",
        "#####::###################################::############################################################################",
        "#########################################::::##############################::######################.....*#%#############",
        "#######################################::::::::###########################::::#####################%:....=*%%######%%###",
        "%%%%%%%%%%%%%%%##########################::::###########################::::::::###################%+-.....=*%#####=+%##",
        "%%%%%%%%%%%%%%%###########################::##############################::::######################%#......:=#%###=+%##",
        "@@@%%+=====*%%%############################################################::########################*........*#########",
        "@@@%#::::::+%%%######################################################################################*........*#########",
        "@@@%#-:::::+%%%###########::########################################################################-:.......:*#########",
        "%%%%%######%%%%##########::::#################################::####################################:........:*#########",
        "%%%%%######%%%%########::::::::##############################::::#############################***..........::-*#########",
        "@@@%#-:::::+%%%##########::::##############################::::::::##########################*:..........::-+###########",
        "@@@%#::::::+%%%###########::#################################::::##############################=--:.....:-=#############",
        "@@@%%+=====*%%%###############################################::##################################*======###############",
        "%%%%%%%%%%%%%%%#########################################################################################################",
        "++=#%%@@@@@%%%%###########=-##################################%%#####%%#################################################",
        ":::*%@@@@@@@%%%###########++##################################%@%%%%%@%#################################################",
        ":::*%@@@@@@@%%%################################________________________________________##########################=:#####",
        "###%%%%%%%%%%%%################################|CONGRATULATIONS! The adventure is over|##########################**#####",
        "%%%%%######%%%%########################=:*#####----------------------------------------#################################",
        "@@@%#::::::+%%%##########################################%%@@@@@%%%=:::::-%%####################################%#######",
        "@@@%%=====-*%%%##########################################%%@@@@@%%%+-=====%%###################################%@@@@@@@@",
        "%%%%%%%%%%%%%%%###########################################%%%%%%%%%%%%%%%%%%################################%%%%%%%%%%%%",
        "%%%%%++++++#%%%###########################################%%%%%%%%%%%%%%%%%%#####################%%%%%%#####%%%#++++*@%%",
        "@@@%#::::::+%%%###########################################%%%%%%%%%*++++++%%################%%%%%@@@@@@@%###%%%*:::.=@%%",
        "@@@%#::::::+%%%###########################################%@@@@@%%%=.:::::%%################@@@@@@@@@@@@@###%%%#****#%%%",
        "%%%%%******#%%%###########################################%%%%%%%%%#******%%################@@@%%@@%@@%@@###%%%%%%%%%%%%",
        "%%%%%%%%%%%%%%%###########################################%%%%%%%%%%%%%%%%%%################@@@@@@@@@@@@@###%%%%%%%%%%%%",
        "---*%@@@@@@%%%%#################################*#########%#####%%%%%%%%%%%%################@@@%%@@%@@%@@###%%%*---:=@%%",
        ":::*%@@@@@@@%%%################################+:+########%-::::#%%@@@@@@@%%################@@@@@@@@@@@@@###%%%#----+@%%",
        "==-#%@@@@@@%%%%###########################################%=---=#%%%@@@@@@%%################@@@%%@@%@@%@@###%%%%%%%%%%%%",
    };
<<<<<<< HEAD
    
    for (const string& line : lines)
        artFile << line << "\n";
=======

    for (const auto& line : lines)
        artFile << line << '\n';
>>>>>>> 5c0c3c76dd4ffac18f572dfe2fb67c5bf7e5fae4

    artFile.close();
    rlutil::hidecursor();
}

// Muestra el contenido del archivo de arte coloreando cada carácter
inline void displayArtFile(const string& fileName)
{
    ifstream artFile(fileName);
    if (!artFile) return;

<<<<<<< HEAD
    string artWidthStr = "124"; // Usando string 
    int artWidth = stoi(artWidthStr); // Convertir a entero para usar en el bucle
    
=======
    const int artWidth = 124;
>>>>>>> 5c0c3c76dd4ffac18f572dfe2fb67c5bf7e5fae4
    string line;

    while (getline(artFile, line))
    {
        int length = (int)line.length();
        for (int i = 0; i < length; ++i)
        {
            rlutil::setColor(getCharColor(line[i]));
            cout << line[i];
        }
        for (int i = length; i < artWidth; ++i)
            cout << ' ';
        rlutil::resetColor();
        cout << endl;
    }

    artFile.close();
    rlutil::hidecursor();
}

// Dibuja un cuadro decorativo en consola
inline void drawBox(int x, int y, int width, int height)
{
    rlutil::setColor(rlutil::WHITE);

<<<<<<< HEAD
// Displays animated text at a specific position

=======
    rlutil::locate(x, y);
    cout << '+';
    for (int i = 0; i < width - 2; ++i) cout << '-';
    cout << '+';

    for (int i = 1; i < height - 1; ++i)
    {
        rlutil::locate(x, y + i);
        cout << '|';
        rlutil::locate(x + width - 1, y + i);
        cout << '|';
    }

    rlutil::locate(x, y + height - 1);
    cout << '+';
    for (int i = 0; i < width - 2; ++i) cout << '-';
    cout << '+';

    rlutil::resetColor();
}

// Muestra texto animado en posición dada
inline void displayAnimatedTextAtPosition(const string& text, int x, int y, int delayMs = 100)
{
    rlutil::locate(x, y);
    for (char c : text)
    {
        cout << c << flush;
        rlutil::msleep(delayMs);
    }
}
>>>>>>> 5c0c3c76dd4ffac18f572dfe2fb67c5bf7e5fae4

// Centra el arte horizontalmente y devuelve offset
inline int getHorizontalArtOffset(int artWidth)
{
    int cols = rlutil::tcols();
    return (cols - artWidth) / 2 + 1;
}

// Centra el arte verticalmente y devuelve offset
inline int getVerticalArtOffset(int artHeight)
{
    int rows = rlutil::trows();
    return (rows - artHeight) / 2 + 1;
}

// Estructura para posición y tamaño del arte
struct ArtPosition {
    int offsetX;
    int offsetY;
    int height;
};

// Muestra el arte centrado y devuelve su posición
inline ArtPosition displayCenteredArtFile(const string& fileName, int extraYOffset = 0)
{
    ArtPosition artPos{0, 0, 0};

    ifstream artFile(fileName);
    if (!artFile) return artPos;

    const int artWidth = 124;
    artPos.offsetX = getHorizontalArtOffset(artWidth);
    artPos.offsetY = getVerticalArtOffset(48) + extraYOffset;

    string line;
    while (getline(artFile, line))
    {
        rlutil::locate(artPos.offsetX, artPos.offsetY + artPos.height);
        for (char c : line)
        {
            rlutil::setColor(getCharColor(c));
            cout << c;
        }
        rlutil::resetColor();
        cout << endl;
        artPos.height++;
    }

    artFile.close();
    rlutil::hidecursor();

    return artPos;
}

// Estructura para coordenadas de cuadro
struct BoxCoordinates {
    int x;
    int y;
};

// Calcula coordenadas para centrar cuadro sobre arte
inline BoxCoordinates getBoxCoordinatesCenteredOverArt(int boxWidth, int boxHeight, int offsetX, int offsetY, int artWidth, int artHeight)
{
    return {
        offsetX + (artWidth - boxWidth) / 2,
        offsetY + (artHeight - boxHeight) / 2
    };
}

// Muestra un cuadro centrado con mensaje animado
inline void displayCenteredBoxWithMessageOverArt(const string& message, int offsetX, int offsetY, int artWidth, int artHeight, int delayMs = 60)
{
    int boxWidth = (int)message.size() + 4;
    int boxHeight = 3;

    BoxCoordinates boxCoords = getBoxCoordinatesCenteredOverArt(boxWidth, boxHeight, offsetX, offsetY, artWidth, artHeight);

    drawBox(boxCoords.x, boxCoords.y, boxWidth, boxHeight);
    displayAnimatedTextAtPosition(message, boxCoords.x + 2, boxCoords.y + 1, delayMs);
}

// Muestra la cinemática final con estadísticas y mensaje final
inline void displayFinalCinematic()
{
    rlutil::cls();
    rlutil::setColor(rlutil::LIGHTGREEN);

    const string finalArt[] = {
        "===================================================================================================================",
        "||                                                                                                               ||",
        "||                                                                                                               ||",
        "||  █████╗     ███████╗    ████████╗    ███████╗    ██████╗     ███╗   ███╗     █████╗     ████████╗    ██╗  ██╗ ||",
        "|| ██╔══██╗    ██╔════╝    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ████╗ ████║    ██╔══██╗    ╚══██╔══╝    ██║  ██║ ||",
        "|| ███████║    █████╗         ██║       █████╗      ██████╔╝    ██╔████╔██║    ███████║       ██║       ███████║ ||",
        "|| ██╔══██║    ██╔══╝         ██║       ██╔══╝      ██╔══██╗    ██║╚██╔╝██║    ██╔══██║       ██║       ██╔══██║ ||",
        "|| ██║  ██║    ██║            ██║       ███████╗    ██║  ██║    ██║ ╚═╝ ██║    ██║  ██║       ██║       ██║  ██║ ||",
        "|| ╚═╝  ╚═╝    ╚═╝            ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝     ╚═╝    ╚═╝  ╚═╝       ╚═╝       ╚═╝  ╚═╝ ||",
        "||                                                                                                               ||",
        "||                                                                                                               ||",
        "||===============================================================================================================||",
        "||                                                                                                               ||",
        "||                                    == G  A  M  E    S  U  M  M  A  R  Y ==                                    ||",
        "||                                                                                                               ||",
    };

    for (const auto& line : finalArt)
    {
        cout << line << endl;
        rlutil::msleep(200);
    }

    // Estadísticas (modifica aquí para actualizar según tu juego)
    rlutil::setColor(rlutil::LIGHTCYAN);
    rlutil::locate(1, 16);
    cout << "||              > Hero Name          :     " << MainMenu::playerName;
    for (size_t i = MainMenu::playerName.length(); i < 70; ++i) cout << ' ';
    cout << "||";

    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(1, 17);
    cout << "||              > Enemies Defeated   :     8                                                                     ||";
    rlutil::locate(1, 18);
    cout << "||              > Bosses Defeated    :     3                                                                     ||";
    rlutil::locate(1, 19);
    cout << "||              > Levels Completed   :     3                                                                     ||";
    rlutil::locate(1, 20);
    cout << "||              > Final Level        :     Master Adventurer                                                     ||";

    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(1, 21);
    cout << "||                                                                                                               ||";
    rlutil::locate(1, 22);
    cout << "||                                                                                                               ||";
    rlutil::locate(1, 23);
    cout << "||                                                                                                               ||";
    rlutil::locate(1, 24);
    cout << "||                              Thank you for playing, " << MainMenu::playerName << "! See you soon.";
    for (size_t i = MainMenu::playerName.length(); i < 43; ++i) cout << ' ';
    cout << "||";

    rlutil::locate(1, 25);
    cout << "||                                                                                                               ||";
    rlutil::locate(1, 26);
    cout << "||                                    Press any key to exit the game...                                          ||";
    rlutil::locate(1, 27);
    cout << "||                                                                                                               ||";
    rlutil::locate(1, 28);
    cout << "===================================================================================================================";

    rlutil::resetColor();

    cout << endl << "Press any key to continue..." << flush;
    cin.get();
}

// Función principal para mostrar la pantalla final
inline void showFinalScreen()
{
    SetConsoleOutputCP(CP_UTF8);

    // Detener música si está sonando
    MainMenu::stopMusic();

    createArtFile();

    constexpr int extraYOffset = 10;
    constexpr int artWidth = 124;

    // Mostrar arte centrado y obtener posición
    ArtPosition artPos = displayCenteredArtFile("arte.txt", extraYOffset);

    // Mostrar mensaje centrado con animación
    string message = "Congratulations " + MainMenu::playerName + "! You have completed your adventure!";
    displayCenteredBoxWithMessageOverArt(message, artPos.offsetX, artPos.offsetY, artWidth, artPos.height);

    rlutil::msleep(4000);

    displayFinalCinematic();

    remove("arte.txt");
}

} // namespace FinalScreen

#endif // FINALSCREEN_H
