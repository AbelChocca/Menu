#pragma once
#include "HambreCeroBiblioteca.h"

// Estructuras
struct Inventario {
	std::string insumo;
	int cantidad;
};

//Variables Globals.cpp
extern Celda** Juego1Matriz;
extern Celda** Juego1FondoMatriz;
extern FiguraAvanzada cajitas[6];
extern Inventario inventario[3];
extern Inventario almacen[3];

extern const int Juego1ALTO;
extern const int Juego1ANCHO;
extern const int ANCHO_TOTAL;

extern bool mostrarIndicacion;

extern const wchar_t* indicacion_insumos[];
extern int longitudInsumos;
extern int alturaInsumos;

// Variables Figuras.cpp
extern FiguraAvanzada mark;

extern const int limiteSuperiorJuego;
extern const int limiteInferiorJuego;
extern const int limiteIzquierdoJuego;
extern const int limiteDerechoJuego;

namespace config {
	void mostrarJuego1();
	void configurarConsolaJuego1();
	void InicializarJuego1();
	void LiberarPantalla();
}
namespace condiciones {
	ConsoleColor MarkCondition(int fila, int columna, wchar_t c);
}
namespace figuras {
	void GenerarPared();
	void GenerarCajasRandom();
	void GenerarSuelo();
	void ImprimirInventario();
	void ImprimirIndicacionInsumos();
	void BorrarIndicacionInsumos();

	// Lore
	void DibujarLore();
	void DibujarLore2();
	void DibujarLore3();
	void DibujarLore4();
}
namespace logica {
	void DibujarFiguraJuego(FiguraAvanzada& figura, Celda** matrizDestino);
	bool DetectarColisiones(FiguraAvanzada& jugador);
	bool DetectarJugador(FiguraAvanzada& jugador);
	void GenerarInsumosRandom();
	void AgarrarInsumos();
	bool SalirAlmacen(FiguraAvanzada& mark);
	bool ContadorInsumos();
	void LeerLore();
}