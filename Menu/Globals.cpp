#include "Juego1.h"
#include "HambreCeroBiblioteca.h"

Celda** Juego1Matriz;
Celda** Juego1FondoMatriz;
FiguraAvanzada cajitas[6];
Inventario almacen[3] = {
	{
	"Botella de agua",
		0,
	},
	{
		"Lata de atún",
		0,
	},
	{
		"Verduras",
		0,
	}
};
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
const wchar_t* indicacion_insumos[] = {
	L"No tienes insumos suficientes"
};
int longitudInsumos = wcslen(indicacion_insumos[0]);
int alturaInsumos = 1;

const int Juego1ALTO = 40;
const int Juego1ANCHO = 120;
const int ANCHO_TOTAL = 150;

bool mostrarIndicacion = false;

