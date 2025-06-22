//Crear un menu de pausa, con menu de salir, guardar partida, reanudar

//NOTA:
//Pasar a inglés luego de ver que el codigo esté correcto 

#include <iostream>
#include <string>

using namespace std;

void mostrarMenuPausa() { //Declaro el struct tipo Menu de pausa
    cout << "========= PAUSA =========" <<endl;
    cout << "|1. Reanudar            |" << endl;
    cout << "|2. Salir del juego     |"<< endl;
    cout << "=========================" << endl;
    cout << "Seleccione una opcion: ";
}

void guardarPartida() { //Declaro struct de tipo Guardar partida

    cout << "Guardando partida..." << endl; // Simular proceso de guardado
  
    cout << "Partida guardada exitosamente!" << endl; //Experiencia del usuario, para que no se vea chueco
}

int main() {
    bool juegoEnPausa = true;
    bool juegoCorriendo = true;

    cout << "Juego iniciado..." << endl; //Aqui tendría que ir como tal el juego, o sea, el codigo para que runee

    while (juegoCorriendo) {
        // Simular el juego en ejecución
        cout << "Presione 'p' para pausar el juego: " << endl;
        char entrada;
        cin >> entrada;

        if (entrada !='p'){
            cout << "Ingrese la letra correspondiente" << endl;
        }
        else if (entrada == 'p' || entrada == 'P') {   //Aqui se validan las posibles entradas de datos del usuario
            juegoEnPausa = true;
            while (juegoEnPausa) {
                mostrarMenuPausa();

                int opcion;
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        cout << "Reanudando juego..." << endl;
                        juegoEnPausa = false;
                        break;
                    case 2:
                        cout << "Desea guardar la partida antes de salir? (s/n): ";
                        char guardar;
                        cin >> guardar;

                        if (guardar == 's' || guardar == 'S') { //Posibles ingresos de variables del usuario
                            guardarPartida();
                        } else {
                            cout << "No se guardo la partida." << endl;   //Caso alterno si algo sale mal
                        }

                        cout << "Saliendo del juego..." << endl;
                        juegoCorriendo = false;
                        juegoEnPausa = false;
                        break;
                    default:
                        cout << "Opción no válida. Intente de nuevo.\n";
                }
            }
        }
    }

    cout << "Juego finalizado." << endl;
    return 0;
}
