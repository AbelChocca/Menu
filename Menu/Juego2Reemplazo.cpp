// MiniJuegoGranjero.cpp - Juego standalone para enseñar a granjeros
#include "HambreCeroBiblioteca.h"
#include "Juego1.h"

using FuncionDinamica = ConsoleColor(*)(int fila, int columna, wchar_t c);

struct FiguraAvanzada_Juan {
    int x, y;
    const wchar_t** forma;        // matriz de caracteres
    const int** colores;          // matriz de colores (mismo tamaño que 'forma')
    int alto, ancho;
};
struct Celda_Sebas {
    wchar_t simbolo;
    int color;
};


struct Figura_Sebas {
    int x, y;
    wchar_t simbolo;
    int color;
};
Celda_Sebas** Matrizmapa;


const wchar_t* Mapa2[] = {
L"░░░░░░░░░█████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████░░░░░░░░░░",
L"░░░░░░░░░█████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████░░░░░░░░░░",
L"░░░░░░░░░█████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████░░░░░░░░░░",
L"░░░░░░░░░█████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████░░░░░░░░░░",
L"░░░░░░░░░█████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████░░░░░░░░░░",
L"░░░░░░░░░███████████▒▒▒▒▒▒▒▒▒▒▒▒▒█████████████████████▒▒▒▒▒▒▒▒▒▒▒▒████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████░░░░░░░░░░",
L"█████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████████████████",
L"███████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████████▒▒▒▒▒▒▒▒▒▒▒▒████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████████████████",
L"██████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████▒▒▒▒▒▒▒▒▒▒▒▒█████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████████████████████",
L"███████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████████████████████████",
L"████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████████████████████████████████████",
L"██████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████████████████████████████",
L"████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████",
L"██████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████████████████████████████████████████████",
L"██████████████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒█████████████████████████████████████████████████████",
L"██████████████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒█████████████████████████████████████████████████████",
L"██████████████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒█████████████████████████████████████████████████████",
L"██████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████████████████████████████████████████████",
L"████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████",
L"██████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████████████████████████████",
L"████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████████████████████████████████████",
L"███████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████████████████████████",
L"██████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████████████████████████",
L"██████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████▒▒▒▒▒▒▒▒▒▒▒▒█████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████████████████████",
L"░░░░░░░░░███████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████████████████▒▒▒▒▒▒▒▒▒▒▒▒████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████████████░░░░░░░░░░",
L"░░░░░░░░░███████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████████████████▒▒▒▒▒▒▒▒▒▒▒▒█████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████░░░░░░░░░░",
L"░░░░░░░░░█████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████░░░░░░░░░░",
L"░░░░░░░░░█████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████░░░░░░░░░░",
L"░░░░░░░░░█████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████░░░░░░░░░░",
L"░░░░░░░░░█████████████████████████████████████████████▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████████████████████████░░░░░░░░░░",
};

const int alturaMapa = sizeof(Mapa2) / sizeof(Mapa2[0]);
const int anchoMapa = wcslen(Mapa2[0]);



bool Colision(FiguraAvanzada_Juan& a, FiguraAvanzada_Juan& b) {
    return !(a.x + a.ancho <= b.x ||    // a está completamente a la izquierda de b
        b.x + b.ancho <= a.x ||    // b está completamente a la izquierda de a
        a.y + a.alto <= b.y ||     // a está completamente arriba de b
        b.y + b.alto <= a.y);      // b está completamente arriba de a
}
// Constantes basadas en el mapa
bool poderActivado = false;
bool poderEnCurso = false;
//Recomendacion de la IA para usar el valor DWORD
DWORD tiempoInicioPoder = 0;
const int ALTO_Sebas = alturaMapa;
const int ANCHO_Sebas = anchoMapa;
const wchar_t* chancho[2] = {
    L"████",
    L"█  █"
};
const wchar_t* RataIzq[] = {
    L"██~"
};

const wchar_t* RataDer[] = {
    L"~██"
};
const int* RataColores[] = {
    new int[3] {8, 8, 8}
};
FiguraAvanzada_Juan ratas[8];
bool ratasActivas[8];

const wchar_t* Granjero[] = {
    L"▄██▄",
    L" ▒▒ ",
    L"▓▓▓▓",
    L"▒▓▓▒",
    L" ▓▓ ",
    L" ▀▀ "
};

const int* GranjeroColores[] = {
    new int[4] { 6, 2, 2, 6 },   // Fila 1 colores
    new int[4] { 0, 6, 6, 0 },   // Fila 2
    new int[4] { 2, 2, 2, 2 },   // Fila 3
    new int[4] { 6, 2, 2, 6 },   // Fila 4
    new int[4] { 0, 2, 2, 0 },   // Fila 5
    new int[4] { 0, 6, 6, 0 }    // Fila 6
};
const wchar_t* Heroe[] = {
    L" ██ ",
    L"▓▓▓▓",
    L"█▓▓█",
    L" ▓▓ ",
    L" ▀▀ "
};
const int* HeroeColores[] = {
    new int[4] { 0, 14, 14, 0 },
    new int[4] { 4, 4, 4, 4 },
    new int[4] { 14, 4, 4, 14 },
    new int[4] { 0, 1, 1, 0 },
    new int[4] { 0, 0, 0, 0 }
};

