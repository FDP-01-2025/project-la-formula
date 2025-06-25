#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Muestra el menú de pausa
void mostrarMenuPausa() {
    cout << "========= PAUSA =========" << endl;
    cout << "|1. Reanudar            |" << endl;
    cout << "|2. Guardar partida     |" << endl;
    cout << "|3. Salir del juego     |" << endl;
    cout << "=========================" << endl;
    cout << "Seleccione una opcion: ";
}

// Pide el nombre al usuario y guarda los datos en un archivo de texto
void guardarPartida() {
    string nombreJugador;
    int puntaje = 150;

    cout << "Ingrese su nombre para guardar la partida: ";
    cin >> nombreJugador;

    // Validación básica: no aceptar nombre vacío
    while (nombreJugador.empty()) {
        cout << "El nombre no puede estar vacío. Intente de nuevo: ";
        cin >> nombreJugador;
    }

    ofstream archivo("partida_guardada.txt");
    if (archivo.is_open()) {
        archivo << "Nombre: " << nombreJugador << endl;
        archivo << "Puntaje: " << puntaje << endl;
        archivo.close();
        cout << "Partida guardada exitosamente en 'partida_guardada.txt'!" << endl;
    } else {
        cout << "Error al guardar la partida." << endl;
    }
}

int main() {
    bool juegoEnPausa = false;
    bool juegoCorriendo = true;

    cout << "Juego iniciado..." << endl;

    while (juegoCorriendo) {
        char entrada;

        // Solo acepta 'p' o 'P'
        cout << "Presione 'p' para pausar el juego: ";
        cin >> entrada;
        while (entrada != 'p' && entrada != 'P') {
            cout << "Entrada inválida. Solo se acepta 'p': ";
            cin >> entrada;
        }

        juegoEnPausa = true;

        while (juegoEnPausa) {
            mostrarMenuPausa();

            int opcion;
            cin >> opcion;

            while (opcion < 1 || opcion > 3) {
                cout << "Opción inválida. Ingrese 1, 2 o 3: ";
                cin >> opcion;
            }

            switch (opcion) {
                case 1:
                    cout << "Reanudando juego..." << endl;
                    juegoEnPausa = false;
                    break;

                case 2:
                    guardarPartida();
                    break;

                case 3: {
                    char guardar;
                    cout << "¿Desea guardar la partida antes de salir? (s/n): ";
                    cin >> guardar;

                    while (guardar != 's' && guardar != 'S' && guardar != 'n' && guardar != 'N') {
                        cout << "Respuesta inválida. Ingrese 's' o 'n': ";
                        cin >> guardar;
                    }

                    if (guardar == 's' || guardar == 'S') {
                        guardarPartida();
                    } else {
                        cout << "No se guardó la partida." << endl;
                    }

                    cout << "Saliendo del juego..." << endl;
                    juegoCorriendo = false;
                    juegoEnPausa = false;
                    break;
                }
            }
        }
    }

    cout << "Juego finalizado." << endl;
    return 0;
}

