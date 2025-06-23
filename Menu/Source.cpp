#include "HambreCeroBiblioteca.h"

GameState currentState = GameState::MenuPrincipal;

int main() {
	SetConsoleOutputCP(CP_UTF8);
	_setmode(_fileno(stdout), _O_U16TEXT);

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