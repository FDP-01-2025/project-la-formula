
#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include "rlutil.h"
using namespace std;

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


void crearArchivoArte()
{
    ofstream archivo("arte.txt");
    if (!archivo)
        return;

    const char *lineas[] = {
        "",
    };

    for (const char *linea : lineas)
        archivo << linea << "\n";

    archivo.close();
    rlutil::hidecursor;
}

void crearArchivoArte2()
{
    ofstream archivo("arte2.txt");
    if (!archivo)
        return;

    const char *lineas[] = {
        "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+++----------------------------+++",
        "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |          M E N U           | |",
        "._              ___%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |----------------------------| |",
        ".*' .*        _.-*\".*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "(   (       .-' .' (    __%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |   [1] New game             | |",
        " .   `-._.-*   /    `-*'  `*-.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |   [2] Continue game        | |",
        "-._.*        _.-'        .-.    `-.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |   [3] Exit                 | |",
        "          .-'         _.'   `-._   `-.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "\\       .'                      `*-.__`-._%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |----------------------------| |",
        "    _.._    /       -.                \"\"\";%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |    Use W S to move         | |",
        ".'-._ `. :   :      `.         :      `+.    ;%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "/     `. \\:    \\           `-.   \\ `-.    \\%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        ":        \\ ;  \\  ;    `. `.    \\   `.__\\;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |    ENTER to confirm        | |",
        "          ;;   ;     `-.  \\ _.-:*\"'   `:`._:%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "       .-*:  ' :   \\    ;;-*'\"*.       .-,%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "      '   :  ; ;   /:.-'        `        ;%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "          ; /     :     _.--s+.        .s:%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        ":        / :  :   ;    \\   dPT$b.    \\d$PTb%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
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
        "     .-'/`      \\            /%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "   .'  /  \\      `._        :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "  /  .'    `.   .-*'        ;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " :  :        \\   \\         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " ;  ;         ;   ;        :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+++----------------------------+++",
    };

    for (const char *linea : lineas)
        archivo << linea << "\n";

    archivo.close();
}

void mostrarArchivo(const char *nombreArchivo)
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

void menuInteractivo(const char *nombreArchivo)
{
    int i = 0;
    int key;
    rlutil::hidecursor();

    mostrarArchivo(nombreArchivo); 
    rlutil::locate(75, 4 + i);
    cout << (char)175;
 
    do
    {
        key = rlutil::getkey();

        
        rlutil::locate(75, 4 + i);
        cout << " ";

        switch (key)
        {
        case 119: 
        case 87:
            i--;
            if (i < 0) i = 0;
            break;

        case 115: 
        case 83:
            i++;
            if (i > 2) i = 2;
            break;
        }

        
        rlutil::locate(75, 4 + i);
        cout << (char)175;

    } while (key != rlutil::KEY_ENTER);
    switch (i)
    {
    case 2:
        cout<<"la aventura puede esperar...";
        rlutil::msleep(1500);
        exit(0);
        break;
    case 1:
    cout<<"cargando partida...";
    rlutil::msleep(1500);
    
    break;
    case 0:
    cout<<"la aventura apenas empieza";
    rlutil::msleep(1500);
    break;
    
    default:
        break;
    }

    rlutil::resetColor();
    rlutil::cls();
    
}


int main()
{
    // 🔊 Inicia la música de fondo
    if (!PlaySoundA("MenuSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP)) {
        cerr << "❌ No se pudo reproducir el archivo musiquitas.wav\n";
    }

    crearArchivoArte();
    crearArchivoArte2();

    mostrarArchivo("arte.txt");
    cin.ignore();
    rlutil::cls();

    menuInteractivo("arte2.txt");
    cin.get();

    // 🛑 Detener música al salir completamente del programa
    PlaySoundA(NULL, NULL, 0);

    return 0;
}