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

// Devuelve el color adecuado para cada caracter del arte ASCII del final
int coloreado(char c)
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

// Crea el archivo de arte ASCII para la pantalla final
void crearArchivoArte()
{
    ofstream archivo("arte.txt");
    if (!archivo)
        return;

    const char *lineas[] = {
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

    for (const char *linea : lineas)
        archivo << linea << "\n";

    archivo.close();
    rlutil::hidecursor();
}

// Muestra el archivo de arte con colores
void mostrarArchivoArte(const char *nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo)
        return;

    char linea[1024];
    while (archivo.getline(linea, sizeof(linea)))
    {
        int longitud = strlen(linea);
        for (int i = 0; i < longitud; ++i)
        {
            rlutil::setColor(coloreado(linea[i]));
            cout << linea[i];
        }
        for (int i = longitud; i < 124; ++i)
        {
            cout << ' ';
        }
        rlutil::resetColor();
        cout << endl;
    }

    archivo.close();
    rlutil::hidecursor();
}

// Dibuja una caja decorativa en consola
void dibujarCaja(int x, int y, int ancho, int alto)
{
    rlutil::setColor(rlutil::WHITE);
    // línea superior
    rlutil::locate(x, y);
    cout << "+";
    for (int i = 0; i < ancho - 2; ++i)
        cout << "-";
    cout << "+";

    // líneas laterales
    for (int i = 1; i < alto - 1; ++i)
    {
        rlutil::locate(x, y + i);
        cout << "|";
        rlutil::locate(x + ancho - 1, y + i);
        cout << "|";
    }

    // línea inferior
    rlutil::locate(x, y + alto - 1);
    cout << "+";
    for (int i = 0; i < ancho - 2; ++i)
        cout << "-";
    cout << "+";

    rlutil::resetColor();
}

// Muestra texto animado en una posición específica
void mostrarTextoAnimadoEnPosicion(const string &texto, int x, int y, int delayMs = 100)
{
    rlutil::locate(x, y);
    for (char c : texto)
    {
        cout << c << flush;
        rlutil::msleep(delayMs);
    }
}

// Muestra la cinemática final con estadísticas del jugador
void mostrarCinematicaFinal()
{
    rlutil::cls();
    rlutil::setColor(rlutil::LIGHTGREEN);
    
    const char *final[] = {
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
        "||                                                                                                               ||"
    };

    for (const char *linea : final)
    {
        cout << linea << endl;
        rlutil::msleep(200);
    }
    
    // Mostrar estadísticas personalizadas
    rlutil::setColor(rlutil::LIGHTCYAN);
    rlutil::locate(15, 16);
    cout << "||              > Hero Name          :     " << MainMenu::playerName;
    for (int i = MainMenu::playerName.length(); i < 50; i++) cout << " ";
    cout << "||";
    
    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(15, 17);
    cout << "||              > Enemies Defeated   :     Many                                                                ||";
    rlutil::locate(15, 18);
    cout << "||              > Bosses Defeated    :     3                                                                   ||";
    rlutil::locate(15, 19);
    cout << "||              > Levels Completed   :     3                                                                   ||";
    rlutil::locate(15, 20);
    cout << "||              > Final Level        :     Master Adventurer                                                   ||";
    
    rlutil::setColor(rlutil::LIGHTGREEN);
    rlutil::locate(15, 21);
    cout << "||                                                                                                               ||";
    rlutil::locate(15, 22);
    cout << "||                                                                                                               ||";
    rlutil::locate(15, 23);
    cout << "||                                                                                                               ||";
    rlutil::locate(15, 24);
    cout << "||                              Thank you for playing, " << MainMenu::playerName << "! See you soon.";
    for (int i = MainMenu::playerName.length(); i < 25; i++) cout << " ";
    cout << "||";
    rlutil::locate(15, 25);
    cout << "||                                                                                                               ||";
    rlutil::locate(15, 26);
    cout << "||                                    Press any key to exit the game...                                        ||";
    rlutil::locate(15, 27);
    cout << "||                                                                                                               ||";
    rlutil::locate(15, 28);
    cout << "===================================================================================================================";
    
    rlutil::resetColor();
    rlutil::anykey();
}

// Calcula offset horizontal para centrar el arte
double obtenerOffsetHorizontalArte(int arteAncho)
{
    int cols = rlutil::tcols();
    return (cols - arteAncho) / 2.0 + 1;
}

// Calcula offset vertical para centrar el arte
double obtenerOffsetVerticalArte(int arteAlto)
{
    int rows = rlutil::trows();
    return (rows - arteAlto) / 2.0 + 1;
}

// Muestra el archivo de arte centrado en la pantalla
void mostrarArchivoArteCentrado(const char *nombreArchivo, int &offsetX, int &offsetY, int &arteAlto, int extraYOffset = 0)
{
    ifstream archivo(nombreArchivo);
    if (!archivo)
        return;
    const int arteAncho = 124;
    arteAlto = 0;
    offsetX = (int)obtenerOffsetHorizontalArte(arteAncho);
    offsetY = (int)obtenerOffsetVerticalArte(48) + extraYOffset;
    string linea;
    while (getline(archivo, linea))
    {
        rlutil::locate(offsetX, offsetY + arteAlto);
        for (char c : linea)
        {
            rlutil::setColor(coloreado(c));
            cout << c;
        }
        rlutil::resetColor();
        cout << endl;
        arteAlto++;
    }
    archivo.close();
    rlutil::hidecursor();
}

// Calcula coordenadas para centrar la caja sobre el arte
void obtenerCoordenadasCajaCentradaSobreArte(int anchoCaja, int altoCaja, int offsetX, int offsetY, int arteAncho, int arteAlto, int &cajaX, int &cajaY)
{
    cajaX = offsetX + (arteAncho - anchoCaja) / 2;
    cajaY = offsetY + (arteAlto - altoCaja) / 2;
}

// Muestra una caja centrada con mensaje sobre el arte
void mostrarCajaCentradaConMensajeSobreArte(const string &mensaje, int offsetX, int offsetY, int arteAncho, int arteAlto, int delayMs = 60)
{
    int anchoCaja = (int)mensaje.size() + 4;
    int altoCaja = 3;
    int cajaX, cajaY;
    obtenerCoordenadasCajaCentradaSobreArte(anchoCaja, altoCaja, offsetX, offsetY, arteAncho, arteAlto, cajaX, cajaY);
    dibujarCaja(cajaX, cajaY, anchoCaja, altoCaja);
    mostrarTextoAnimadoEnPosicion(mensaje, cajaX + 2, cajaY + 1, delayMs);
}

// Función principal que muestra toda la pantalla final
void showFinalScreen()
{
    SetConsoleOutputCP(CP_UTF8);
    
    // Detener la música del juego si está sonando
    MainMenu::stopMusic();
    
    crearArchivoArte();
    int offsetX, offsetY, arteAlto;
    int extraYOffset = 10;
    
    mostrarArchivoArteCentrado("arte.txt", offsetX, offsetY, arteAlto, extraYOffset);
    
    string mensaje = "Congratulations " + MainMenu::playerName + "! You have completed your adventure!";
    mostrarCajaCentradaConMensajeSobreArte(mensaje, offsetX, offsetY, 124, arteAlto);
    
    rlutil::msleep(4000); // espera 4 segundos
    
    mostrarCinematicaFinal();
    
    // Limpiar archivo temporal
    remove("arte.txt");
}

} // namespace FinalScreen

#endif // FINALSCREEN_H
