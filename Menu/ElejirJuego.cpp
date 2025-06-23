#include "HambreCeroBiblioteca.h"


// posiciones del borde
const int posicionesBorde[3][2] = {
	{14, ALTO / 2 - 10}, {49, ALTO / 2 - 10}, {ANCHO / 2 - 17, ALTO / 2},
};
int seleccionJuego = 0;

namespace Juegos {
	void DibujarParaElBorde(FiguraAvanzada& figura) {
		for (int i = 0; i < figura.alto; i++) {
			for (int j = 0; j < figura.ancho; j++) {
				wchar_t c = figura.dato[i][j];
				if (c != L' ') {
					int x = figura.posx + j;
					int y = figura.posy + i;

					if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
						pantalla[y][x].simbolo = c;
						ConsoleColor color = figura.funcionColor ? figura.funcionColor(i, j, c) : figura.color;

						pantalla[y][x].color = color;
						Console::ForegroundColor = pantalla[y][x].color;
						Console::SetCursorPosition(x, y);
						Console::Write(pantalla[y][x].simbolo);
					}
				}
			}
		}
	}
	void DibujarFondo() {
		for (int i = 0; i < ALTO; ++i) {
			for (int j = 0; j < ANCHO; ++j) {
				pantalla[i][j].simbolo = L' ';
				pantalla[i][j].color = ConsoleColor::DarkBlue;
				Console::BackgroundColor = pantalla[i][j].color;
				Console::SetCursorPosition(j, i);
				Console::Write(pantalla[i][j].simbolo);
			}
		}
	}
	void DibujarCuadro1() {
		const wchar_t* cuadro1[] = {
			L"╔══════════════════════════════╗",
			L"║             ██               ║",
			L"║            █ █               ║",
			L"║              █               ║",
			L"║              █               ║",
			L"║              █               ║",
			L"║            █████             ║",
			L"╚══════════════════════════════╝"
		};
		int altoCuadro1 = 8;
		int anchoCuadro1 = wcslen(cuadro1[0]);
		FiguraAvanzada figuraCuadro1 = {
			cuadro1,
			altoCuadro1,
			anchoCuadro1,
			15,
			ALTO / 2 - (altoCuadro1 / 2) - 5,
			ConsoleColor::White,
			nullptr
		};
		funciones::DibujarFiguraAvanzada(figuraCuadro1);
	}
	void DibujarCuadro2() {
		const wchar_t* cuadro2[] = {
			L"╔══════════════════════════════╗",
			L"║           █████              ║",
			L"║          ██   ██             ║",
			L"║              ██              ║",
			L"║             ██               ║",
			L"║            ██                ║",
			L"║           ██████             ║",
			L"╚══════════════════════════════╝"
		};
		int altoCuadro2 = 8;
		int anchoCuadro2 = wcslen(cuadro2[0]);
		FiguraAvanzada figuraCuadro2 = {
			cuadro2,
			altoCuadro2,
			anchoCuadro2,
			50,
			ALTO / 2 - (altoCuadro2 / 2) - 5,
			ConsoleColor::White,
			nullptr
		};
		funciones::DibujarFiguraAvanzada(figuraCuadro2);
	}
	void DibujarCuadro3() {
		const wchar_t* cuadro3[] = {
			L"╔══════════════════════════════╗",
			L"║           █████              ║",
			L"║               ██             ║",
			L"║               ██             ║",
			L"║            ████              ║",
			L"║               ██             ║",
			L"║           ██████             ║",
			L"╚══════════════════════════════╝"
		};
		int altoCuadro3 = 8;
		int anchoCuadro3 = wcslen(cuadro3[0]);
		FiguraAvanzada figuraCuadro2 = {
			cuadro3,
			altoCuadro3,
			anchoCuadro3,
			ANCHO / 2 - (anchoCuadro3 / 2),
			ALTO / 2 - (altoCuadro3 / 2) + 5,
			ConsoleColor::White,
			nullptr
		};
		funciones::DibujarFiguraAvanzada(figuraCuadro2);
	}
	void BordeSeleccion() {
		const wchar_t* borde[] = {
			L"██████████████████████████████████",
			L"█                                █",
			L"█                                █",
			L"█                                █",
			L"█                                █",
			L"█                                █",
			L"█                                █",
			L"█                                █",
			L"█                                █",
			L"██████████████████████████████████",
		};
		int altoBorde = 10;
		int anchoBorde = wcslen(borde[0]);
		FiguraAvanzada Bordes{
			borde,
			altoBorde,
			anchoBorde,
			posicionesBorde[seleccionJuego][0],
			posicionesBorde[seleccionJuego][1],
			ConsoleColor::DarkYellow,
			nullptr
		};
		DibujarParaElBorde(Bordes);
	}
	void BorrarBordes() {
		const wchar_t* borrar[] = {
	L"██████████████████████████████████",
	L"█                                █",
	L"█                                █",
	L"█                                █",
	L"█                                █",
	L"█                                █",
	L"█                                █",
	L"█                                █",
	L"█                                █",
	L"██████████████████████████████████",
		};
		int altoBorde = 10;
		int anchoBorde = wcslen(borrar[0]);
		FiguraAvanzada Bordes{
			borrar,
			altoBorde,
			anchoBorde,
			posicionesBorde[seleccionJuego][0],
			posicionesBorde[seleccionJuego][1],
			ConsoleColor::DarkBlue,
			nullptr
		};
		DibujarParaElBorde(Bordes);
	}
	void Volver() {
		const wchar_t* volver[] = {
			L"▓▓▓▓▓▓▓ █ █ ███ █▄█ █▀",
			L"▓▓▓▓▓▓▓ ███ █ █ █ █ █▄",
			L" ██▒██  █ █ ███ █ █ █▄",
			L"Pulsa 'Q' para volver ",
		};
		int altoVolver = 4;
		int anchoVolver = wcslen(volver[0]);
		FiguraAvanzada figuraVolver = {
			volver,
			altoVolver,
			anchoVolver,
			1,
			1,
			ConsoleColor::DarkYellow,
			nullptr
		};
		funciones::DibujarFiguraAvanzada(figuraVolver);
	}
	void Atajos() {
		BordeSeleccion();
		while (true)
		{
			if (_kbhit()) {
				char tecla = _getch();
				switch (tecla)
				{
				case 'q':
					funciones::LiberarPantalla();
					funciones::ResetearConsola();
					Console::Clear();
					currentState = GameState::MenuPrincipal;
					return;
					break;
				case '1':
					BorrarBordes();
					seleccionJuego = 0;
					BordeSeleccion();
					break;
				case '2':
					BorrarBordes();
					seleccionJuego = 1;
					BordeSeleccion();
					break;
				case '3':
					BorrarBordes();
					seleccionJuego = 2;
					BordeSeleccion();
					break;
				case 13:
					Console::Clear();
					if (seleccionJuego == 0) {
						funciones::LiberarPantalla();
						funciones::ResetearConsola();
						Console::Clear();
						currentState = GameState::Juego1;
					}
					else if (seleccionJuego == 1) {
						funciones::LiberarPantalla();
						Console::Clear();
						currentState = GameState::Juego2;
					}
					return;
					break;
				}
			}
		}
	}
	void DibujarOpciones() {
		DibujarFondo();
		DibujarCuadro1();
		DibujarCuadro2();
		DibujarCuadro3();
		Volver();
		funciones::mostrarPantalla();
	}
	void ElejirJuego() {
		Console::Clear();
		DibujarOpciones();
		Atajos();
	}
}