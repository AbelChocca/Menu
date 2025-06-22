#include "../HambreCeroBiblioteca.h"

const int PantallaInfoHeight = 100;
const int ViewPortHeight = 30;
Celda** PantallaInfo;

namespace informacion {
	// MostrarPantalla
	void mostrarPantallaInfo() {
		for (int i = 0; i < ViewPortHeight; i++) {
			for (int j = 0; j < ANCHO; j++) {
				Console::ForegroundColor = PantallaInfo[i][j].color;
				Console::SetCursorPosition(j, i);
				Console::Write(PantallaInfo[i][j].simbolo);
			}
		}
	}
	void LiberarPantallaInfo() {
		for (int i = 0; i < PantallaInfoHeight; ++i)
			delete[] PantallaInfo[i];
		delete[] PantallaInfo;
		PantallaInfo = nullptr;
	}
	// Dibujar figura Avanzanda
	void DibujarFiguraAvanzadaInfo(FiguraAvanzada& figura) {
		for (int i = 0; i < figura.alto; i++) {
			for (int j = 0; j < figura.ancho; j++) {
				wchar_t c = figura.dato[i][j];
				if (c != L' ') {
					int x = figura.posx + j;
					int y = figura.posy + i;

					if (y >= 0 && y < PantallaInfoHeight && x >= 0 && x < ANCHO) {
						PantallaInfo[y][x].simbolo = c;
						ConsoleColor color = figura.funcionColor ? figura.funcionColor(i, j, c) : figura.color;

						PantallaInfo[y][x].color = color;
					}
				}
			}
		}
	}
	// Incializar pantalla
	void InicializarPantallaInfo() {
		PantallaInfo = new Celda * [PantallaInfoHeight];
		for (int i = 0; i < PantallaInfoHeight; ++i) {
			PantallaInfo[i] = new Celda[ANCHO];
			for (int j = 0; j < ANCHO; ++j) {
				PantallaInfo[i][j].simbolo = L' ';
				PantallaInfo[i][j].color = ConsoleColor::Black;
			}
		}
	}
	// Dibujar flechita
	ConsoleColor CondicionFlechita(int fila, int columna, wchar_t c) {
		bool textito = (fila == 6);
		return textito ? ConsoleColor::DarkYellow : ConsoleColor::Blue;
	}
	void DibujarFlechita() {
		const wchar_t* flecha[] = {
			L"     ##      ",
			L"   ######### ",
			L" ########### ",
			L"   ######### ",
			L"     ##      ",
			L"             ",
			L" Pulsa 'Q'   ",
			L" para volver "
		};
		int longitud = wcslen(flecha[0]);
		FiguraAvanzada flechita = {
			flecha,
			8,
			longitud,
			0,
			14,
			ConsoleColor::Blue,
			CondicionFlechita
		};
		DibujarFiguraAvanzadaInfo(flechita);
	}
	// Dibujar titulo de informacion
	ConsoleColor CondicionTitulo(int fila, int columna, wchar_t c) {
		bool bordes = (fila == 0 || fila == 9 || columna <= 1 || columna >= 102);
		return bordes ? ConsoleColor::Blue : ConsoleColor::DarkBlue;
	}
	void ContenidoInformacion() {
		const wchar_t* Informacion[] = {
			L"*******************************************************************************************************",
			L"**                                                                                                   **",
			L"**  ### ####   ### ######## #######  ######## ####   ####  ######   ####### ###  ####### ####   ###  **",
			L"**  ### #####  ### ################# ###  ### ##### ##### ###  ### ######## ### ##############  ###  **",
			L"**  ### ###### ### ###     ###   ### #######  ########### ######## ###      ### ###   ######### ###  **",
			L"**  ### ########## ######  ###   ### ######## ########### ######## ###      ### ###   #############  **",
			L"**  ### ### ###### ######  ######### ###  ### ### ### ### ###  ### ######## ### ############ ######  **",
			L"**  ### ###  ##### ###      #######  ###  ### ###     ### ###  ###  ####### ###  ####### ###  #####  **",
			L"**                                                                                                   **",
			L"*****************************************************************************************+++***********",
		};

		int longitud = wcslen(Informacion[0]);
		FiguraAvanzada titulo = {
			Informacion,
			10,
			longitud,
			ANCHO / 2 - (longitud / 2),
			1,
			ConsoleColor::DarkBlue,
			CondicionTitulo
		};
		DibujarFiguraAvanzadaInfo(titulo);
	}
	// Descripcion
	ConsoleColor BordesDescripcion(int fila, int columna, wchar_t c) {
		return (c == L'#') ? ConsoleColor::Blue : ConsoleColor::DarkYellow;
	}
	ConsoleColor MarkCondition(int fila, int columna, wchar_t c) {
		if (fila == 0) return ConsoleColor::DarkYellow;
		if (fila == 1) return ConsoleColor::Blue;
		if (fila == 2) return ConsoleColor::Green;
		return ConsoleColor::DarkYellow;

	}
	ConsoleColor SantiagoCondition(int fila, int columna, wchar_t c) {
		return (c == L'#') ?
			ConsoleColor::DarkYellow : ConsoleColor::Gray;
	}
	void DescripcionDelJuego() {
		const wchar_t* DefinicionJuego[] = {
			L"                 +-------------------+              ",
			L"                 |   DESCRIPCION     |              ",
			L"                 +-------------------+              ",
			L"                                                    ",
			L"                                                    ",
			L"####################################################",
			L"#  Hambre Cero: La Mision es un videojuego         #",
			L"#  en consola enfocado en el ODS 2: Hambre Cero,   #",
			L"#  donde el jugador enfrenta desafios para         #",
			L"#  recolectar, distribuir y gestionar alimentos    #",
			L"#  con el fin de apoyar a comunidades vulnerables. #",
			L"#  Este juego busca generar consciencia, empatia   #",
			L"#  y compromiso social frente a la problematica    #",
			L"#  global del hambre.                              #",
			L"####################################################"
		};
		int longitud = wcslen(DefinicionJuego[0]);
		FiguraAvanzada descripcion = {
			DefinicionJuego,
			15,
			longitud,
			13,
			12,
			ConsoleColor::DarkYellow,
			BordesDescripcion
		};
		DibujarFiguraAvanzadaInfo(descripcion);
	}
	// Personajes
	void PartePersonajes() {
		const wchar_t* Titulo[] = {
			L"##################",
			L"#   PERSONAJES   #",
			L"##################",
		};
		int longitudTitulo = wcslen(Titulo[0]);
		FiguraAvanzada tituloPersonaje = {
			Titulo,
			3,
			longitudTitulo,
			35 - (longitudTitulo / 2),
			30,
			ConsoleColor::DarkYellow,
			BordesDescripcion
		};
		DibujarFiguraAvanzadaInfo(tituloPersonaje);

		const wchar_t* Personajes[] = {
			L"#####################################################################",
			L"# ° Mark - Protagonista: Un joven altruista que busca combatir el   #",
			L"#      hambre en su comunidad.                                      #",
			L"# ° Santiago - Antagonista: Un empresario corrupto que prioriza sus #",
			L"#      ganancias sobre el bienestar social.                         #",
			L"# ° Fiel - Aliado: Un cerdo que busca apoyar a quien lo ayuda       #",
			L"# ° Comunidad: Personas afectadas por el hambre que necesitan ayuda.#",
			L"#####################################################################"
		};
		int longitudPersonaje = wcslen(Personajes[0]);
		FiguraAvanzada descripcionPersonajes = {
			Personajes,
			8,
			longitudPersonaje,
			2,
			35,
			ConsoleColor::DarkYellow,
			BordesDescripcion
		};
		DibujarFiguraAvanzadaInfo(descripcionPersonajes);
		// Dibujar Personajes
		const wchar_t* Mark[] = {
			L"    #   ",
			L"   ###  ",
			L"    #   ",
			L"  Mark  ",
		};
		int longitudMark = wcslen(Mark[0]);
		FiguraAvanzada mark = {
			Mark,
			4,
			longitudMark,
			15,
			45,
			ConsoleColor::DarkYellow,
			MarkCondition
		};
		DibujarFiguraAvanzadaInfo(mark);
		const wchar_t* Fiel[] = {
			L"           ",
			L"  -#####   ",
			L"    # #    ",
			L"    Fiel   ",
		};
		int longitudFiel = wcslen(Fiel[0]);
		FiguraAvanzada fiel = {
			Fiel,
			4,
			longitudFiel,
			45,
			45,
			ConsoleColor::Magenta,
			nullptr
		};
		DibujarFiguraAvanzadaInfo(fiel);

		const wchar_t* Santiago[] = {
			L"    ##    ",
			L"   ####   ",
			L"   ####   ",
			L"    ##    ",
			L"    ##    ",
			L" Santiago "
		};
		int longitudSantiago = wcslen(Santiago[0]);
		FiguraAvanzada santiago = {
			Santiago,
			6,
			longitudSantiago,
			15,
			50,
			ConsoleColor::DarkGray,
			SantiagoCondition
		};
		DibujarFiguraAvanzadaInfo(santiago);

		const wchar_t* Personas[] = {
			L"            ",
			L"     #      ",
			L"    ###     ",
			L"     #      ",
			L"  Personas  ",
		};
		int longitudPersonas = wcslen(Personas[0]);
		FiguraAvanzada persona = {
			Personas,
			5,
			longitudPersonas,
			45,
			50,
			ConsoleColor::Gray,
			nullptr
		};
		DibujarFiguraAvanzadaInfo(persona);
	}
	// Dibujar ayuda
	ConsoleColor AyudaCondicion(int fila, int columna, wchar_t c) {
		if (c == L'|' || c == L'-' || c == L'+') return ConsoleColor::DarkYellow;
		if (fila == 1 || fila == 3 || fila == 9 || fila == 10) return ConsoleColor::Blue;

		return ConsoleColor::White;
	}
	void DibujarAyuda() {
		const wchar_t* Ayuda[] = {
		   L"+---------------------------+",
		   L"|          AYUDA            |",
		   L"+---------------------------+",
		   L"|        CONTROLES          |",
		   L"|                           |",
		   L"| 'w' - Subir               |",
		   L"| 's' - Bajar               |",
		   L"| 'q' - Volver al menú      |",
		   L"|                           |",
		   L"| Explora los personajes y  |",
		   L"| la historia del juego.    |",
		   L"|                           |",
		   L"| Cuando entre a seleccionar|",
		   L"| los niveles, debe pulsar  |",
		   L"| la tecla '1' para selecc- |",
		   L"| ionar el nivel 1, tecla   |",
		   L"| '2' para el nivel 2, etc..|",
		   L"| Y darle a la tecla Enter  |",
		   L"| para comenzar a jugar!    |",
		   L"|                           |",
		   L"|  ¡Disfruta descubriendo!  |",
		   L"+---------------------------+",
		};
		int longitudAyuda = wcslen(Ayuda[0]);
		FiguraAvanzada ayuda = {
			Ayuda,
			22,
			longitudAyuda,
			70,
			12,
			ConsoleColor::White,
			AyudaCondicion
		};
		DibujarFiguraAvanzadaInfo(ayuda);
	}

