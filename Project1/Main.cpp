#include <iostream>
#include <cstdlib>  
#include <ctime>
#include <fstream>
#include <string>
#include "Turnos.h"
#define width 3
#define length 3

using namespace std;

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    cout << "\nMenu Principal:\n";
    cout << "1. Fer una nova partida\n";
    cout << "2. Carregar una partida guardada\n";
    cout << "3. Sortir del joc\n";
}

// Función para inicializar una nueva partida
void iniciarNuevaPartida(char tablero[width][length]) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            tablero[i][j] = ' ';  // Tablero vacío
        }
    }
    cout << "S'ha iniciat una nova partida.\n";
}

// Función para cargar una partida
bool cargarPartida(char tablero[width][length]) {
    string saveName;
    cout << "Introduce el nombre del archivo para cargar (sin extension): ";
    cin >> saveName;

    if (saveName == "menu") {
        return false; // Volver al menú
    }

    ifstream archivoCargar(saveName + ".tictacsave");

    if (!archivoCargar.is_open()) {
        cout << "No se encontro el archivo. Intenta nuevamente." << endl;
        return false;
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            char c;
            archivoCargar >> c;
            tablero[i][j] = (c == '_') ? ' ' : c;  // Convertimos '_' de vuelta a espacio ' '
        }
    }

    cout << "Partida cargada con exito." << endl;
    return true;
}


void mostrarMenuGameplay() {
    cout << "\nOpcions:\n";
    cout << "1. Collocar una fitxa\n";
    cout << "2. Guardar partida\n";
    cout << "3. Tornar al menu principal\n";
}

// Función para guardar la partida
void guardarPartida(char tablero[width][length]) {
    string saveName;
    cout << "Introduce el nombre del archivo para guardar (sin extension): ";
    cin >> saveName;

    if (saveName == "menu") {
        cout << "El nombre 'menu' no esta permitido." << endl;
        return;
    }

    ifstream archivoExistente(saveName + ".tictacsave");
    if (archivoExistente.is_open()) {
        char respuesta;
        cout << "El archivo ya existe. ¿Quieres sobrescribirlo? (s/n): ";
        cin >> respuesta;

        if (respuesta == 'n' || respuesta == 'N') {
            cout << "Operacion cancelada. El archivo no ha sido sobrescrito." << endl;
            return;
        }
    }

    ofstream archivoGuardar(saveName + ".tictacsave");

    if (archivoGuardar.is_open()) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++) {
                archivoGuardar << (tablero[i][j] == ' ' ? '_' : tablero[i][j]) << " ";
                // Guardamos '_' en lugar de espacios para evitar problemas
            }
            archivoGuardar << endl;
        }
        cout << "Partida guardada con exito en " << saveName << ".tictacsave" << endl;
    }
    else {
        cout << "Error al guardar la partida." << endl;
    }
}

void imprimirTablero(char tablero[width][length]) {
    system("cls");
    cout << "+---+---+---+" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < 3; j++) {
            cout << " " << tablero[i][j] << " |";
        }
        cout << endl;
        cout << "+---+---+---+" << endl;
    }
}

int main() {
    srand(time(0));  // Inicializa la semilla para rand()

    bool salir = false;

    while (!salir) {
        mostrarMenuPrincipal();
        int opcion;
        cin >> opcion;

        switch (opcion) {
        case 1: {  // Nueva partida
            char tablero[width][length] = {
                {' ', ' ', ' '},
                {' ', ' ', ' '},
                {' ', ' ', ' '}
            };

            int widthPos = 0, lengthPos = 0;
            bool turnoJugador = true;
            bool gameOver = false;

            while (!gameOver) {
                imprimirTablero(tablero);
                mostrarMenuGameplay();

                int opcionGameplay;
                cout << "Elige una opcion: ";
                cin >> opcionGameplay;

                switch (opcionGameplay) {
                case 1:  // Colocar una ficha
                    if (turnoJugador) {
                        cout << "Turno del jugador (X)" << endl;
                        pedirPosicion(tablero, widthPos, lengthPos);
                        ponerPieza(tablero, widthPos, lengthPos, false); // false para 'X'

                        if (Victoria(tablero, 'X')) {
                            imprimirTablero(tablero);
                            cout << "¡Has ganado!" << endl;
                            gameOver = true;
                        }
                    }
                    else {
                        cout << "Turno de la IA (O)" << endl;
                        iaJuega(tablero);

                        if (Victoria(tablero, 'O')) {
                            imprimirTablero(tablero);
                            cout << "La IA ha ganado." << endl;
                            gameOver = true;
                        }
                    }

                    // Si el tablero está lleno, se reinicia
                    if (estaLleno(tablero)) {
                        imprimirTablero(tablero);
                        cout << "Empate, se reinicia la partida." << endl;
                        // Reiniciar tablero
                        for (int i = 0; i < 3; i++) {
                            for (int j = 0; j < 3; j++) {
                                tablero[i][j] = ' ';
                            }
                        }
                    }

                    // Cambiar turno
                    turnoJugador = !turnoJugador;
                    break;

                case 2:  // Guardar la partida
                    guardarPartida(tablero);
                    break;

                case 3:  // Volver al menú principal
                    cout << "Volviendo al menú principal..." << endl;
                    gameOver = true;
                    break;

                default:
                    cout << "Opcion no valida." << endl;
                }
            }
            break;
        }

        case 2: {  // Cargar partida
            char tablero[width][length];

            if (cargarPartida(tablero)) {
                cout << "Continuando la partida guardada...\n";

                int widthPos = 0, lengthPos = 0;
                bool turnoJugador = true;
                bool gameOver = false;

                while (!gameOver) {
                    imprimirTablero(tablero);
                    mostrarMenuGameplay();

                    int opcionGameplay;
                    cout << "Elige una opcion: ";
                    cin >> opcionGameplay;

                    switch (opcionGameplay) {
                    case 1:  // Colocar una ficha
                        if (turnoJugador) {
                            cout << "Turno del jugador (X)" << endl;
                            pedirPosicion(tablero, widthPos, lengthPos);
                            ponerPieza(tablero, widthPos, lengthPos, false); // false para 'X'

                            if (Victoria(tablero, 'X')) {
                                imprimirTablero(tablero);
                                cout << "¡Has ganado!" << endl;
                                gameOver = true;
                            }
                        }
                        else {
                            cout << "Turno de la IA (O)" << endl;
                            iaJuega(tablero);

                            if (Victoria(tablero, 'O')) {
                                imprimirTablero(tablero);
                                cout << "La IA ha ganado." << endl;
                                gameOver = true;
                            }
                        }

                        // Si el tablero está lleno, se reinicia
                        if (estaLleno(tablero)) {
                            imprimirTablero(tablero);
                            cout << "Empate, se reinicia la partida." << endl;
                            // Reiniciar tablero
                            for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                    tablero[i][j] = ' ';
                                }
                            }
                        }

                        // Cambiar turno
                        turnoJugador = !turnoJugador;
                        break;

                    case 2:  // Guardar la partida
                        guardarPartida(tablero);
                        break;

                    case 3:  // Volver al menú principal
                        cout << "Volviendo al menu principal..." << endl;
                        gameOver = true;
                        break;

                    default:
                        cout << "Opción no valida." << endl;
                    }
                }
            }
            break;
        }

        case 3:  // Salir del juego
            cout << "Saliendo del juego... ¡Hasta la proxima!" << endl;
            salir = true;
            break;

        default:
            cout << "Opcion no valida. Intentalo de nuevo.\n";
        }
    }

    return 0;
}