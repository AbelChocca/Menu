#include "HambreCeroBiblioteca.h"

int ALTO_Chancho = 30;
int ANCHO_Chancho = 100;
Celda** pantallaChancho;

namespace funcionesChancho {
    void mostrarPantalla() {
        for (int i = 0; i < ALTO_Chancho; i++) {
            for (int j = 0; j < ANCHO_Chancho; j++) {
                Console::ForegroundColor = pantallaChancho[i][j].color;
                Console::SetCursorPosition(j, i);
                Console::Write(pantallaChancho[i][j].simbolo);
            }
        }
    }
    void InicializarPantalla() {
        pantallaChancho = new Celda * [ALTO_Chancho];
        for (int i = 0; i < ALTO_Chancho; ++i) {
            pantallaChancho[i] = new Celda[ANCHO_Chancho];
            for (int j = 0; j < ANCHO_Chancho; ++j) {
                pantallaChancho[i][j].simbolo = L' ';
                pantallaChancho[i][j].color = ConsoleColor::Black;
            }
        }
    }
    void DibujarFiguraAvanzada(FiguraAvanzada& figura) {
        for (int i = 0; i < figura.alto; i++) {
            for (int j = 0; j < figura.ancho; j++) {
                wchar_t c = figura.dato[i][j];
                if (c != L' ') {
                    int x = figura.posx + j;
                    int y = figura.posy + i;

                    if (y >= 0 && y < ALTO_Chancho && x >= 0 && x < ANCHO_Chancho) {
                        pantallaChancho[y][x].simbolo = c;
                        ConsoleColor color = figura.funcionColor ? figura.funcionColor(i, j, c) : figura.color;

                        pantallaChancho[y][x].color = color;
                    }
                }
            }
        }
    }
    ConsoleColor chancho(int fila, int columna, wchar_t c) {
        bool cerdo = (fila < 11);
        return cerdo ? ConsoleColor::Magenta : ConsoleColor::Red;
    }
}
void limpiarPantalla() {
    for (int i = 0; i < ALTO_Chancho; ++i)
        delete[] pantallaChancho[i];
    delete[] pantallaChancho;
}


void transcion() {
    const wchar_t* chanchito[] = {
        L"                                   █     █                                ",
        L"                     █████████████████████                                ",
        L"                   ██                     ██                              ",
        L"                   ██                       ██                            ",
        L"                 ████                 ▇   ▇ ██                            ",
        L"               ██  ██                 ████████████                        ",
        L"                   ██                 ██  ████  ██                        ",
        L"                   ██                 ████████████                        ",
        L"                   ██                       ██                            ",
        L"                     ███████████████████████                              ",
        L"                     ██    ██     ██    ██                                ",
        L"                       ____________________                               ",
        L"                     / |           |        \\                            ",
        L"                   /   |           |          \\                          ",
        L"      ___________/____ |___________|__________()\\__________________      ",
        L"    /__________________|_=_________|_=___________|_________________{}     ",
        L"    [           ______ |           | .           | ==  ______      { }    ",
        L"  __[__        /##  ##\\|           |             |    /##  ##\\    _{# }_",
        L"{_____)______|##    ##|___________|_____________|___|##    ##|__(______}  ",
        L"             /  ##__##                              /  ##__##        \\   ",
    };
    int altoChanchito = 20;
    int anchoChanchito = wcslen(chanchito[0]);
    funcionesChancho::InicializarPantalla();

    for (int posx = 0; posx <= ANCHO_Chancho; posx += 5) {
        FiguraAvanzada chanchito1 = {
            chanchito,
            altoChanchito,
            anchoChanchito,
            posx,
            10,
            ConsoleColor::Green,
            funcionesChancho::chancho,
        };

        funcionesChancho::InicializarPantalla();
        funcionesChancho::DibujarFiguraAvanzada(chanchito1);
        funcionesChancho::mostrarPantalla();

        Sleep(50);
    }
}

namespace Chancho {
    void AnimacionChancho() {
        Console::CursorVisible = false;

        SetConsoleOutputCP(CP_UTF8);
        _setmode(_fileno(stdout), _O_U16TEXT);

        transcion();
        Console::Clear();
        limpiarPantalla();
        currentState = GameState::Juego2;
    }
}