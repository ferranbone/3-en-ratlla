#include <iostream>
#define width 3
#define length 3

void pedirPosicion(char tablero[width][length], int widthPos, int lengthPos) {
	bool posCorrect = false;
	while (!posCorrect)
	{
		std::cout << "Dime donde quieres tirar" << std::endl;
		std::cin >> widthPos;
		std::cin >> lengthPos;
		if ((widthPos >= 0 && widthPos <= 2) && (lengthPos >= 0 && lengthPos <= 2)) {
			if (tablero[widthPos][lengthPos] = ' ') {
				posCorrect = true;
			}
			else {
				std::cout << "Posisicon ocupada" << std::endl;
			}
		}
		else {
			std::cout << "Posicion no valida" << std::endl;
		}
	}
}

void ponerPieza(char tablero[width][length], int widthPos, int lengthPos, bool turno) {
	if (!turno) {
		tablero[widthPos][lengthPos] = 'X';
	}
	if (turno) {
		tablero[widthPos][lengthPos] = 'O';
	}
}