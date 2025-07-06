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

// Función para calcular el ancho visual de una cadena UTF-8
int visualWidth(const char *str)
{
    int width = 0;
    for (int i = 0; str[i] != '\0';)
    {
        width++;
        // Avanzar al siguiente caracter UTF-8
        if ((str[i] & 0x80) == 0)
        { // ASCII
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
            i += 1; // Caracter inválido, avanzar 1
        }
    }
    return width;
}

void mostrarLogo()
{
    const char *logo[] = {
        " █████╗     ███████╗    ████████╗    ███████╗    ██████╗     ███╗   ███╗     █████╗     ████████╗    ██╗  ██╗",
        "██╔══██╗    ██╔════╝    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ████╗ ████║    ██╔══██╗    ╚══██╔══╝    ██║  ██║",
        "███████║    █████╗         ██║       █████╗      ██████╔╝    ██╔████╔██║    ███████║       ██║       ███████║",
        "██╔══██║    ██╔══╝         ██║       ██╔══╝      ██╔══██╗    ██║╚██╔╝██║    ██╔══██║       ██║       ██╔══██║",
        "██║  ██║    ██║            ██║       ███████╗    ██║  ██║    ██║ ╚═╝ ██║    ██║  ██║       ██║       ██║  ██║",
        "╚═╝  ╚═╝    ╚═╝            ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝     ╚═╝    ╚═╝  ╚═╝       ╚═╝       ╚═╝  ╚═╝"};
    int num_lines = sizeof(logo) / sizeof(logo[0]);
    int max_len = visualWidth(logo[0]);
    int startY = 15;
    int startX = (rlutil::tcols() - max_len) / 2;

    for (int i = 0; i < num_lines; ++i)
    {
        rlutil::locate(startX, startY + i);
        const char *line = logo[i];
        for (int j = 0; line[j] != '\0';)
        {
            int char_bytes = 1;
            if ((line[j] & 0x80) == 0)
            { // ASCII
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

            // Imprimir el caracter (todos sus bytes)
            for (int k = 0; k < char_bytes; ++k)
            {
                cout << line[j + k];
            }
            cout.flush();
            j += char_bytes;

            rlutil::msleep(5); // Ajustar para la velocidad deseada
        }
    }
}

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
    // Ajustamos la posición inicial del selector
    rlutil::locate(75, 5 + i);
    cout << '>'; // Usamos un carácter más compatible

    do
    {
        key = rlutil::getkey();

        // Borramos el selector anterior
        rlutil::locate(75, 5 + i);
        cout << " ";

        switch (key)
        {
        case 'w': // Usamos 'w' y 's' para que sea más intuitivo
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

        // Dibujamos el nuevo selector
        rlutil::locate(75, 5 + i);
        cout << '>';

    } while (key != rlutil::KEY_ENTER);
    switch (i)
    {
    case 2:
        cout << "la aventura puede esperar...";
        rlutil::msleep(1500);
        exit(0);
        break;
    case 1:
        cout << "cargando partida...";
        rlutil::msleep(1500);

        break;
    case 0:
        cout << "la aventura apenas empieza";
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
    SetConsoleOutputCP(CP_UTF8);
    // 🔊 Inicia la música de fondo
    if (!PlaySoundA("MenuSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP))
    {
        cerr << "❌ No se pudo reproducir el archivo musiquitas.wav\n";
    }
    mostrarLogo();

    rlutil::msleep(5000);
    rlutil::cls();

    crearArchivoArte2();
    menuInteractivo("arte2.txt");
    remove("arte2.txt");
    cin.get();

    // 🛑 Detener música al salir completamente del programa
    PlaySoundA(NULL, NULL, 0);

    return 0;
}