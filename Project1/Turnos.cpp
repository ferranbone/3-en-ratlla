#include <iostream>
#include <cstdlib>
#define width 3
#define length 3

void pedirPosicion(char tablero[width][length], int& widthPos, int& lengthPos) {
	bool posCorrect = false;
	while (!posCorrect) {
		std::cout << "Dime donde quieres tirar (fila columna): ";
		std::cin >> widthPos >> lengthPos;

		widthPos -= 1;
		lengthPos -= 1;

		if ((widthPos >= 0 && widthPos <= 2) && (lengthPos >= 0 && lengthPos <= 2)) {
			if (tablero[widthPos][lengthPos] == ' ') {
				posCorrect = true;
			}
			else {
				std::cout << "Posicion ocupada, elige otra.\n";
			}
		}
		else {
			std::cout << "Posicion no valida, elige entre 0 y 2.\n";
		}
	}
}

void ponerPieza(char tablero[width][length], int widthPos, int lengthPos, bool turno) {
	if (turno) {
		tablero[widthPos][lengthPos] = 'O';
	}
	else {
		tablero[widthPos][lengthPos] = 'X';
	}
}

bool Victoria(char tablero[width][length], char ficha) {
	// Comprobar filas y columnas
	for (int i = 0; i < 3; i++) {
		if ((tablero[i][0] == ficha && tablero[i][1] == ficha && tablero[i][2] == ficha) || // Filas
			(tablero[0][i] == ficha && tablero[1][i] == ficha && tablero[2][i] == ficha))   // Columnas
		{
			return true;
		}
	}

	// Comprobar diagonales
	if ((tablero[0][0] == ficha && tablero[1][1] == ficha && tablero[2][2] == ficha) || // Diagonal principal
		(tablero[0][2] == ficha && tablero[1][1] == ficha && tablero[2][0] == ficha))   // Diagonal inversa
	{
		return true;
	}

	return false;
}

bool estaLleno(char tablero[width][length]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tablero[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}

void iaJuega(char tablero[width][length]) {
	int x, y;
	bool posValida = false;

	while (!posValida) {
		x = rand() % 3; // Número aleatorio entre 0 y 2
		y = rand() % 3;
		if (tablero[x][y] == ' ') {
			tablero[x][y] = 'O';
			posValida = true;
		}
	}
}