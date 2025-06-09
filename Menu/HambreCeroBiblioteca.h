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
// Posiciones de los pinos
const Posicion posicionesPinos[6] = {
    {1, 16},
    {10, 14},
    {20, 15},
    {30, 17},
    {40, 18},
    {50, 19}
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

//Liberar Pantalla
void LiberarPantalla(int alto);
// Incializar Pantalla
void InicializarPantalla(int alto, int ancho);

// funciones de la animacion de entrada
namespace AnimacionEntrada {
    void EscribirFrase();
    void DibujarFrame2();
    void DibujarFrame3();

    void AnimacionDeEntrada();
}
namespace informacion {
    void TituloInformacion();
	ConsoleColor CondicionTitulo(int fila, int columna, wchar_t c);
    void MostrarInformacion();
}


// funciones principales del juego
namespace funciones {
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
    

}

