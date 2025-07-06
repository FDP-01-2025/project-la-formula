#include <iostream>
#include <fstream>
#include <cstring>
#include "rlutil.h"
#include <windows.h>

using namespace std;

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

// Nueva función para dibujar la caja en consola
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

void mostrarTextoAnimadoEnPosicion(const string &texto, int x, int y, int delayMs = 100)
{
    rlutil::locate(x, y);
    for (char c : texto)
    {
        cout << c << flush;
        rlutil::msleep(delayMs);
    }
}

void mostrarCinematicaFinal()
{
    rlutil::cls();
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
        "||                                                                                                               ||",
        "||              > Enemies Defeated   :     9                                                                     ||",
        "||              > Bosses Defeated    :     3                                                                     ||",
        "||              > Level Reached      :     12                                                                    ||",
        "||              > Total Play Time    :     XXh XXm XXs                                                           ||",
        "||                                                                                                               ||",
        "||                                                                                                               ||",
        "||                                                                                                               ||",
        "||                                    Thank you for playing! See you soon.                                       ||",
        "||                                                                                                               ||",
        "===================================================================================================================",
    };

    for (const char *linea : final)
    {
        cout << linea << endl;
        rlutil::msleep(250);
    }

    rlutil::anykey();
}

// Imprime el arte ASCII centrado en la ventana de la consola
double obtenerOffsetHorizontalArte(int arteAncho)
{
    int cols = rlutil::tcols();
    return (cols - arteAncho) / 2.0 + 1;
}
double obtenerOffsetVerticalArte(int arteAlto)
{
    int rows = rlutil::trows();
    return (rows - arteAlto) / 2.0 + 1;
}

// Permite bajar el arte y la caja una cantidad de líneas (offset vertical extra)
void mostrarArchivoArteCentrado(const char *nombreArchivo, int &offsetX, int &offsetY, int &arteAlto, int extraYOffset = 0)
{
    ifstream archivo(nombreArchivo);
    if (!archivo)
        return;
    const int arteAncho = 124;
    arteAlto = 0;
    offsetX = (int)obtenerOffsetHorizontalArte(arteAncho);
    offsetY = (int)obtenerOffsetVerticalArte(48) + extraYOffset; // suma el offset extra
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

// Calcula las coordenadas para centrar la caja sobre el arte ASCII centrado en la ventana
void obtenerCoordenadasCajaCentradaSobreArte(int anchoCaja, int altoCaja, int offsetX, int offsetY, int arteAncho, int arteAlto, int &cajaX, int &cajaY)
{
    cajaX = offsetX + (arteAncho - anchoCaja) / 2;
    cajaY = offsetY + (arteAlto - altoCaja) / 2;
}

void mostrarCajaCentradaConMensajeSobreArte(const string &mensaje, int offsetX, int offsetY, int arteAncho, int arteAlto, int delayMs = 60)
{
    int anchoCaja = (int)mensaje.size() + 4;
    int altoCaja = 3;
    int cajaX, cajaY;
    obtenerCoordenadasCajaCentradaSobreArte(anchoCaja, altoCaja, offsetX, offsetY, arteAncho, arteAlto, cajaX, cajaY);
    dibujarCaja(cajaX, cajaY, anchoCaja, altoCaja);
    mostrarTextoAnimadoEnPosicion(mensaje, cajaX + 2, cajaY + 1, delayMs);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    crearArchivoArte();
    int offsetX, offsetY, arteAlto;
    int extraYOffset = 10; // Ahora baja dos líneas más respecto al valor anterior
    mostrarArchivoArteCentrado("arte.txt", offsetX, offsetY, arteAlto, extraYOffset);
    mostrarCajaCentradaConMensajeSobreArte("Congratulations on beating the game. Starting summary...", offsetX, offsetY, 124, arteAlto);
    rlutil::msleep(3000); // espera 3 segundos
    mostrarCinematicaFinal();
    return 0;
}
