#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#using <System.dll>

using namespace std;
using namespace System;
using namespace System::Media;

// Structs
struct Posicion
{
    int x;
    int y;
};
struct Figura
{   
    const wchar_t** dato;
    int alto;
    int ancho;
    int posx;
    int posy;
};
// Funcion dinamica
struct ColorParametros {
    int fila;
    int columna;
    wchar_t caracter;
};
using FuncionDinamica = ConsoleColor(*)(int fila, int columna, wchar_t c);
struct FiguraAvanzada
{
    const wchar_t** dato;
    int alto;
    int ancho;
    int posx;
    int posy;
    ConsoleColor color;
    FuncionDinamica funcionColor;
};
struct Celda {
    wchar_t simbolo;
    ConsoleColor color;
};

extern int ALTO;
extern int ANCHO;
extern Celda** pantalla;

extern bool salirAnimacion;

// funciones de la animacion de entrada
namespace AnimacionEntrada {
    void EscribirFrase();
    void DibujarFrame2();
    void DibujarFrame3();

    void AnimacionDeEntrada();
}
namespace informacion {
    void ContenidoInformacion();
	ConsoleColor CondicionTitulo(int fila, int columna, wchar_t c);
    void MostrarInformacion();
}


// funciones principales del juego
namespace funciones {
    void ResetearConsola();
    void configurarConsola();
    //Mostrar Pantalla
    void mostrarPantalla();
    // Mostrar frases
    void MostrarFrases(int i);
    // Dibujar Arbol Madre
    ConsoleColor ArbolMadre(int fila, int columna, wchar_t c);
    // Reproducir Audio 
    void ReproducirAudio();
    // Pintar Pinos
    ConsoleColor Pinos(int fila, int columna, wchar_t c);
    // Dibujar bordes de botones
    ConsoleColor Bordes(int fila, int columna, wchar_t c);
    void DibujarFiguraAvanzada(FiguraAvanzada& figura);
    void ElejirOpcion(int opcion, int seleccionDeOpcion, int* configurarEntrada, bool* salirAnimacion);
	void LiberarPantalla();
	void InicializarPantalla();

    void Menu();

}

namespace Juegos {
    void ElejirJuego();
}
namespace PrimerJuego {
    void IniciarJuego();
}
