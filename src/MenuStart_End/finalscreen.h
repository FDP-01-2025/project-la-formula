#ifndef FINALSCREEN_H
#define FINALSCREEN_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include "Level1/Archi_h/rlutil.h"
#include "mainmenu.h"

using namespace std;

namespace FinalScreen {

// Returns the appropriate color for each character in the ASCII art
int getCharColor(char c)
{
    switch (c)
    {
    case '.':
    case ':':
        return rlutil::YELLOW;
    case '#':
        return rlutil::MAGENTA;
    case '%':
    case '@':
        return rlutil::BLACK;
    case '=':
    case '|':
    case '+':
    case '-':
        return rlutil::WHITE;
    default:
        return rlutil::DARKGREY;
    }
}

// Creates the ASCII art file for the final screen
void createArtFile()
{
    ofstream artFile("arte.txt");
    if (!artFile)
        return;

    string lines[] = {
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

    for (const string& line : lines)
        artFile << line << "\n";

    artFile.close();
    rlutil::hidecursor();
}

// Displays the art file with colors
void displayArtFile(const string& fileName)
{
    ifstream artFile(fileName);
    if (!artFile)
        return;

    string artWidthStr = "124"; // Usando string en lugar de constante
    int artWidth = stoi(artWidthStr); // Convertir a entero para usar en el bucle
    
    string line;
    while (getline(artFile, line))
    {
        int length = line.length();
        for (int i = 0; i < length; ++i)
        {
            rlutil::setColor(getCharColor(line[i]));
            cout << line[i];
        }
        for (int i = length; i < artWidth; ++i) // Usando la variable convertida
        {
            cout << ' ';
        }
        rlutil::resetColor();
        cout << endl;
    }

    artFile.close();
    rlutil::hidecursor();
}


// Displays animated text at a specific position
void displayAnimatedTextAtPosition(const string &text, int x, int y, int delayMs = 100)
{
    rlutil::locate(x, y);
    for (char c : text)
    {
        cout << c << flush;
        rlutil::msleep(delayMs);
    }
}

// Displays the final cinematic with player statistics
void displayFinalCinematic()
{
    rlutil::cls();
    rlutil::setColor(rlutil::LIGHTGREEN);

    string finalArt[] = {
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

    for (const string& line : finalArt)
    {
        cout << line << endl;
        rlutil::msleep(200);
    }

    // Mostrar estadísticas personalizadas
    rlutil::setColor(rlutil::LIGHTCYAN);
    rlutil::locate(1, 16);
    cout << "||              > Hero Name          :     " << MainMenu::playerName;
    for (int i = MainMenu::playerName.length(); i < 70; i++) cout << " ";
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
    for (int i = MainMenu::playerName.length(); i < 43; i++) cout << " ";
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
    // Esperar a que el usuario presione una tecla
    cout << endl << "Presiona cualquier tecla para continuar..." << flush;
    cin.get();
}



// Displays the art file



// Main function that displays the entire final screen
void showFinalScreen()
{
    SetConsoleOutputCP(CP_UTF8);

    // Stop the game music if it's playing
    MainMenu::stopMusic();

    createArtFile();
    
    string artFileName = "arte.txt";
    // Mostrar el arte 
    displayArtFile(artFileName);

    // Pausa breve para que el usuario vea el arte
    rlutil::msleep(3000); // esperar 3 segundos

    displayFinalCinematic();

    // Clean up temporary file
    remove(artFileName.c_str());
}

} // namespace FinalScreen

#endif // FINALSCREEN_H