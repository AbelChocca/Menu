#include "HambreCeroBiblioteca.h"
#include "Juego1.h"

// Personaje principal
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
	condiciones::MarkCondition
};

const int limiteSuperiorJuego = 25;
const int limiteInferiorJuego = Juego1ALTO - mark.alto;
const int limiteIzquierdoJuego = 0;
const int limiteDerechoJuego = Juego1ANCHO - mark.ancho;


namespace condiciones {
	ConsoleColor ParedCondicion(int fila, int columna, wchar_t c) {
		if (c == L'░') return ConsoleColor::DarkGray;
		else if (c == L'█') return ConsoleColor::Cyan;
		return ConsoleColor::Gray;
	}
	ConsoleColor MarkCondition(int fila, int columna, wchar_t c) {
		if (c == L'█') return ConsoleColor::DarkYellow;
		if (c == L'▓') return ConsoleColor::Blue;
		if (fila == 3) return ConsoleColor::DarkBlue;
		return ConsoleColor::DarkBlue;
	}
	ConsoleColor CondicionLore(int fila, int columna, wchar_t c) {
		if (c == L'▓') return ConsoleColor::Black;
		return ConsoleColor::DarkYellow;
	}
	ConsoleColor CondicionInv(int fila, int columna, wchar_t c) {
		return c == L'█' ? ConsoleColor::Black : ConsoleColor::DarkYellow;
	}
}

namespace figuras {
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
			condiciones::ParedCondicion
		};
		logica::DibujarFiguraJuego(Pared, Juego1FondoMatriz);
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
			int posy = f.Next(26, 30);

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
			logica::DibujarFiguraJuego(Cajita, Juego1FondoMatriz);
		}
	}
	void DibujarLore() {
		const wchar_t* lore[] = {
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓Mark▓creció▓viendo▓cómo▓su▓barrio▓se▓quedaba▓sin▓comida.▓▓▓▓",
			L"▓▓Hoy,▓está▓listo▓para▓ayudar▓a▓quienes▓no▓pueden▓conseguirla▓",
			L"▓▓por▓sí▓mismos.▓Él▓no▓es▓un▓héroe,▓pero▓está▓decidido▓a▓▓▓▓▓▓",
			L"▓▓hacer▓la▓diferencia.▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓Pulsa▓'Enter'▓para▓comenzar▓tu▓misión▓con▓Mark.▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
		};
		int longitud = wcslen(lore[0]);
		FiguraAvanzada lore1{
			lore,
			11,
			longitud,
			Juego1ANCHO / 2 - (longitud / 2),
			Juego1ALTO / 2 - 5,
			ConsoleColor::DarkYellow,
			condiciones::CondicionLore,
		};
		logica::DibujarFiguraJuego(lore1, Juego1Matriz);
	}
	void DibujarLore2() {
		const wchar_t* lore2[] = {
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓La▓ciudad▓atraviesa▓días▓difíciles.▓El▓hambre▓golpea▓cada▓▓",
			L"▓▓▓casa,▓cada▓calle,▓cada▓familia.▓Niños,▓madres▓y▓ancianos▓▓▓",
			L"▓▓▓esperan,▓confiando▓en▓que▓alguien▓traiga▓alimento▓antes▓de▓",
			L"▓▓▓que▓sea▓tarde.▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓Pulsa▓'Enter'▓para▓continuar▓y▓ayudar▓a▓tu▓comunidad.▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
		};
		int longitud = wcslen(lore2[0]);
		FiguraAvanzada loredos{
			lore2,
			11,
			longitud,
			Juego1ANCHO / 2 - (longitud / 2),
			Juego1ALTO / 2 - 5,
			ConsoleColor::DarkYellow,
			condiciones::CondicionLore,
		};
		logica::DibujarFiguraJuego(loredos, Juego1Matriz);
	}
	void DibujarLore3() {
		const wchar_t* lore3[] = {
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓Mark▓ha▓encontrado▓un▓viejo▓almacén▓que▓podría▓tener▓comida▓▓",
			L"▓entre▓sus▓cajas▓y▓estantes▓polvorientos.▓Su▓misión▓es▓clara:▓",
			L"▓buscar▓toda▓la▓comida▓posible▓para▓alimentar▓a▓su▓comunidad.▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓Pulsa▓'Enter'▓para▓iniciar▓la▓búsqueda▓con▓Mark.▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
		};

		int longitud = wcslen(lore3[0]);
		FiguraAvanzada loretres{
			lore3,
			11,
			longitud,
			Juego1ANCHO / 2 - (longitud / 2),
			Juego1ALTO / 2 - 5,
			ConsoleColor::DarkYellow,
			condiciones::CondicionLore,
		};
		logica::DibujarFiguraJuego(loretres, Juego1Matriz);
	}
	void DibujarLore4() {
		const wchar_t* lore4[] = {
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓Cada▓lata▓encontrada▓es▓un▓día▓más▓de▓vida▓para▓alguien.▓▓▓▓▓",
			L"▓Cada▓botella▓de▓agua,▓una▓esperanza.▓Acompaña▓a▓Mark▓en▓esta▓",
			L"▓misión:▓¡Hoy▓comienza▓la▓lucha▓contra▓el▓hambre!▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓Pulsa▓'Enter'▓y▓comienza▓a▓cambiar▓historias▓con▓Mark.▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
			L"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
		};

		int longitud = wcslen(lore4[0]);
		FiguraAvanzada lorecuatro{
			lore4,
			11,
			longitud,
			Juego1ANCHO / 2 - (longitud / 2),
			Juego1ALTO / 2 - 5,
			ConsoleColor::DarkYellow,
			condiciones::CondicionLore,
		};
		logica::DibujarFiguraJuego(lorecuatro, Juego1Matriz);
	}
	void ImprimirInventario() {
		int longitud = 21;
		Console::SetCursorPosition(ANCHO_TOTAL - (15 + (longitud / 2)), 2);
		std::cout << "-----Inventario-----";
		for (int i = 0; i < 3; i++) {
			string nombre = inventario[i].insumo;
			int cantidad = inventario[i].cantidad;

			int posx = Juego1ANCHO + 2;
			int posy = 6 + i;
			Console::SetCursorPosition(posx, posy);
			Console::ForegroundColor = ConsoleColor::White;
			std::cout << nombre + ": " << cantidad;
		}
	}
	// Indicacion insumos insuficientes
	void ImprimirIndicacionInsumos() {
		for (int i = 0; i < alturaInsumos; i++) {
			for (int j = 0; j < longitudInsumos; j++) {
				int posx = (Juego1ANCHO / 2 - (longitudInsumos / 2)) + j;
				int posy = Juego1ALTO - 8;

				Console::ForegroundColor = ConsoleColor::DarkRed;
				Console::SetCursorPosition(posx, posy);
				Console::Write(indicacion_insumos[i][j]);
			}
		}
	}
	void BorrarIndicacionInsumos() {
		for (int i = 0; i < alturaInsumos; i++) {
			for (int j = 0; j < longitudInsumos; j++) {
				int posx = (Juego1ANCHO / 2 - (longitudInsumos / 2)) + j;
				int posy = Juego1ALTO - 8;

				Console::ForegroundColor = Juego1FondoMatriz[posy][posx].color;
				Console::SetCursorPosition(posx, posy);
				Console::Write(Juego1FondoMatriz[posy][posx].simbolo);
			}
		}
	}
}