#include "HambreCeroBiblioteca.h"


namespace informacion {
	// Dibujar titulo de informacion
	ConsoleColor CondicionTitulo(int fila, int columna, wchar_t c) {
		bool bordes = (fila == 0 || fila == 9 || columna <= 1 || columna >= 94);
		return bordes ? ConsoleColor::DarkGray : ConsoleColor::DarkBlue;
	}
	void TituloInformacion() {
		const wchar_t* Informacion[] = {
			L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
			L"░░                                                                                            ░░",
			L"░░  ██╗███╗   ██╗███████╗ ██████╗ ███████╗ ███╗   ███╗ █████╗  ██████╗██╗ ██████╗ ███╗   ██╗  ░░",
			L"░░  ██║████╗  ██║██╔════╝██╔═══██╗██   ██║ ████╗ ████║██╔══██╗██╔════╝██║██╔═══██╗████╗  ██║  ░░",
			L"░░  ██║██╔██╗ ██║█████╗  ██║   ██║█████╔═╝ ██╔████╔██║███████║██║     ██║██║   ██║██╔██╗ ██║  ░░",
			L"░░  ██║██║╚██╗██║██╔══╝  ██║   ██║██╔████╗ ██║╚██╔╝██║██╔══██║██║     ██║██║   ██║██║╚██╗██║  ░░",
			L"░░  ██║██║ ╚████║██║     ╚██████╔╝██║  ██║ ██║ ╚═╝ ██║██║  ██║╚██████╗██║╚██████╔╝██║ ╚████║  ░░",
			L"░░  ╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝ ╚═╝  ╚═╝ ╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝  ░░",
			L"░░                                                                                            ░░",
			L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
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
		funciones::DibujarFiguraAvanzada(titulo);
	}

	void MostrarInformacion() {
		Console::Clear();
		LiberarPantalla(ALTO);
		InicializarPantalla(ALTO, ANCHO);
		TituloInformacion();
		funciones::mostrarPantalla();
	}

}