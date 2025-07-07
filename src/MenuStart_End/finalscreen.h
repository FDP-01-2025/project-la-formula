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
        ":::*%@@@@@@@%%%###############################################%@@@@@@@%##########################################=:#####",
        "###%%%%%%%%%%%%###########################################%%%%%%%%%%%%%%%%%%#########=:*#########################**#####",
        "%%%%%######%%%%########################=:*###############%%%%%%%%%%%######%%##########*#################################",
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

    string line;
    while (getline(artFile, line))
    {
        int length = line.length();
        for (int i = 0; i < length; ++i)
        {
            rlutil::setColor(getCharColor(line[i]));
            cout << line[i];
        }
        for (int i = length; i < 124; ++i)
        {
            cout << ' ';
        }
        rlutil::resetColor();
        cout << endl;
    }

    artFile.close();
    rlutil::hidecursor();
}

// Draws a decorative box in the console
void drawBox(int x, int y, int width, int height)
{
    rlutil::setColor(rlutil::WHITE);
    // Top line
    rlutil::locate(x, y);
    cout << "+";
    for (int i = 0; i < width - 2; ++i)
        cout << "-";
    cout << "+";

    // Side lines
    for (int i = 1; i < height - 1; ++i)
    {
        rlutil::locate(x, y + i);
        cout << "|";
        rlutil::locate(x + width - 1, y + i);
        cout << "|";
    }

    // Bottom line
    rlutil::locate(x, y + height - 1);
    cout << "+";
    for (int i = 0; i < width - 2; ++i)
        cout << "-";
    cout << "+";

    rlutil::resetColor();
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
    cout << "||              > Enemies Defeated   :     8                                                                  ||";
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

// Calculates horizontal offset to center the art
double getHorizontalArtOffset(int artWidth)
{
    int cols = rlutil::tcols();
    return (cols - artWidth) / 2.0 + 1;
}

// Calculates vertical offset to center the art
double getVerticalArtOffset(int artHeight)
{
    int rows = rlutil::trows();
    return (rows - artHeight) / 2.0 + 1;
}

// Displays the art file centered on the screen
void displayCenteredArtFile(const string& fileName, int &offsetX, int &offsetY, int &artHeight, int extraYOffset = 0)
{
    ifstream artFile(fileName);
    if (!artFile)
        return;
    const int artWidth = 124;
    artHeight = 0;
    offsetX = (int)getHorizontalArtOffset(artWidth);
    offsetY = (int)getVerticalArtOffset(48) + extraYOffset;
    string line;
    while (getline(artFile, line))
    {
        rlutil::locate(offsetX, offsetY + artHeight);
        for (char c : line)
        {
            rlutil::setColor(getCharColor(c));
            cout << c;
        }
        rlutil::resetColor();
        cout << endl;
        artHeight++;
    }
    artFile.close();
    rlutil::hidecursor();
}

// Calculates coordinates to center the box over the art
void getBoxCoordinatesCenteredOverArt(int boxWidth, int boxHeight, int offsetX, int offsetY, int artWidth, int artHeight, int &boxX, int &boxY)
{
    boxX = offsetX + (artWidth - boxWidth) / 2;
    boxY = offsetY + (artHeight - boxHeight) / 2;
}

// Displays a centered box with a message over the art
void displayCenteredBoxWithMessageOverArt(const string &message, int offsetX, int offsetY, int artWidth, int artHeight, int delayMs = 60)
{
    int boxWidth = (int)message.size() + 4;
    int boxHeight = 3;
    int boxX, boxY;
    getBoxCoordinatesCenteredOverArt(boxWidth, boxHeight, offsetX, offsetY, artWidth, artHeight, boxX, boxY);
    drawBox(boxX, boxY, boxWidth, boxHeight);
    displayAnimatedTextAtPosition(message, boxX + 2, boxY + 1, delayMs);
}

// Main function that displays the entire final screen
void showFinalScreen()
{
    SetConsoleOutputCP(CP_UTF8);
    
    // Stop the game music if it's playing
    MainMenu::stopMusic();
    
    createArtFile();
    int offsetX, offsetY, artHeight;
    int extraYOffset = 10;
    
    string artFileName = "arte.txt";
    displayCenteredArtFile(artFileName, offsetX, offsetY, artHeight, extraYOffset);
    
    string message = "Congratulations " + MainMenu::playerName + "! You have completed your adventure!";
    displayCenteredBoxWithMessageOverArt(message, offsetX, offsetY, 124, artHeight);
    
    rlutil::msleep(4000); // wait 4 seconds
    
    displayFinalCinematic();
    
    // Clean up temporary file
    remove(artFileName.c_str());
}

} // namespace FinalScreen

#endif // FINALSCREEN_H
