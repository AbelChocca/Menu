#pragma once
#include <iostream>
#include <windows.h>

using namespace std;
using namespace System;

struct Celda {
    wchar_t simbolo;
    ConsoleColor color;
};

extern int ALTO;
extern int ANCHO;
extern Celda** pantalla;


namespace funciones {
	// Dibujar todo tipo de figura
    void DibujarFigura(Celda** pantalla, int altoPantalla, int anchoPantalla, const wchar_t* figura[], int alto, int ancho, int posX, int posY, ConsoleColor color) {
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                wchar_t c = figura[i][j];
                if (c != L' ') {
                    if (posY + i >= 0 && posY + i < altoPantalla && posX + j >= 0 && posX + j < anchoPantalla) {
                        pantalla[posY + i][posX + j].simbolo = c;
                        pantalla[posY + i][posX + j].color = color;
                    }
                }
            }
        }
    }
    void LiberarPantalla(int alto) {
        for (int i = 0; i < alto; ++i)
            delete[] pantalla[i];
        delete[] pantalla;
    }

}

