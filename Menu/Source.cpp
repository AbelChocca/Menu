#include "HambreCeroBiblioteca.h"

GameState currentState = GameState::MenuPrincipal;

int main() {

	while (currentState != GameState::Salir)
	{
		switch (currentState) {
		case GameState::MenuPrincipal:
			funciones::Menu();
			break;
		case GameState::Informacion:
			informacion::MostrarInformacion();
			break;
		case GameState::SeleccionJuego:
			Juegos::ElejirJuego();
			break;
		case GameState::Juego1:
			PrimerJuego::ConfigurarPrimerNivel();
			PrimerJuego::IniciarJuego();
			break;
		case GameState::Juego2:
			Juego2::IniciarJuego2();
			break;
		}
	}
	return getch();
}