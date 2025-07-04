#include "Juego1.h"
#include "HambreCeroBiblioteca.h"

Celda** Juego1Matriz;
Celda** Juego1FondoMatriz;
FiguraAvanzada cajitas[6];
Inventario inventario[3] = {
	{
		"Botella de agua",
		0,
	},
	{
		"Lata de atun",
		0,
	},
	{
		"Verduras",
		0,
	}
};

const int Juego1ALTO = 40;
const int Juego1ANCHO = 120;
const int ANCHO_TOTAL = 150;

bool mostrarIndicacion = false;

