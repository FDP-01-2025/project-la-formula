#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "rlutil.h"
using namespace std;

int colorear(char c)
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
    default: return rlutil::BLACK;
    }
}

void crearArchivoArte2()
{
    ofstream archivo("arte2.txt");
    if (!archivo) return;

    const char *lineas[] = {
        "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%++------------------------------++",
        "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |          M E N U           | |",
        "._              ___%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |----------------------------| |",
        ".*' .*        _.-*\".*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "(   (       .-' .' (    __%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |   [1] New game             | |",
        " .   `-._.-*   /    `-*'  `*-.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |   [2] Continue game        | |",
        "-._.*        _.-'        .-.    `-.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |   [3] Exit                 | |",
        "          .-'         _.'   `-._   `-.%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "\\       .'                      `*-.__`-._%%%%%%%%%%%%%%%%%%%%%%%%%%%| |----------------------------| |",
        "    _.._    /       -.                \"\"\";%%%%%%%%%%%%%%%%%%%%%%%%%| |    Use W S to move         | |",
        ".'-._ `. :   :      `.         :      `+.    ;%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "/     `. \\:    \\           `-.   \\ `-.    \\%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        ":        \\ ;  \\  ;    `. `.    \\   `.__\\;%%%%%%%%%%%%%%%%%%%%%%%%%| |    ENTER to confirm        | |",
        "          ;;   ;     `-.  \\ _.-:*\"'   `:`._:%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "       .-*:  ' :   \\    ;;-*'\"*.       .-,%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "      '   :  ; ;   /:.-'        `        ;%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "          ; /     :     _.--s+.        .s:%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        ":        / :  :   ;    \\   dPT$b.    \\d$PTb%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "\\     .'  ;  ;   ;     `.:$bd$$$b    `Tbd$%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " `._.'   /  /    :       `*^^^^*' ,    `T$%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " .-'    : .'      \\                      `-._%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "/      .+'         \\                         \\%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        ":      /            \\`._                       ;%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "      :          `.  ;                        /%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "              ;    \\ :              ;  ,s*' .'%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "        '    /      :;              `. '   (%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "       /   .'       :                   .-*-*.%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "  .'   /      /    /            ._.'   _.---(%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " /    :    .-'   .'         '      *--*\"      :%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        ":         /     /`.                `-.__.--._.'%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "               :   `.                       ;%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "         '     ;     `-.                    :%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "        /;     :        `---..._______...--*'%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "     .-'/`      \\            /%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "   .'  /  \\      `._        :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        "  /  .'    `.   .-*'        ;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " :  :        \\   \\         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%| |                            | |",
        " ;  ;         ;   ;        :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%++----------------------------++",
    };

    for (const char *linea : lineas)
        archivo << linea << "\n";

    archivo.close();
}

void mostrarArchivo(const char* nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir " << nombreArchivo << endl;
        return;
    }

    vector<string> lineas;
    string linea;
    size_t maxLong = 0;

    // Leer todas las líneas y calcular la longitud máxima
    while (getline(archivo, linea)) {
        if (linea.length() > maxLong)
            maxLong = linea.length();
        lineas.push_back(linea);
    }
    archivo.close();

    // Imprimir línea por línea, rellenando con espacios
    for (const auto& l : lineas) {
        for (size_t i = 0; i < l.length(); ++i) {
            rlutil::setColor(colorear(l[i]));
            cout << l[i];
        }
        // Relleno con espacios si hace falta
        for (size_t i = l.length(); i < maxLong; ++i) {
            cout << ' ';
        }
        rlutil::resetColor();
        cout << endl;
    }
}

int main()
{
    crearArchivoArte2();
    mostrarArchivo("arte2.txt");

    cout << "\nPresiona ENTER para salir...";
    cin.get();
    return 0;
}
