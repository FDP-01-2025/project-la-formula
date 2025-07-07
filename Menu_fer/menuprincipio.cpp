#include <iostream>  // Entrada/salida estándar
#include <fstream>   // Manejo de archivos
#include <cstring>   // Funciones de cadenas C
#include <windows.h> // Funciones específicas de Windows
#include "rlutil.h"  // Librería para manejo de consola
using namespace std; // Uso de std para simplificar el código

// Devuelve el color adecuado para cada caracter del arte ASCII
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

// Calcula el ancho visual de una cadena UTF-8 (para centrar el logo)
int visualWidth(const char *str)
{
    int width = 0;
    for (int i = 0; str[i] != '\0';)
    {
        width++;
        // Avanza al siguiente caracter UTF-8
        if ((str[i] & 0x80) == 0)
        {
            i += 1;
        } // ASCII
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
            i += 1;
        } // Caracter inválido
    }
    return width;
}

// Muestra el logo animado y centrado
void mostrarLogo()
{
    // Logo en arte ASCII
    const char *logo[] = {
        " █████╗     ███████╗    ████████╗    ███████╗    ██████╗     ███╗   ███╗     █████╗     ████████╗    ██╗  ██╗",
        "██╔══██╗    ██╔════╝    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ████╗ ████║    ██╔══██╗    ╚══██╔══╝    ██║  ██║",
        "███████║    █████╗         ██║       █████╗      ██████╔╝    ██╔████╔██║    ███████║       ██║       ███████║",
        "██╔══██║    ██╔══╝         ██║       ██╔══╝      ██╔══██╗    ██║╚██╔╝██║    ██╔══██║       ██║       ██╔══██║",
        "██║  ██║    ██║            ██║       ███████╗    ██║  ██║    ██║ ╚═╝ ██║    ██║  ██║       ██║       ██║  ██║",
        "╚═╝  ╚═╝    ╚═╝            ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝     ╚═╝    ╚═╝  ╚═╝       ╚═╝       ╚═╝  ╚═╝"};
    int num_lines = sizeof(logo) / sizeof(logo[0]);
    int max_len = visualWidth(logo[0]);
    int startY = 15;                              // Fila inicial para el logo
    int startX = (rlutil::tcols() - max_len) / 2; // Centrado horizontal

    // Animación de aparición del logo
    for (int i = 0; i < num_lines; ++i)
    {
        rlutil::locate(startX, startY + i);
        const char *line = logo[i];
        for (int j = 0; line[j] != '\0';)
        {
            int char_bytes = 1;
            if ((line[j] & 0x80) == 0)
            {
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
            // Imprime el caracter (todos sus bytes)
            for (int k = 0; k < char_bytes; ++k)
            {
                cout << line[j + k];
            }
            cout.flush();
            j += char_bytes;
            rlutil::msleep(5); // Velocidad de animación
        }
    }
}

// Crea el archivo arte2.txt con el menú y arte decorativo
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

// Muestra el arte o menú desde un archivo, coloreando cada caracter
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

// Muestra el menú interactivo y permite seleccionar una opción con W/S
void menuInteractivo(const char *nombreArchivo)
{
    int i = 0; // Opción seleccionada
    int key;
    rlutil::hidecursor();
    mostrarArchivo(nombreArchivo);
    // Posición inicial del selector
    rlutil::locate(75, 5 + i);
    cout << '>'; // Selector visible
    do
    {
        key = rlutil::getkey();
        // Borra el selector anterior
        rlutil::locate(75, 5 + i);
        cout << " ";
        switch (key)
        {
        case 'w':
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
        // Dibuja el nuevo selector
        rlutil::locate(75, 5 + i);
        cout << '>';
    } while (key != rlutil::KEY_ENTER);
    // Acción según la opción elegida
    switch (i)
    {
    case 2:
        cout << "The adventure can wait...";
        rlutil::msleep(1500);
        exit(0);
        break;
    case 1:
        cout << "Loading game...";
        rlutil::msleep(1500);
        break;
    case 0:
        cout << "Rhe adventure begins!...";
        rlutil::msleep(1500);
        break;
    default:
        break;
    }
    rlutil::resetColor();
    rlutil::cls();
}

// Función principal: muestra logo, menú y maneja la música
int main()
{
    SetConsoleOutputCP(CP_UTF8); // Soporte UTF-8 en consola
    //  Inicia la música de fondo en loop
    if (!PlaySoundA("MenuSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP))
    {
        cerr << " No se pudo reproducir el archivo musiquitas.wav\n";
    }
    mostrarLogo();                // Muestra el logo animado
    rlutil::msleep(5000);         // Espera 5 segundos
    rlutil::cls();                // Limpia pantalla
    crearArchivoArte2();          // Crea el menú arte2.txt
    menuInteractivo("arte2.txt"); // Muestra menú interactivo
    remove("arte2.txt");          // Borra archivo temporal
    cin.get();                    // Espera entrada
    //  Detener música al salir completamente del programa
    PlaySoundA(NULL, NULL, 0);
    return 0;
}