#include "HambreCeroBiblioteca.h"

const int Juego1ALTO = 40;
const int Juego1ANCHO = 120;
Celda** Juego1Matriz;
Celda** Juego1FondoMatriz;

FiguraAvanzada cajitas[6];

bool mostrarIndicacion = false;

// Indicacion global
const wchar_t* indicacion[] = {
	L"Pulsa 'Q' para agarrar"
};
int longitudIndicacion = wcslen(indicacion[0]);
int alturaIndicacion = 1;

// Personaje principal
ConsoleColor MarkCondition(int fila, int columna, wchar_t c) {
	if (c == L'█') return ConsoleColor::DarkYellow;
	if (c == L'▓') return ConsoleColor::Blue;
	if (fila == 3) return ConsoleColor::DarkBlue;
	return ConsoleColor::DarkBlue;
}
const wchar_t* MarkIdle[] = {
	L" ██ ",
	L"▓▓▓▓",
	L"█▓▓█",
	L" ▓▓ ",
	L" ▒▒ ",
};
int longitudMark = wcslen(MarkIdle[0]);
FiguraAvanzada mark = {
	MarkIdle,
	5,
	longitudMark,
	1,
	32,
	ConsoleColor::DarkYellow,
	MarkCondition
};

namespace PrimerJuego {
	void configurarConsolaJuego1() {
		Console::SetBufferSize(Juego1ANCHO, Juego1ALTO);
		Console::SetWindowSize(Juego1ANCHO, Juego1ALTO);
		Console::CursorVisible = false;
	}
	void InicializarJuego1() {
		Juego1Matriz = new Celda * [Juego1ALTO];
		for (int i = 0; i < Juego1ALTO; i++) {
			Juego1Matriz[i] = new Celda[Juego1ANCHO];
			for (int j = 0; j < Juego1ANCHO; ++j) {
				Juego1Matriz[i][j].simbolo = L' ';
				Juego1Matriz[i][j].color = ConsoleColor::Black;
			}
		}

		Juego1FondoMatriz = new Celda * [Juego1ALTO];
		for (int i = 0; i < Juego1ALTO; i++) {
			Juego1FondoMatriz[i] = new Celda[Juego1ANCHO];
			for (int j = 0; j < Juego1ANCHO; ++j) {
				Juego1FondoMatriz[i][j].simbolo = L' ';
				Juego1FondoMatriz[i][j].color = ConsoleColor::Black;
			}
		}
	}
	void mostrarJuego1() {
		for (int i = 0; i < Juego1ALTO; i++) {
			for (int j = 0; j < Juego1ANCHO; j++) {
				Console::ForegroundColor = Juego1Matriz[i][j].color;
				Console::SetCursorPosition(j, i);
				Console::Write(Juego1Matriz[i][j].simbolo);
			}
		}
	}
	void DibujarFiguraJuego(FiguraAvanzada& figura, Celda** matrizDestino) {
		for (int i = 0; i < figura.alto; i++) {
			for (int j = 0; j < figura.ancho; j++) {
				wchar_t c = figura.dato[i][j];
				if (c != L' ') {
					int x = figura.posx + j;
					int y = figura.posy + i;

					if (y >= 0 && y < Juego1ALTO && x >= 0 && x < Juego1ANCHO) {
						matrizDestino[y][x].simbolo = c;
						ConsoleColor color = figura.funcionColor ? figura.funcionColor(i, j, c) : figura.color;

						matrizDestino[y][x].color = color;
					}
				}
			}
		}
	}
	ConsoleColor ParedCondicion(int fila, int columna, wchar_t c) {
		if (c == L'░') return ConsoleColor::DarkGray;
		else if (c == L'█') return ConsoleColor::Cyan;
		return ConsoleColor::Gray;
	}
	void GenerarSuelo() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < Juego1ANCHO; j++) {
				int posy = 30 + i;
				Juego1FondoMatriz[posy][j].simbolo = L'█';
				Juego1FondoMatriz[posy][j].color = ConsoleColor::DarkGray;
			}
		}
	}
	void GenerarPared() {
		const wchar_t* pared[] = {
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒░░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒░░▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒░░▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▓████▓████▓▒▒▒▒▒▒▒░░▒▒▒▒▒▒▓████▓████▓▒▒▒▒▒▒░░▒▒▒▒▒▓████▓████▓▒▒▒▒▒░░▒▒▒▓████▓████▓▒▒░░▒▓████▓████▓▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒░░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒░░▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒░░▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▓████▓████▓▒▒▒▒▒▒▒░░▒▒▒▒▒▒▓████▓████▓▒▒▒▒▒▒░░▒▒▒▒▒▓████▓████▓▒▒▒▒▒░░▒▒▒▓████▓████▓▒▒░░▒▓████▓████▓▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒░░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒░░▒▒▒▓▓▓▓▓▓▓▓▓▓▓▒▒░░▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓▓▓▓▓▓▓▓▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓██████▓▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓██████▓▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓██████▓▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓██████▓▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓██████▓▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓██████▓▒▒",
			L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓██████▓▒▒",
		};
		int longitud = wcslen(pared[0]);
		int altura = 30;
		FiguraAvanzada Pared{
			pared,
			altura,
			longitud,
			0,
			0,
			ConsoleColor::Gray,
			ParedCondicion
		};
		DibujarFiguraJuego(Pared, Juego1FondoMatriz);
	}
	void GenerarCajasRandom() {
		const wchar_t* caja[] = {
			L"▓▓▓▓▓▓▓",
			L"▓▒▒▓▒▒▓",
			L"▓▒▒▓▒▒▓",
			L"▓▓▓▓▓▓▓",
		};
		Random f;
		int longitud = wcslen(caja[0]);
		for (int i = 0; i < 6; i++) {
			int posx = f.Next(10, 95);
			int posy = f.Next(26, 33);

			FiguraAvanzada Cajita{
				caja,
				4,
				longitud,
				posx,
				posy,
				ConsoleColor::DarkYellow,
				nullptr,
			};
			cajitas[i] = Cajita;
			DibujarFiguraJuego(Cajita, Juego1FondoMatriz);
		}
	}
	void ImprimirIndicacion() {
		for (int i = 0; i < alturaIndicacion; i++) {
			for (int j = 0; j < longitudIndicacion; j++) {
				int posx = (Juego1ANCHO / 2 - (longitudIndicacion / 2)) + j;
				int posy = Juego1ALTO - 8;

				Console::ForegroundColor = ConsoleColor::DarkYellow;
				Console::SetCursorPosition(posx, posy);
				Console::Write(indicacion[i][j]);
			}
		}
	}
	void BorrarIndicacion() {
		for (int i = 0; i < alturaIndicacion; i++) {
			for (int j = 0; j < longitudIndicacion; j++) {
				int posx = (Juego1ANCHO / 2 - (longitudIndicacion / 2)) + j;
				int posy = Juego1ALTO - 8;

				Console::ForegroundColor = Juego1FondoMatriz[posy][posx].color;
				Console::SetCursorPosition(posx, posy);
				Console::Write(Juego1FondoMatriz[posy][posx].simbolo);
			}
		}
	}
	void BorrarFrameJugador(FiguraAvanzada& jugador) {
		for (int i = 0; i < jugador.alto; i++) {
			for (int j = 0; j < jugador.ancho; j++) {
				int posx = jugador.posx + j;
				int posy = jugador.posy + i;

				if (posy >= 0 && posy < Juego1ALTO && posx >= 0 && posx < Juego1ANCHO) {
					wchar_t character = Juego1FondoMatriz[posy][posx].simbolo;
					ConsoleColor color = Juego1FondoMatriz[posy][posx].color;

					Console::ForegroundColor = color;
					Console::SetCursorPosition(posx, posy);
					Console::Write(character);
				}
			}
		}
	}
	void DibujarMark(FiguraAvanzada& mark) {
		for (int i = 0; i < mark.alto; i++) {
			for (int j = 0; j < mark.ancho; j++) {
				wchar_t c = mark.dato[i][j];
				if (c != L' ') {
					int x = mark.posx + j;
					int y = mark.posy + i;

					if (x >= 0 && x < Juego1ANCHO && y >= 0 && y < Juego1ALTO) {
						Console::ForegroundColor = mark.funcionColor ? mark.funcionColor(i, j, c) : mark.color;
						Console::SetCursorPosition(x, y);
						Console::Write(c);
					}
				}
			}
		}
	}
	bool DetectarColisiones(FiguraAvanzada& jugador) {
		for (int i = 0; i < 6; i++) {
			int caja_derecha = cajitas[i].posx + cajitas[i].ancho - 1;
			int caja_izquierda = cajitas[i].posx;
			int caja_arriba = cajitas[i].posy;
			int caja_abajo = cajitas[i].posy + cajitas[i].alto - 1;

			int jugador_derecha = jugador.posx + jugador.ancho - 1;
			int jugador_izquierda = jugador.posx;
			int jugador_abajo = jugador.posy + jugador.alto - 1;
			int jugador_arriba = jugador.posy;

			if (!(jugador_derecha < caja_izquierda ||
				jugador_izquierda > caja_derecha ||
				jugador_arriba > caja_abajo ||
				jugador_abajo < caja_arriba)) {
				return true;
			}

		}
		return false;
	}
	void RenderizarPantalla() {
		if (mostrarIndicacion) {
			ImprimirIndicacion();
		}
		else {
			BorrarIndicacion();
		}
		DibujarMark(mark);
	}

	void ConfigurarPrimerNivel() {
		configurarConsolaJuego1();
		InicializarJuego1();
		GenerarSuelo();
		GenerarPared();
		GenerarCajasRandom();
		
		for (int i = 0; i < Juego1ALTO; ++i) {
			for (int j = 0; j < Juego1ANCHO; ++j) {
				Juego1Matriz[i][j] = Juego1FondoMatriz[i][j];
			}
		}

		mostrarJuego1();
		RenderizarPantalla();
	}
	void IniciarJuego() {
		ConfigurarPrimerNivel();
		const int limiteSuperiorJuego = 25; 
		const int limiteInferiorJuego = Juego1ALTO - mark.alto;
		const int limiteIzquierdoJuego = 0;
		const int limiteDerechoJuego = Juego1ANCHO - mark.ancho;

		const int VELOCIDAD = 1;
		
		while (true) { // Reemplaza 'true' con una condición de fin de nivel
			// 1. Procesar entrada del usuario
			int mark_old_posx = mark.posx;
			int mark_old_posy = mark.posy;
			if (_kbhit()) {
				char tecla = _getch();
				// Lógica para mover el jugador, etc.
				switch (tecla)
				{
				case 13:
					// Si el jugador presiona 'q' para volver al menú
					funciones::LiberarPantalla(); // Liberar recursos del juego
					funciones::ResetearConsola();
					Console::Clear();
					currentState = GameState::SeleccionJuego; // O GameState::MenuPrincipal
					return; // Sale de BucleJuegoNivel1
					break;
				case 'w':
					BorrarFrameJugador(mark);
					mark.posy -= VELOCIDAD;
					break;
				case 's':
					BorrarFrameJugador(mark);
					mark.posy += VELOCIDAD;
					break;
				case 'd':
					BorrarFrameJugador(mark);
					mark.posx += VELOCIDAD;
					break;
				case 'a':
					BorrarFrameJugador(mark);
					mark.posx -= VELOCIDAD;
					break;
				}
			}


			bool colisiones_cajas = DetectarColisiones(mark);
			bool colisiones_bordes = false;
			if (mark.posy < limiteSuperiorJuego || mark.posy > limiteInferiorJuego
				|| mark.posx > limiteDerechoJuego || mark.posx < limiteIzquierdoJuego) {
				colisiones_bordes = true;
			}
			if (colisiones_cajas || colisiones_bordes) {
				mark.posx = mark_old_posx;
				mark.posy = mark_old_posy;
				mostrarIndicacion = true;

			}
			else {
				mostrarIndicacion = false;
			}
			// 2. Actualizar el estado del juego
			// ... (mover jugador, enemigos, detectar colisiones, etc.)

			// 3. Dibujar/Renderizar
			// Solo redibujar los elementos que cambian.
			// La matriz Juego1Matriz ya tiene las paredes, suelo y cajas.
			// Solo necesitas dibujar el jugador, enemigos, etc., y luego mostrar la pantalla.
			// Para dibujar:
			// BorrarJugadorAnterior();
			// DibujarJugadorNuevo();
			// Mostrar elementos de la UI (puntaje, vida)
			RenderizarPantalla();

			Sleep(50);
		}
	}
}