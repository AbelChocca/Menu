#include "../HambreCeroBiblioteca.h"

namespace AnimacionEntrada {
	void LimpiarFrame() {
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < ANCHO; ++j) {
				pantalla[i + 7][j].simbolo = L' ';
				pantalla[i + 7][j].color = ConsoleColor::Black;
			}
		}
	}
	void DibujarFrame2() {
		const wchar_t* silla[] = {
			L"                                                              ",
			L"                              ▒▒▒▒▒▒▒▒▒                       ",
			L"                             ▒▒▓▓▓▓▓▓                         ",
			L"                             ▓▓▓▓▓▓▓▓▓                        ",
			L" ███████████████   ▓▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓                         ",
			L" ███████████████ ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                         ",
			L" ██████████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  ▓▓▓      ▓▓           ▓▓     ",
			L" █████████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓ ▓▓▓        ▓▓▓▓▓▓▓▓▓▓▓▓▓      ",
			L" ████████████▓▓▓▓▓▓▓▓▓▓▓    ▓▓▓▓▓▓████████████████████████    ",
			L" ███████████▓▓▓▓▓▓▓▓▓▓▓         ██████████████████████████    ",
			L" ███████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓     ███     ███          █████    ",
			L" ███████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓   ███     ███          █████    ",
			L" ████████████▓▓▓▓▓▓▓▓▓▓▓  ▓▓▓   ███     ███          █████    ",
			L" ████████████████████▓▓▓  ▓▓▓   ███     ███          █████    ",
			L" ████   ███    ████ █▓▓▓  ▓▓▓   ███     ███          █████    ",
			L" ████   ███    ████ █▓▓▓  ▓▓▓   ███     ███          █████    ",
			L" ████   ███    ████ █▓▓▓  ▓▓▓▓  ███                  █████    ",
			L" ████          ████  ▓▓▓▓                                     ",
		};
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < wcslen(silla[0]); j++) {
				wchar_t c = silla[i][j];
				if (c != L' ') {
					int x = ANCHO / 2 - (wcslen(silla[0]) / 2) + j;
					int y = ALTO / 2 - 7 + i;

					if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
						pantalla[y][x].simbolo = c;
						ConsoleColor color = ConsoleColor::DarkGray;

						pantalla[y][x].color = color;
					}
				}
			}
		}
	}
	void DibujarFrame3() {
		const wchar_t* silla[] = {
			L"                                                              ",
			L"                     ▒▒▒▒▒▒▒▒                                 ",
			L"                    ▒▓▓▓▓▓▓▓                                  ",
			L"                     ▓▓▓▓▓▓▓                                  ",
			L"                     ▓▓▓▓▓▓▓                                  ",
			L"                      ▓▓▓▓▓                                   ",
			L"                   ▓▓▓▓▓▓▓▓▓▓▓▓                               ",
			L" ███████████████   ▓▓▓▓▓▓▓▓▓▓▓▓▓                              ",
			L" ███████████████   ▓▓▓▓▓▓▓▓▓▓ ▓▓▓                             ",
			L" ███████████████   ▓▓▓▓▓▓▓▓▓▓  ▓▓▓        ▓▓           ▓▓     ",
			L" ███████████████   ▓▓▓▓▓▓▓▓▓▓   ▓▓▓        ▓▓▓▓▓▓▓▓▓▓▓▓▓      ",
			L" ███████████████   ▓▓▓▓▓▓▓▓▓▓    ████████████████████████     ",
			L" ███████████████     ▓▓▓▓▓▓▓▓   ██████████████████████████    ",
			L" ███████████████     ▓▓▓▓▓▓▓▓   ███     ███          █████    ",
			L" ████████████████████▓▓▓▓▓▓▓▓   ███     ███          █████    ",
			L" ████████████████████▓▓▓  ▓▓▓   ███     ███          █████    ",
			L" ████████████████████▓▓▓  ▓▓▓   ███     ███          █████    ",
			L" ████   ███    ████ █▓▓▓  ▓▓▓   ███     ███          █████    ",
			L" ████   ███    ████ █▓▓▓  ▓▓▓   ███     ███          █████    ",
			L" ████   ███    ████ █▓▓▓  ▓▓▓▓  ███                  █████    ",
			L" ████          ████  ▓▓▓▓                                     ",
		};
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < wcslen(silla[0]); j++) {
				wchar_t c = silla[i][j];
				if (c != L' ') {
					int x = ANCHO / 2 - (wcslen(silla[0]) / 2) + j;
					int y = ALTO / 2 - 7 + i;

					if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
						pantalla[y][x].simbolo = c;
						ConsoleColor color = ConsoleColor::DarkGray;

						pantalla[y][x].color = color;
					}
				}
			}
		}
	}
	void DibujarFrame4() {
		const wchar_t* silla[] = {
			L"                                                           ",
			L"                                      ▒▒▒▒▒▒▒▒             ",
			L"                                     ▒▓▓▓▓▓▓▓              ",
			L"                                      ▓▓▓▓▓▓▓              ",
			L"                                      ▓▓▓▓▓▓▓              ",
			L"                                       ▓▓▓▓▓               ",
			L"                                  ▓▓▓▓▓▓▓▓▓▓▓▓▓            ",
			L" ███████████████                ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓           ",
			L" ███████████████                ▓▓▓ ▓▓▓▓▓▓▓▓▓▓▓▓▓          ",
			L" ███████████████                ▓▓▓ ▓▓▓▓▓▓▓▓▓▓ ▓▓▓         ",
			L" ███████████████                ▓▓▓ ▓▓▓▓▓▓▓▓▓▓  ▓▓▓        ",
			L" ███████████████              ██▓▓▓█▓▓▓▓▓▓▓▓▓▓███▓▓▓█████  ",
			L" ███████████████              ██████▓▓▓▓▓▓▓▓▓▓███████████  ",
			L" ███████████████              ███   ▓▓▓▓▓▓▓▓▓▓    █████    ",
			L" ██████████████████████       ███   ▓▓▓▓   ▓▓▓▓   █████    ",
			L" ██████████████████████       ███   ▓▓▓▓    ▓▓▓▓  █████    ",
			L" ██████████████████████       ███  ▓▓▓▓█     ▓▓▓▓ █████    ",
			L" ████   ███    ████ ███       ███ ▓▓▓▓██      ▓▓▓ █████    ",
			L" ████   ███    ████ ███       ███▓▓▓▓ ██      ▓▓▓ █████    ",
			L" ████   ███    ████ ███       ██▓▓▓            ▓▓▓█████    ",
			L" ████          ████             ▓▓▓▓           ▓▓▓▓▓       ",
		};
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < wcslen(silla[0]); j++) {
				wchar_t c = silla[i][j];
				if (c != L' ') {
					int x = ANCHO / 2 - (wcslen(silla[0]) / 2) + j;
					int y = ALTO / 2 - 7 + i;

					if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
						pantalla[y][x].simbolo = c;
						ConsoleColor color = ConsoleColor::DarkGray;

						pantalla[y][x].color = color;
					}
				}
			}
		}
	}
	void EscribirFrase() {
		const wchar_t* frase[] = {
			L"\"Mientras tú juegas, millones no tienen qué comer…\""
		};
		int longitud = wcslen(frase[0]);

		for (int j = 0; j < wcslen(frase[0]); j++) {
			wchar_t c = frase[0][j];
			if (c != L' ') {
				int x = ANCHO / 2 - (longitud / 2) + j;
				int y = 4;

				if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
					ConsoleColor color = ConsoleColor::DarkYellow;
					pantalla[y][x].color = color;
					pantalla[y][x].simbolo = c;
				}

				// Imprimir letra
				Console::ForegroundColor = ConsoleColor::DarkYellow;
				Console::SetCursorPosition(x, y);
				Console::Write(pantalla[y][x].simbolo);
				Sleep(30);
			}
			
			if (j == longitud / 3) {
				LimpiarFrame();
				DibujarFrame3();
			}
		}	
		funciones::mostrarPantalla();
	}
	void PulsarEnter() {
		const wchar_t* enter[] = {
			L"Pulsa 'Enter' para continuar..."
		};
		int longitud = wcslen(enter[0]);
		FiguraAvanzada Enter{
			enter,
			1,
			longitud,
			ANCHO - longitud,
			ALTO - 3,
			ConsoleColor::DarkYellow,
			nullptr
		};
		funciones::DibujarFiguraAvanzada(Enter);
		funciones::mostrarPantalla();
		// Requerir enter para continuar
		int key;
		do {
			key = _getch();
			if (key == 13) {
				break;
			}
		} while (key != 13);
	}
	// Funcion principal
	void AnimacionDeEntrada() {
		Sleep(2000); 
		funciones::LiberarPantalla();
		funciones::InicializarPantalla();

		DibujarFrame2();
		funciones::mostrarPantalla();
		Sleep(1000);
		EscribirFrase();
		Sleep(1000);
		LimpiarFrame();
		DibujarFrame4();
		funciones::mostrarPantalla();
		PulsarEnter();
		Sleep(1000);
	}

}