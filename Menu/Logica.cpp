#include "HambreCeroBiblioteca.h"
#include "Juego1.h"

void (*Lores[])() = { 
	figuras::DibujarLore, figuras::DibujarLore2,
	figuras::DibujarLore3, figuras::DibujarLore4
};

namespace logica {
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
	void PresionarEnter() {
		while (true) {
			if (_kbhit()) {
				char tecla = _getch();
				if (tecla == 13) {
					break;
				}
			}
		}
	}
	void LeerLore() {
		for (int i = 0; i < 4; i++) {
			Lores[i]();
			config::mostrarJuego1();
			PresionarEnter();
		}
	}
		
}