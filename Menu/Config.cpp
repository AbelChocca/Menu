#include "HambreCeroBiblioteca.h"
#include "Juego1.h"

namespace config {
	void mostrarJuego1() {
		for (int i = 0; i < Juego1ALTO; i++) {
			for (int j = 0; j < ANCHO_TOTAL; j++) {
				Console::ForegroundColor = Juego1Matriz[i][j].color;
				Console::SetCursorPosition(j, i);
				Console::Write(Juego1Matriz[i][j].simbolo);
			}
		}
	}
	void configurarConsolaJuego1() {
		Console::SetBufferSize(ANCHO_TOTAL, Juego1ALTO);
		Console::SetWindowSize(ANCHO_TOTAL, Juego1ALTO);
		Console::CursorVisible = false;
	}
	void InicializarJuego1() {
		Juego1Matriz = new Celda * [Juego1ALTO];
		for (int i = 0; i < Juego1ALTO; i++) {
			Juego1Matriz[i] = new Celda[ANCHO_TOTAL];
			for (int j = 0; j < ANCHO_TOTAL; ++j) {
				Juego1Matriz[i][j].simbolo = L' ';
				Juego1Matriz[i][j].color = ConsoleColor::Black;
			}
		}

		Juego1FondoMatriz = new Celda * [Juego1ALTO];
		for (int i = 0; i < Juego1ALTO; i++) {
			Juego1FondoMatriz[i] = new Celda[ANCHO_TOTAL];
			for (int j = 0; j < ANCHO_TOTAL; ++j) {
				Juego1FondoMatriz[i][j].simbolo = L' ';
				Juego1FondoMatriz[i][j].color = ConsoleColor::Black;
			}
		}
	}
	void LiberarPantalla() {
		for (int i = 0; i < Juego1ALTO; i++) {
			delete[] Juego1Matriz[i];
			delete[] Juego1FondoMatriz[i];
		}
		delete[] Juego1FondoMatriz;
		delete[] Juego1Matriz;
	}
}