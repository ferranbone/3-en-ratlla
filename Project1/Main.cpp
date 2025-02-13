#include <iostream>
#include "Turnos.h"
#define width 3
#define length 3

using namespace std;

void imprimirTablero(char tablero[width][length]) {
    cout << "+---+---+---+" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < 3; j++) {
            cout << " " << tablero[i][j] << " |"; // Separador de columnas y bordes
        }
        cout << endl;
        cout << "+---+---+---+" << endl; // Separador de filas y bordes
    }
}

int main() {
    char tablero[width][length] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    imprimirTablero(tablero);
    pedirPosicion(tablero, widthPos, lengthPos);

    return 0;
}