	void ScrollVertical(int inicio) {
		for (int i = 0; i < ViewPortHeight; i++) {
			int linea = inicio + i;
			if (linea < PantallaInfoHeight) {
				for (int j = 0; j < ANCHO; j++) {
					Console::SetCursorPosition(j, i);
					Console::ForegroundColor = PantallaInfo[linea][j].color;
					Console::Write(PantallaInfo[linea][j].simbolo);
				}
			}

		}
	}
	void CambiarAMenu() {
		Console::Clear();
		LiberarPantallaInfo();
		funciones::Menu();
	}
	void MostrarInformacion() {
		funciones::LiberarPantalla(); // Pantalla del Menu
		InicializarPantallaInfo();

		ContenidoInformacion();
		DibujarFlechita();
		DescripcionDelJuego();
		DibujarAyuda();
		PartePersonajes();
		mostrarPantallaInfo();

		int lineaInicio = 0;

		while (currentState == GameState::Informacion)
		{
			if (_kbhit()) {
				char tecla = _getch();
				switch (tecla)
				{
				case 'w':
					if (lineaInicio > 0) {
						lineaInicio--;
						ScrollVertical(lineaInicio);
					}
					break;
				case 's':
					if (lineaInicio + ViewPortHeight < PantallaInfoHeight) {
						lineaInicio++;
						ScrollVertical(lineaInicio);
					}
					break;
				case 'q':
					currentState = GameState::MenuPrincipal;
					break;
				default:
					break;
				}
			}
		}
	}
}