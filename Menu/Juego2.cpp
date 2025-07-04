#include "HambreCeroBiblioteca.h"


const int juego2ANCHO = 50;
const int juego2ALTO = 28;

const wchar_t CARRETERA_IZQ = L'║';
const wchar_t CARRETERA_DER = L'║';
const wchar_t LINEA_CENTRO = L'│';
const wchar_t VACIO = L' ';
const wchar_t OBSTACULO = L'X';

const int ALTURA_JUGADOR = 6;
const int ANCHO_JUGADOR = 5;

const wstring jugadorFigura[ALTURA_JUGADOR] = {
    L" ___ ",
    L"|> <|",
    L"(---)",
    L"|   |",
    L"(---)",
    L"|___|"
};

int jugadorX = juego2ANCHO / 2;
int jugadorY = juego2ALTO - 1;

wchar_t mapa[juego2ALTO][juego2ANCHO];

const int MAX_OBST = 5;
int obstX[MAX_OBST];
int obstY[MAX_OBST];


namespace Juego2 {
    void ocultarCursor() {
        CONSOLE_CURSOR_INFO cursor;
        cursor.dwSize = 100;
        cursor.bVisible = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    }

    enum class ConsoleColor : WORD {
        Black = 0,
        RedBackground = BACKGROUND_RED,
        WhiteBackground = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
        GreenBackground = BACKGROUND_GREEN,
        BlackForeground = FOREGROUND_INTENSITY,
        WhiteForeground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        WhiteOnBlack = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        WhiteOnBlackBright = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    };

    void SetConsoleColor(ConsoleColor color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    }

    void gotoxy(int x, int y) {
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void inicializarMapa() {
        for (int i = 0; i < juego2ALTO; i++) {
            for (int j = 0; j < juego2ANCHO; j++) {
                if (j == 10) mapa[i][j] = CARRETERA_IZQ;
                else if (j == juego2ANCHO - 11) mapa[i][j] = CARRETERA_DER;
                else if ((j == juego2ANCHO / 2) && (i % 2 == 0)) mapa[i][j] = LINEA_CENTRO;
                else mapa[i][j] = VACIO;
            }
        }
    }
    void inicializarObstaculos() {
        for (int i = 0; i < MAX_OBST; i++) {
            obstY[i] = -(i * 5);
            obstX[i] = 11 + rand() % (juego2ANCHO - 22);
        }
    }

    void dibujarJugador() {
        SetConsoleColor(ConsoleColor::WhiteOnBlackBright);
        for (int i = 0; i < ALTURA_JUGADOR; i++) {
            gotoxy(jugadorX, jugadorY - ALTURA_JUGADOR + 1 + i);
            wcout << jugadorFigura[i];
        }
    }

    void dibujarMapa() {
        gotoxy(0, 0);
        for (int i = 0; i < juego2ALTO; i++) {
            for (int j = 0; j < juego2ANCHO; j++) {
                wchar_t c = mapa[i][j];
                if (c == CARRETERA_IZQ || c == CARRETERA_DER) {
                    SetConsoleColor(i % 2 == 0 ? ConsoleColor::RedBackground : ConsoleColor::WhiteBackground);
                    wcout << L' ';
                }
                else if (c == LINEA_CENTRO) {
                    SetConsoleColor(i % 2 == 0 ? ConsoleColor::WhiteOnBlack : ConsoleColor::Black);
                    wcout << c;
                }
                else if (c == OBSTACULO) {
                    SetConsoleColor(ConsoleColor::RedBackground);
                    wcout << c;
                }
                else if (c == VACIO) {
                    SetConsoleColor((j < 10 || j > juego2ANCHO - 11) ? ConsoleColor::GreenBackground : ConsoleColor::Black);
                    wcout << L' ';
                }
                else {
                    SetConsoleColor(ConsoleColor::Black);
                    wcout << c;
                }
            }
            wcout << L'\n';
        }
        SetConsoleColor(ConsoleColor::WhiteOnBlack);
    }

    bool moverJugador(wchar_t tecla) {
        if (tecla == L'a' && jugadorX > 11) jugadorX--;
        else if (tecla == L'd' && jugadorX < juego2ANCHO - ANCHO_JUGADOR - 11) jugadorX++;
        return true;
    }

    bool colisiona(int ox, int oy) {
        int jugadorTop = jugadorY - ALTURA_JUGADOR + 1;
        int jugadorBottom = jugadorY;
        int jugadorLeft = jugadorX;
        int jugadorRight = jugadorX + ANCHO_JUGADOR - 1;

        return (oy >= jugadorTop && oy <= jugadorBottom && ox >= jugadorLeft && ox <= jugadorRight);
    }

    bool actualizarObstaculos() {
        for (int i = 0; i < MAX_OBST; i++) {
            obstY[i]++;
            if (colisiona(obstX[i], obstY[i])) return false;
            if (obstY[i] >= juego2ALTO) {
                obstY[i] = 0;
                obstX[i] = 11 + rand() % (juego2ANCHO - 22);
            }
            if (mapa[obstY[i]][obstX[i]] == VACIO) {
                mapa[obstY[i]][obstX[i]] = OBSTACULO;
            }
        }
        return true;
    }
    void limpiarObstaculos() {
        for (int i = 0; i < juego2ALTO; i++) {
            for (int j = 11; j < juego2ANCHO - 11; j++) {
                if (mapa[i][j] == OBSTACULO) mapa[i][j] = VACIO;
            }
        }
    }
    void IniciarJuego2() {
        ocultarCursor();
        srand((unsigned)time(NULL));
        limpiarObstaculos();

        bool reiniciar = true;

        while (reiniciar) {
            system("cls");
            inicializarMapa();
            inicializarObstaculos();
            bool jugando = true;
            int puntos = 0;

            while (jugando) {
                if (_kbhit()) {
                    wchar_t tecla = _getwch();
                    if (tecla == L'q') {
                        jugando = false;
                        reiniciar = false;
                        break;
                    }
                    moverJugador(tecla);
                }

                if (!actualizarObstaculos()) {
                    jugando = false;
                    break;
                }
                dibujarMapa();
                dibujarJugador();

                limpiarObstaculos();

                gotoxy(0, juego2ALTO);
                SetConsoleColor(ConsoleColor::WhiteOnBlackBright);
                wcout << L"Puntos: " << puntos + 1 << L"    ";

                if (puntos >= 500) {
                    wcout << L"\nGANASTE! Has llegado a 500 puntos.\n";
                    reiniciar = false;
                    break;
                }

                puntos++;
                Sleep(120);
            }

            if (puntos < 500) {
                wcout << L"\n\n\U0001F4A5 GAME OVER! Puntaje final: " << puntos << L"\n";
                wcout << L"\nReintentar? (R para reiniciar): ";
                wchar_t respuesta = _getwch();
                if (respuesta != L'R' && respuesta != L'r') reiniciar = false;
            }
        }

        wcout << L"\nGracias por jugar. Presiona una tecla para salir...";
        _getch();
    }
}






