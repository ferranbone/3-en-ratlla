#pragma once
#include <iostream>
#include <cstdlib>
#define width 3
#define length 3

void pedirPosicion(char tablero[width][length], int& widthPos, int& lengthPos);
void ponerPieza(char tablero[width][length], int widthPos, int lengthPos, bool turno);
bool Victoria(char tablero[width][length], char ficha);
bool estaLleno(char tablero[width][length]);
void iaJuega(char tablero[width][length]);