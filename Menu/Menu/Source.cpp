#include "HambreCeroBiblioteca.h"

	// Variables generales de la pantalla
	int ANCHO = 100;
	int ALTO = 30;
	bool mostrarFondo = false;
	int seleccionDeOpcion = 0;
	int configurarAnimacionEntrada = 0;
	bool salirAnimacion = false;
	Celda** pantalla;


	// Posiciones de las nubes
	int nube_x1 = 3, nube_y1 = 2;
	int nube_x2 = 53, nube_y2 = 3;
	int nube_x3 = 27, nube_y3 = 3;
	int nube_x4 = 75, nube_y4 = 1;
	// Forma de las nubes
	const wchar_t* nube1[] = {
	L"         ███████████         ",
	L"     ████████▓▓▓▓▓▓▓███      ",
	L"   ███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███    ",
	L"  ████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█   ",
	L" ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██  ",
	L"████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██ ",
	L" ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██",
	L"  ████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██  "
	};

	const wchar_t* nube2[] = {
		L"            ██████████████████            ",
		L"        ████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███        ",
		L"     ███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███     ",
		L"   ███████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███   ",
		L"  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█   ",
		L" █████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██  ",
		L" ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██ ",
		L"  ██████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███  "
	};


	void configurarConsola() {
		Console::SetWindowSize(ANCHO, ALTO);
		Console::SetBufferSize(ANCHO, ALTO);
		Console::CursorVisible = false;
	}
	
	// Dibujar todo el escenario en la pantalla
	void InicializarPantalla(int alto, int ancho) {
		pantalla = new Celda * [alto];
		for (int i = 0; i < alto; ++i) {
			pantalla[i] = new Celda[ancho];
			for (int j = 0; j < ancho; ++j) {
				pantalla[i][j].simbolo = L' ';
				pantalla[i][j].color = ConsoleColor::Black;
			}
		}
	}
	// Liberar pantalla
	void LiberarPantalla(int alto) {
		for (int i = 0; i < alto; ++i)
			delete[] pantalla[i];
		delete[] pantalla;
	}


	// Dibujar nubes
	void DibujarNubes() {
		// Dibuja nube1 en varias posiciones
		int altoNube1 = 8;
		int anchoNube1 = wcslen(nube1[0]);

		for (int i = 0; i < altoNube1; i++) {
			for (int j = 0; j < anchoNube1; j++) {
				wchar_t c = nube1[i][j];
				if (c != L' ') {
					if ((nube_y1 + i >= 0) && (nube_y1 + i < ALTO) && (nube_x1 + j >= 0) && (nube_x1 + j < ANCHO)) {
						pantalla[nube_y1 + i][nube_x1 + j].simbolo = c;
						pantalla[nube_y1 + i][nube_x1 + j].color = ConsoleColor::White;
					}
					if ((nube_y2 + i >= 0) && (nube_y2 + i < ALTO) && (nube_x2 + j >= 0) && (nube_x2 + j < ANCHO)) {
						pantalla[nube_y2 + i][nube_x2 + j].simbolo = c;
						pantalla[nube_y2 + i][nube_x2 + j].color = ConsoleColor::White;
					}
				}
			}
		}

		// Dibuja nube2
		int altoNube2 = 8;
		int anchoNube2 = wcslen(nube2[0]);

		for (int i = 0; i < altoNube2; i++) {
			for (int j = 0; j < anchoNube2; j++) {
				wchar_t c = nube2[i][j];
				if (c != L' ') {
					if (nube_y3 + i >= 0 && nube_y3 + i < ALTO && nube_x3 + j >= 0 && nube_x3 + j < ANCHO) {
						pantalla[nube_y3 + i][nube_x3 + j].simbolo = c;
						pantalla[nube_y3 + i][nube_x3 + j].color = ConsoleColor::White;
					}

					if (nube_y4 + i >= 0 && nube_y4 + i < ALTO && nube_x4 + j >= 0 && nube_x4 + j < ANCHO) {
						pantalla[nube_y4 + i][nube_x4 + j].simbolo = c;
						pantalla[nube_y4 + i][nube_x4 + j].color = ConsoleColor::White;
					}
				}
			}
		}
	}
	void ActualizarNubes() {
		const int velocidad = 1;

		nube_x1 += velocidad;
		nube_x2 += velocidad;
		nube_x3 += velocidad;
		nube_x4 += velocidad;

		int anchoNube1 = wcslen(nube1[0]);
		int anchoNube2 = wcslen(nube2[0]);

		if (nube_x1 > ANCHO) nube_x1 = -anchoNube1;
		if (nube_x2 > ANCHO) nube_x2 = -anchoNube1;
		if (nube_x3 > ANCHO) nube_x3 = -anchoNube2;
		if (nube_x4 > ANCHO) nube_x4 = -anchoNube2;
	}

	// Dibujar Suelo
	void DibujarSuelo() {
		const wchar_t* suelo[] = {
			L"██████████████                                                                   ███████████████████",
			L"████████████████████                                                      ██████████████████████████",
			L"████████████████████████████████████████                              ██████████████████████████████",
			L"██████████████████████████████████████████                       ███████████████████████████████████",
			L"████████████████████████████████████████████             ███████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
		};

		FiguraAvanzada sueloFigura = {
			suelo,
			10,
			wcslen(suelo[0]),
			0,
			20,
			ConsoleColor::DarkGreen,
			nullptr
		};

		funciones::DibujarFiguraAvanzada(sueloFigura);
	}

	// Dibujar Arbol Madre
	void DibujarArbolMadre() {
		const wchar_t* arbol[] = {
		L"                                  ▓▓▓▓▓▓▓▓▓▓▓         ",
		L"                               ▓▓▓████████████        ",
		L"              ▓▓▓▓▓▓▓▓▓▓      ▓████████████████       ",
		L"           ▓▓▓████████████▄   ▓█████████░░░░░░█       ",
		L"         ▓▓████████░░░░░███░▄█████████████░░░░░██     ",
		L"        ▓████░░░░░░░░░░░░░░▓███████████████░░░░░████  ",
		L"        ▓███░▓▓▓▓▓▓▓▓▓▓▓▓▓▓█████████████████░░░░█████ ",
		L"      ▓▓░░█░▓██████████████████████████░░░░░░████████ ",
		L"    ▓▓████░▓████████████░░░░░░░░░░░░░░░░██░░█████████ ",
		L"   ▓██████░▓█████░░███░░░░░░██████░░░░██████░░███████ ",
		L"  ▓███████░▓███░░░░░░░░░░░████████░░███████░░██████   ",
		L"  ▓███████░░▓░░░░░░░░░░░░░███████░░░░░█████░░░██████  ",
		L"  ▓███░█░░░░░░░░░░░░░░░░░░░███░░░░░▓▓▓▓▓▓▓▓▓▓░░░███   ",
		L"   ░█░░░░░░░░░░░░▓▓▓▓▓▓▓▓▓▓▓░░░░░▓▓███████████▓░░     ",
		L"    ░░░░░░░░░░░░▓████████████░░░▓████████████████     ",
		L"   ▓▓▓▓▓▓▓▓▓▓░░▓██████████████░░▓█████████████████    ",
		L"  ▓█████████▓░▓███████░░█░█░█████████████████████     ",
		L" ▓█████████░░▓███████░░░░░░░░░░███████░██░░█░░█░░     ",
		L" ▓███████░░░░░██████░░░░░░░░░░░██████░░░░░░░░░░░░     ",
		L" ▓████░█░░░░░░█████░░░░░░░░░░░░░█████░░░░░░░░░░░░     ",
		L"  ░█░█░░░░░░░░░███░░░░░░░░░░░░░░░█░█░░░░░░░░░░░       ",
		L"   █░░░░░░░░░░░░░░░░░░░░░░░░░░░▒░░░░░░░ ░░░░░ ░░      ",
		L"      ░░ ░░ ░  ░▓░▓▓▓░▒░▒░▒░▒░▒▒ ░░  ░░ ▓░░░  ░       ",
		L"       ░ ░  ░    ▓▓▓▓░▒░░░▒░▒░▒▒  ░ ▓▓░ ▓▓░           ",
		L"         ░         ▓▓▓░▒░▒▒░▒▒▒    ▓▓▓ ▓▓▒            ",
		L"                    ▓▓▓▒▓▓░▓▓░▓▓▓▓▓▓▓▓▓▓▒▒            ",
		L"                   ▓░▓▓▓░▓▓░▓▓░▓▓▓▓▒▒▒▒▒              ",
		L"                  ▓▓▓░▓▓▓░▓▓░▓▓░▒▒▒▒                  ",
		L"               ▓▓▓▓░░▓▓▓░▓▓▓▓░░▓▒▒▒▒▒                 "
		};
		FiguraAvanzada arbolMadre = {
			arbol,
			29,
			wcslen(arbol[0]),
			50,
			0,
			ConsoleColor::Green,
			funciones::ArbolMadre
		};
		
		funciones::DibujarFiguraAvanzada(arbolMadre);
	}

	// Dibujar Montañas
	void DibujarMontañas() {
		const wchar_t* montanas[] = {
			L"                                                          ░░█████████                               ",
			L"                                                        ░░░██████▓▓████                       ▓█    ",
			L"                                                      ░░░░███████▓▓█████                    ▓▓▓██   ",
			L"                                                   ░░░░█░░████████▓▓████                  ▓▓▓▓████  ",
			L"                                                 ░░░█░░█░░█████████▓▓████▓ ██            ▓▓▓█▓████  ",
			L"                         ░░▓█                   ░░░░█░░████░░███████▓▓█▓▓█▓███          ▓▓█▓█▓████  ",
			L"    ░██                 ░░█▓▓█                  ░░░░██████░███████████▓▓█▓█████        ▓▓▓█▓███████ ",
			L"   ░████               ░█░██▓██               ░░█░███████░██████████████▓░██████      ▓▓█▓█████████ ",
			L"  ░██████    ░█       ░░█░██▓███              ░░█░█████████████████████▓░░██████     ▓█▓████████████",
			L" ░████████  ░███     ░█░█░██▓███              ░░█░████░░██████████████▓░░████████   ▓▓█▓████████████",
			L"░██████████▓█████  ░█░█░██░██▓██            ░░███████░██████████████▓▓░░██████████ ▓█▓██████████████",
			L"██████████▓███████▓░█░███░░██▓█▓██       ███░██░██░░██████████████▓▓███████████████▓█▓██████████████",
			L"█████████▓███████▓█░████░░████▓████     ██████░██░██████████████▓▓████████████████▓█████████████████",
			L"████████▓███████▓████████████▓█████    ██████░████████████████▓▓█████████████████▓██████████████████",
			L"████████████████████████████▓██████   ██████████████████████▓▓██████████████████▓███████████████████",
			L"███████████████████████████▓████████ █████████████████████▓▓███████████████████▓████████████████████",
			L"███████████████████████████████████████████████████████▓▓▓███████████████████▓▓█████████████████████",
			L"████████████████████████████████████████████████████▓▓▓████████████████████▓▓███████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████",
			L"████████████████████████████████████████████████████████████████████████████████████████████████████"
		};
		FiguraAvanzada montanaFigura = {
			montanas,
			23,
			wcslen(montanas[0]),
			0,
			3,
			ConsoleColor::DarkGray,
			nullptr
		};

		funciones::DibujarFiguraAvanzada(montanaFigura);
	}

	// Dibujar Opcion 1
	void DibujarOpcion1() {
		const wchar_t* opcion1[] = {
			L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█",
			L"██████████████████████",
			L"█████████JUGAR████████",
			L"██████████████████████",
			L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█"
		};


		FiguraAvanzada botonUno = {
			opcion1,
			5,
			wcslen(opcion1[0]),
			ANCHO / 2 - (wcslen(opcion1[0]) / 2),
			11,
			ConsoleColor::Black,
			funciones::Bordes,
		};

		funciones::DibujarFiguraAvanzada(botonUno);
	}
	void DibujarOpcion2() {
		const wchar_t* opcion2[] = {
			L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█",
			L"██████████████████████",
			L"██████INFORMACION█████",
			L"██████████████████████",
			L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█"
		};

		FiguraAvanzada botonDos = {
			opcion2,
			5,
			wcslen(opcion2[0]),
			ANCHO / 2 - (wcslen(opcion2[0]) / 2),
			17,
			ConsoleColor::Black,
			funciones::Bordes,
		};

		funciones::DibujarFiguraAvanzada(botonDos);
	}
	void DibujarOpcion3() {
		const wchar_t* opcion3[] = {
			L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█",
			L"██████████████████████",
			L"███████CREDITOS███████",
			L"██████████████████████",
			L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█"
		};

		FiguraAvanzada botonTres = {
			opcion3,
			5,
			wcslen(opcion3[0]),
			ANCHO / 2 - (wcslen(opcion3[0]) / 2),
			23,
			ConsoleColor::Black,
			funciones::Bordes,
		};

		funciones::DibujarFiguraAvanzada(botonTres);
	}
	//dibujar flecha
	const wchar_t* flecha[] = {
				L"██    ",
				L"████  ",
				L"██████",
				L"████  ",
				L"██    ",
			};
	int flechitaX = 32;
	int flechitaY = 11;
	void Dibujartriangulo() {
		int alto = 5;
		int ancho = 6;

		for (int i = 0; i < alto; i++) {
			for (int j = 0; j < ancho; j++) {
				wchar_t c = flecha[i][j];
				if (c != L' ') {
					int x = flechitaX + j;
					int y = flechitaY + i;
						
					if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
						pantalla[y][x].simbolo = c;
						pantalla[y][x].color = ConsoleColor::DarkBlue;
					}
				}
			}
		}
	}
	void ActualizarTriangulo(int& posY, int aumenta) {
		posY += aumenta;
	}
	// Dibujar Menu
	void DibujarMenu() {
		const wchar_t* Menu[] = {
			L"                                          ",
			L"  ███╗   ███╗███████╗███╗   ██╗██╗   ██╗  ",
			L"  ████╗ ████║██╔════╝████╗  ██║██║   ██║  ",
			L"  ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║  ",
			L"  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║  ",
			L"  ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝  ",
			L"  ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝   "
		};

		const int int_AltoMenu = sizeof(Menu) / sizeof(Menu[0]);
		const size_t int_AnchoMenu = wcslen(Menu[0]);

		int posx = 10;
		int posy = 0;
		int ancho = 80;
		int alto = 11;

		size_t x = posx + (ancho - int_AnchoMenu) / 2;
		size_t y = posy + (alto - int_AltoMenu) / 2;

		if (x + int_AnchoMenu + 1 > ANCHO) {
			x = ANCHO - int_AnchoMenu - 1;
		}
		if (x < 0) x = 0;

		for (int i = -1; i <= int_AltoMenu; i++) {
			for (int a = -1; a <= (int)int_AnchoMenu; a++) {
				size_t y2 = y + i;
				size_t x2 = x + a;

				if (y2 >= 0 && y2 < ALTO && x2 >= 0 && x2 < ANCHO) {
					if (i == -1 || i == int_AltoMenu || a == -1 || a == (int)int_AnchoMenu) {
						pantalla[y2][x2].simbolo = L'█';
						pantalla[y2][x2].color = ConsoleColor::DarkGray;
					}
				}
			}
		}

		// Dibujar el contenido del menú
		for (int i = 0; i < int_AltoMenu; i++) {
			for (int a = 0; a < (int)int_AnchoMenu; a++) {
				wchar_t ccc = Menu[i][a];
				size_t y2 = y + i;
				size_t x2 = x + a;

				if (y2 >= 0 && y2 < ALTO && x2 >= 0 && x2 < ANCHO) {
					pantalla[y2][x2].simbolo = (ccc == L' ') ? L'█' : ccc;
					pantalla[y2][x2].color = (ccc == L' ') ? ConsoleColor::Black : ConsoleColor::Blue;
				}
			}
		}
	}

	// Dibujar Pino
	void DibujarPino() {
		const wchar_t* pino[] = {
		L"    █    ",
		L"   ██▒   ",
		L"  ███▒▒  ",
		L" ████▒▒▒ ",
		L"█████▒▒▒▒",
		L"    █▓    ",
		L"    █▓   "
		};

		int altoPino = 7;
		int anchoPino = wcslen(pino[0]);

		for (int p = 0; p < 6; p++) {
			int posY = posicionesPinos[p].y;
			int posX = posicionesPinos[p].x;

			FiguraAvanzada pinoFigura = {
				pino,
				altoPino,
				anchoPino,
				posX,
				posY,
				ConsoleColor::DarkGreen,
				funciones::Pinos
			};

			funciones::DibujarFiguraAvanzada(pinoFigura);

		}
	}

	void RedibujarFondo() {
		// Cielo
		for (int i = 0; i < ALTO - 2; i++) {
			for (int j = 0; j < ANCHO; j++) {
				pantalla[i][j].simbolo = L'█';
				pantalla[i][j].color = ConsoleColor::Cyan;
			}
		}

		DibujarMontañas();
		DibujarSuelo();
		DibujarPino();
		DibujarArbolMadre();
		DibujarNubes();

		if (!mostrarFondo) {
			DibujarMenu();
			DibujarOpcion1();
			DibujarOpcion2();
			DibujarOpcion3();
			Dibujartriangulo();
		}
	}

	void AnimarNubes() {
		DWORD tiempoUltimaFrase = GetTickCount64();
		int fraseActual = 0;
		while (!salirAnimacion) {
			if (_kbhit()) {
				char tecla = _getch();
				tecla = tolower(tecla);
				switch (tecla)
				{
				case 'f':
					mostrarFondo = !mostrarFondo;
					break;
				case 'w':
					if (seleccionDeOpcion > 0) {
						seleccionDeOpcion--;
						ActualizarTriangulo(flechitaY, -6);
					}
					break;
				case 's':
					if (seleccionDeOpcion < 2) {
						seleccionDeOpcion++;
						ActualizarTriangulo(flechitaY, 6);
					}
					break;
				}
				funciones::ElejirOpcion(tecla, seleccionDeOpcion, &configurarAnimacionEntrada, &salirAnimacion);
			}
			if (!salirAnimacion) {
				RedibujarFondo();
				ActualizarNubes();
				DibujarNubes();
				if (!mostrarFondo) DibujarMenu();

				if (GetTickCount64() - tiempoUltimaFrase >= 10000) {
					fraseActual++;
					tiempoUltimaFrase = GetTickCount64();
				}

				if (!mostrarFondo) funciones::MostrarFrases(fraseActual);
				funciones::mostrarPantalla();
				Sleep(50);
			}
		}
	}

	int main() {
		configurarConsola();
		funciones::ReproducirAudio();
		InicializarPantalla(ALTO, ANCHO);
		for (int i = 0; i < ALTO; i++) {
			for (int j = 0; j < ANCHO; j++) {
				pantalla[i][j].simbolo = L'█';
				pantalla[i][j].color = i < ALTO - 1 ? ConsoleColor::Cyan : ConsoleColor::DarkGreen;
			}
		}

		funciones::mostrarPantalla();
		AnimarNubes();

		return getch();
	}