FiguraAvanzada_Juan jugador = {
    10, 10,           // posición inicial
    Heroe,
    HeroeColores,
    5, 4              // alto, ancho
};


void DibujarFiguraAvanzada(FiguraAvanzada_Juan& f, Celda_Sebas** pantalla) {
    for (int i = 0; i < f.alto; i++) {
        for (int j = 0; j < f.ancho; j++) {
            wchar_t simbolo = f.forma[i][j];
            if (simbolo != L' ') {
                int px = f.x + j;
                int py = f.y + i;
                if (py >= 0 && py < ALTO_Sebas && px >= 0 && px < ANCHO_Sebas) {
                    pantalla[py][px].simbolo = simbolo;
                    pantalla[py][px].color = f.colores[i][j];
                }
            }
        }
    }
}


Celda_Sebas** mapa;
FiguraAvanzada_Juan granjeros[4];
bool ayudados[4] = { false, false, false, false };
int puntaje = 0;
bool mostrarInteraccion = false;
int granjeroCercano = -1;

void DibujarMapaEnPantalla(Celda_Sebas** pantalla) {
    for (int y = 0; y < alturaMapa; y++) {
        for (int x = 0; x < anchoMapa; x++) {
            pantalla[y][x].simbolo = Mapa2[y][x];

            switch (Mapa2[y][x]) {
            case L'░': pantalla[y][x].color = 8; break;
            case L'▒': pantalla[y][x].color = 6; break;
            case L'█': pantalla[y][x].color = 2; break;
            default:  pantalla[y][x].color = 7; break;
            }
        }
    }
}

void mostrarPantalla(Celda_Sebas** pantalla, int ancho, int alto) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(hConsole, coord);

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            SetConsoleTextAttribute(hConsole, pantalla[y][x].color);
            wcout << pantalla[y][x].simbolo;
        }
        wcout << endl;
    }
}
void ReiniciarJuego() {
    jugador.x = 10;
    jugador.y = 10;

    for (int i = 0; i < 4; i++) {
        ayudados[i] = false;
    }

    puntaje = 0;


    for (int i = 0; i < 8; i++) {
        int activa = rand() % 2;
        ratasActivas[i] = (activa == 1);

        if (i < 2) {
            ratas[i].x = 0;
            ratas[i].y = 5 + i * 5;
            ratas[i].forma = RataDer;
        }
        else {
            ratas[i].x = ANCHO - 3;
            ratas[i].y = 5 + (i - 2) * 5;
            ratas[i].forma = RataIzq;
        }

        ratas[i].colores = RataColores;
        ratas[i].alto = 1;
        ratas[i].ancho = 3;
    }
}
int vidas = 3;


void Dibujar() {

    DibujarMapaEnPantalla(mapa);


    for (int k = 0; k < 4; k++) {
        if (!ayudados[k]) {
            DibujarFiguraAvanzada(granjeros[k], mapa);
        }
    }
    for (int i = 0; i < 8; i++) {
        if (ratasActivas[i]) {
            DibujarFiguraAvanzada(ratas[i], mapa);
        }
    }
    DibujarFiguraAvanzada(jugador, mapa);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0,0 };
    SetConsoleCursorPosition(hConsole, coord);
    if (poderEnCurso) {
        int centroX = ANCHO_Sebas / 2 - 2;
        int centroY = ALTO_Sebas / 2 - 1;

        for (int y = 0; y < 2; y++) {
            for (int x = 0; x < 4; x++) {
                mapa[centroY + y][centroX + x].simbolo = chancho[y][x];
                mapa[centroY + y][centroX + x].color = 13;
            }
        }
    }
    for (int i = 0; i < ALTO_Sebas; i++) {
        for (int j = 0; j < ANCHO_Sebas; j++) {
            SetConsoleTextAttribute(hConsole, mapa[i][j].color);
            wcout << mapa[i][j].simbolo;
        }
        wcout << endl;
    }

    SetConsoleTextAttribute(hConsole, 15);
    wcout << L"Puntaje: " << puntaje << endl;
    wcout << L"Vidas: " << vidas << endl;

}

void InicializarGranjero(int index, int x, int y) {
    granjeros[index].x = x;
    granjeros[index].y = y;
    granjeros[index].forma = Granjero;
    granjeros[index].colores = GranjeroColores;
    granjeros[index].alto = 6;
    granjeros[index].ancho = 4;
}

