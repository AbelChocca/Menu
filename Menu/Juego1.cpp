﻿#include "HambreCeroBiblioteca.h"
#include "Juego1.h"

// Indicacion global
const wchar_t* indicacion[] = {
	L"Pulsa 'Q' para agarrar"
};
int longitudIndicacion = wcslen(indicacion[0]);
int alturaIndicacion = 1;

namespace PrimerJuego {
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

	void RenderizarPantalla() {
		if (mostrarIndicacion) {
			ImprimirIndicacion();
			Sleep(500);
		}
		else {
			BorrarIndicacion();
		}
		DibujarMark(mark);
	}

	void ConfigurarPrimerNivel() {
		config::configurarConsolaJuego1();
		config::InicializarJuego1();
		figuras::GenerarSuelo();
		figuras::GenerarPared();
		figuras::GenerarCajasRandom();
		figuras::DibujarInventario();
		
		for (int i = 0; i < Juego1ALTO; ++i) {
			for (int j = 0; j < Juego1ANCHO; ++j) {
				Juego1Matriz[i][j] = Juego1FondoMatriz[i][j];
			}
		}
		config::mostrarJuego1();
		RenderizarPantalla();
	}
	// Inciar Juego
	void IniciarJuego() {
		ConfigurarPrimerNivel();
		const int VELOCIDAD = 1;
		logica::LeerLore();
		ConfigurarPrimerNivel();
		while (true) { 
			int mark_old_posx = mark.posx;
			int mark_old_posy = mark.posy;
			if (_kbhit()) {
				char tecla = _getch();
				// Lógica para mover el jugador, etc.
				switch (tecla)
				{
				case 'q':
					config::LiberarPantalla();
					funciones::ResetearConsola();
					currentState = GameState::SeleccionJuego; 
					return; 
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


			bool colisiones_cajas = logica::DetectarColisiones(mark);
			bool colisiones_bordes = false;
			if (mark.posy < limiteSuperiorJuego || mark.posy > limiteInferiorJuego
				|| mark.posx > limiteDerechoJuego || mark.posx < limiteIzquierdoJuego) {
				colisiones_bordes = true;
			}
			if (colisiones_cajas || colisiones_bordes) {
				mark.posx = mark_old_posx;
				mark.posy = mark_old_posy;
				if (!colisiones_bordes) mostrarIndicacion = true;
			}
			else {
				mostrarIndicacion = false;
			}


			RenderizarPantalla();

			Sleep(50);
		}
	}
}