void MostrarAgradecimiento(int indiceGranjero) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Texto amarillo
    wcout << L"\n🙏 ¡Gracias por tu ayuda, héroe!" << endl;
    switch (indiceGranjero) {
    case 0:
        wcout << L"La granjera del norte te da las gracias por protegerla de las ratas" << endl;
        break;
    case 1:
        wcout << L"El granjero del noreste te ofrece una sonrisa sincera." << endl;
        break;
    case 2:
        wcout << L"La anciana del sur te da las gracias por combatir la hambruna" << endl;
        break;
    case 3:
        wcout << L"el viejo granjero del sureste te llama su salvador." << endl;
        break;
    default:
        wcout << L"Gracias por tu ayuda" << endl;
        break;
    }
    wcout << L"\npresiona cualquier tecla para continuar" << endl;
    _getch();
}
void ActualizarJuego() {

    if (_kbhit()) {
        char tecla = _getch();
        switch (tecla) {
        case 'w':
            jugador.y = max(jugador.y - 1, 0);
            break;
        case 's':
            jugador.y = min(jugador.y + 1, ALTO_Sebas - jugador.alto);
            break;
        case 'a':
            jugador.x = max(jugador.x - 1, 0);
            break;
        case 'd':
            jugador.x = min(jugador.x + 1, ANCHO_Sebas - jugador.ancho);
            break;
        case 27:
            exit(0);

        }
    }

    for (int i = 0; i < 4; i++) {
        if (!ayudados[i]) {
            int dx = abs(jugador.x - granjeros[i].x);
            int dy = abs(jugador.y - granjeros[i].y);
            if (dx <= 1 && dy <= 1) {
                ayudados[i] = true;
                puntaje += 50;
                if (puntaje >= 100 && !poderActivado) {
                    poderActivado = true;
                    poderEnCurso = true;
                    tiempoInicioPoder = GetTickCount();  // Guarda el tiempo actual en milisegundos
                }
                MostrarAgradecimiento(i);
                if (puntaje >= 200) {
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                    wcout << L"\nGanaste el juego! Pudiste combatir el Habmre Cero" << endl;
                    wcout << L"Puntaje final: " << puntaje << endl;
                    wcout << L"Gracias por jugar." << endl;
                    system("pause");
                    exit(0);
					currentState = GameState::MenuPrincipal;
                    break;
                }
            }
        }
    }


    for (int i = 0; i < 8; i++) {
        if (ratasActivas[i] && !poderEnCurso) {
            if (i < 4) {
                ratas[i].x++;
                if (ratas[i].x > ANCHO_Sebas) {
                    ratas[i].x = 0;

                    int nuevaFila;
                    do {
                        nuevaFila = 5 + rand() % (ALTO_Sebas - 10);
                    } while (nuevaFila == ratas[i].y);

                    ratas[i].y = nuevaFila;
                }
            }
            else {
                ratas[i].x--;
                if (ratas[i].x < 0) {
                    ratas[i].x = ANCHO_Sebas - 3;

                    int nuevaFila;
                    do {
                        nuevaFila = 5 + rand() % (ALTO_Sebas - 10);
                    } while (nuevaFila == ratas[i].y); // evita misma fila

                    ratas[i].y = nuevaFila;
                }
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        if (ratasActivas[i]) {
            if (Colision(jugador, ratas[i])) {
                vidas--;

                if (vidas <= 0) {
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    wcout << L"Game Over: Te has quedado sin vidas." << endl;
                    wcout << L"Puntaje final: " << puntaje << endl;
                    system("pause");
                    exit(0);
                    break;
                }
                else {
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    wcout << L"Has perdido una vida, vidas restantes: " << vidas << endl;
                    system("pause");
                    ReiniciarJuego();
                    return;
                }
            }
        }
    }
    if (poderEnCurso && GetTickCount() - tiempoInicioPoder >= 10000) {
        poderEnCurso = false;
    }
}

namespace Juego2 {
    void IniciarJuego2() {
        _setmode(_fileno(stdout), _O_U16TEXT);
        srand(time(NULL));

        Console::CursorVisible = false;

        Celda_Sebas** pantalla = new Celda_Sebas * [ALTO_Sebas];
        for (int i = 0; i < ALTO_Sebas; i++)
            pantalla[i] = new Celda_Sebas[ANCHO_Sebas];

        DibujarMapaEnPantalla(pantalla);
        mapa = pantalla;
        Matrizmapa = mapa;


        InicializarGranjero(0, 2, 0);
        InicializarGranjero(1, ANCHO_Sebas - 5, 0);
        InicializarGranjero(2, 2, ALTO_Sebas - 6);
        InicializarGranjero(3, ANCHO_Sebas - 5, ALTO_Sebas - 6);
        for (int i = 0; i < 8; i++) {
            int activa = 1;
            ratasActivas[i] = (activa == 1);

            int filaRandom = 5 + rand() % (ALTO_Sebas - 10);

            if (i < 2) {
                ratas[i].x = 0;
                ratas[i].y = filaRandom;
                ratas[i].forma = RataDer;
            }
            else {
                ratas[i].x = ANCHO_Sebas - 3;
                ratas[i].y = filaRandom;
                ratas[i].forma = RataIzq;
            }

            ratas[i].colores = RataColores;
            ratas[i].alto = 1;
            ratas[i].ancho = 3;
        }

        while (true) {
            Dibujar();
            ActualizarJuego();
        }

        for (int i = 0; i < ALTO_Sebas; i++) delete[] pantalla[i];
        delete[] pantalla;
        Console::Clear();
		currentState = GameState::MenuPrincipal;
    }
}