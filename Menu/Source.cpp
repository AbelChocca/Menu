    #include "HambreCeroBiblioteca.h"

    // Structs
    struct Posicion
    {
        int x;
        int y;
    };
    // Posiciones de los pinos
    const Posicion posicionesPinos[6] = {
        {1, 16},
        {10, 14},
        {20, 15},
        {30, 17},
        {40, 18},
        {50, 19}
    };

    // Posiciones de las nubes
    int nube_x1 = 3, nube_y1 = 2;
    int nube_x2 = 53, nube_y2 = 3;
    int nube_x3 = 27, nube_y3 = 3;
    int nube_x4 = 75, nube_y4 = 1;
    // Forma de las nubes
    const wchar_t* nube1[] = {
    L"         ███████████         ",
    L"     ████████▓▓▓▓▓▓▓███      ",
    L"   ███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███    ",
    L"  ████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█   ",
    L" ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██  ",
    L"████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██ ",
    L" ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██",
    L"  ████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██  "
    };

    const wchar_t* nube2[] = {
        L"            ██████████████████            ",
        L"        ████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███        ",
        L"     ███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███     ",
        L"   ███████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███   ",
        L"  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█   ",
        L" █████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██  ",
        L" ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██ ",
        L"  ██████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███  "
    };

    

    // Variables generales de la pantalla
    int ANCHO = 100;
    int ALTO = 80;
    Celda** pantalla;

    void configurarConsola() {
        Console::SetWindowSize(ANCHO, ALTO);
        Console::SetBufferSize(ANCHO, ALTO);
        Console::CursorVisible = false;
    }

    // Dibujar todo el escenario en la pantalla
    void InicializarPantalla(int alto, int ancho) {
        pantalla = new Celda * [alto];
        for (int i = 0; i < alto; ++i) {
            pantalla[i] = new Celda[ancho];
            for (int j = 0; j < ancho; ++j) {
                pantalla[i][j].simbolo = L' ';
                pantalla[i][j].color = ConsoleColor::Cyan;
            }
        }
    }
    void mostrarPantalla() {
        for (int i = 0; i < ALTO; i++) {
            for (int j = 0; j < ANCHO; j++) {
                Console::ForegroundColor = pantalla[i][j].color;
                Console::SetCursorPosition(j, i);
                Console::Write(pantalla[i][j].simbolo);
            }
        }
    }


    // Dibujar nubes
    void DibujarNubes() {


        // Dibuja nube1 en varias posiciones
        int altoNube1 = 8;
        int anchoNube1 = wcslen(nube1[0]);

        for (int i = 0; i < altoNube1; i++) {
            for (int j = 0; j < anchoNube1; j++) {
                wchar_t c = nube1[i][j];
                if (c != L' ') {
                    if ((nube_y1 + i >= 0) && (nube_y1 + i < ALTO) && (nube_x1 + j >= 0) && (nube_x1 + j < ANCHO)) {
                        pantalla[nube_y1 + i][nube_x1 + j].simbolo = c;
                        pantalla[nube_y1 + i][nube_x1 + j].color = ConsoleColor::White;
                    }
                    if ((nube_y2 + i >= 0) && (nube_y2 + i < ALTO) && (nube_x2 + j >= 0) && (nube_x2 + j < ANCHO)) {
                        pantalla[nube_y2 + i][nube_x2 + j].simbolo = c;
                        pantalla[nube_y2 + i][nube_x2 + j].color = ConsoleColor::White;
                    }
                }
            }
        }

        // Dibuja nube2
        int altoNube2 = 8;
        int anchoNube2 = wcslen(nube2[0]);

        for (int i = 0; i < altoNube2; i++) {
            for (int j = 0; j < anchoNube2; j++) {
                wchar_t c = nube2[i][j];
                if (c != L' ') {
                    if (nube_y3 + i >= 0 && nube_y3 + i < ALTO && nube_x3 + j >= 0 && nube_x3 + j < ANCHO) {
                        pantalla[nube_y3 + i][nube_x3 + j].simbolo = c;
                        pantalla[nube_y3 + i][nube_x3 + j].color = ConsoleColor::White;
                    }

                    if (nube_y4 + i >= 0 && nube_y4 + i < ALTO && nube_x4 + j >= 0 && nube_x4 + j < ANCHO) {
                        pantalla[nube_y4 + i][nube_x4 + j].simbolo = c;
                        pantalla[nube_y4 + i][nube_x4 + j].color = ConsoleColor::White;
                    }
                }
            }
        }
    }
    void ActualizarNubes() {
        const int velocidad = 1;

        nube_x1 += velocidad;
        nube_x2 += velocidad;
        nube_x3 += velocidad;
        nube_x4 += velocidad;

        int anchoNube1 = wcslen(nube1[0]);
        int anchoNube2 = wcslen(nube2[0]);

        if (nube_x1 > ANCHO) nube_x1 = -anchoNube1;
        if (nube_x2 > ANCHO) nube_x2 = -anchoNube1;
        if (nube_x3 > ANCHO) nube_x3 = -anchoNube2;
        if (nube_x4 > ANCHO) nube_x4 = -anchoNube2;
    }
    void eliminarNubes() {
        int altoNube1 = 8;
        int anchoNube1 = wcslen(nube1[0]);

        for (int i = 0; i < altoNube1; i++) {
            for (int j = 0; j < anchoNube1; j++) {
                wchar_t c = L'█';
                if (c != L' ') {
                    if ((nube_y1 + i >= 0) && (nube_y1 + i < ALTO) && (nube_x1 + j >= 0) && (nube_x1 + j < ANCHO)) {
                        pantalla[nube_y1 + i][nube_x1 + j].simbolo = c;
                        pantalla[nube_y1 + i][nube_x1 + j].color = ConsoleColor::Cyan;
                    }
                    if ((nube_y2 + i >= 0) && (nube_y2 + i < ALTO) && (nube_x2 + j >= 0) && (nube_x2 + j < ANCHO)) {
                        pantalla[nube_y2 + i][nube_x2 + j].simbolo = c;
                        pantalla[nube_y2 + i][nube_x2 + j].color = ConsoleColor::Cyan;
                    }
                }
            }
        }
        int altoNube2 = 8;
        int anchoNube2 = wcslen(nube2[0]);

        for (int i = 0; i < altoNube2; i++) {
            for (int j = 0; j < anchoNube2; j++) {
                wchar_t c = L'█';
                if (c != L' ') {
                    if (nube_y3 + i >= 0 && nube_y3 + i < ALTO && nube_x3 + j >= 0 && nube_x3 + j < ANCHO) {
                        pantalla[nube_y3 + i][nube_x3 + j].simbolo = c;
                        pantalla[nube_y3 + i][nube_x3 + j].color = ConsoleColor::Cyan;
                    }

                    if (nube_y4 + i >= 0 && nube_y4 + i < ALTO && nube_x4 + j >= 0 && nube_x4 + j < ANCHO) {
                        pantalla[nube_y4 + i][nube_x4 + j].simbolo = c;
                        pantalla[nube_y4 + i][nube_x4 + j].color = ConsoleColor::Cyan;
                    }
                }
            }
        }
    }
    // Dibujar Suelo
    void DibujarSuelo() {
        const wchar_t* suelo[] = {
            L"██████████████                                                                   ███████████████████",
            L"████████████████████                                                      ██████████████████████████",
            L"████████████████████████████████████████                              ██████████████████████████████",
            L"██████████████████████████████████████████                       ███████████████████████████████████",
            L"████████████████████████████████████████████             ███████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
        };
        
        int altoSuelo = 10;
		int anchoSuelo = wcslen(suelo[0]); 
        int posYSuelo = 20;

        funciones::DibujarFigura(pantalla, ALTO, ANCHO, suelo, altoSuelo, anchoSuelo, 0, posYSuelo, ConsoleColor::DarkGreen);
    }

    // Dibujar Arbol Madre
    void DibujarArbolMadre() {
        const wchar_t* arbol[] = {
        L"                                  ▓▓▓▓▓▓▓▓▓▓▓         ",
        L"                               ▓▓▓████████████        ",
        L"              ▓▓▓▓▓▓▓▓▓▓      ▓████████████████       ",
        L"           ▓▓▓████████████▄   ▓█████████░░░░░░█       ",
        L"         ▓▓████████░░░░░███░▄█████████████░░░░░██     ",
        L"        ▓████░░░░░░░░░░░░░░▓███████████████░░░░░████  ",
        L"        ▓███░▓▓▓▓▓▓▓▓▓▓▓▓▓▓█████████████████░░░░█████ ",
        L"      ▓▓░░█░▓██████████████████████████░░░░░░████████ ",
        L"    ▓▓████░▓████████████░░░░░░░░░░░░░░░░██░░█████████ ",
        L"   ▓██████░▓█████░░███░░░░░░██████░░░░██████░░███████ ",
        L"  ▓███████░▓███░░░░░░░░░░░████████░░███████░░██████   ",
        L"  ▓███████░░▓░░░░░░░░░░░░░███████░░░░░█████░░░██████  ",
        L"  ▓███░█░░░░░░░░░░░░░░░░░░░███░░░░░▓▓▓▓▓▓▓▓▓▓░░░███   ",
        L"   ░█░░░░░░░░░░░░▓▓▓▓▓▓▓▓▓▓▓░░░░░▓▓███████████▓░░     ",
        L"    ░░░░░░░░░░░░▓████████████░░░▓████████████████     ",
        L"   ▓▓▓▓▓▓▓▓▓▓░░▓██████████████░░▓█████████████████    ",
        L"  ▓█████████▓░▓███████░░█░█░█████████████████████     ",
        L" ▓█████████░░▓███████░░░░░░░░░░███████░██░░█░░█░░     ",
        L" ▓███████░░░░░██████░░░░░░░░░░░██████░░░░░░░░░░░░     ",
        L" ▓████░█░░░░░░█████░░░░░░░░░░░░░█████░░░░░░░░░░░░     ",
        L"  ░█░█░░░░░░░░░███░░░░░░░░░░░░░░░█░█░░░░░░░░░░░       ",
        L"   █░░░░░░░░░░░░░░░░░░░░░░░░░░░▒░░░░░░░ ░░░░░ ░░      ",
        L"      ░░ ░░ ░  ░▓░▓▓▓░▒░▒░▒░▒░▒▒ ░░  ░░ ▓░░░  ░       ",
        L"       ░ ░  ░    ▓▓▓▓░▒░░░▒░▒░▒▒  ░ ▓▓░ ▓▓░           ",
        L"         ░         ▓▓▓░▒░▒▒░▒▒▒    ▓▓▓ ▓▓▒            ",
        L"                    ▓▓▓▒▓▓░▓▓░▓▓▓▓▓▓▓▓▓▓▒▒            ",
        L"                   ▓░▓▓▓░▓▓░▓▓░▓▓▓▓▒▒▒▒▒              ",
        L"                  ▓▓▓░▓▓▓░▓▓░▓▓░▒▒▒▒                  ",
        L"               ▓▓▓▓░░▓▓▓░▓▓▓▓░░▓▒▒▒▒▒                 "
        };

        int altoArbol = 29;
        int anchoArbol = wcslen(arbol[0]);
        int posYArbol = 0; 
        int posXArbol = 50;
        for (int i = 0; i < altoArbol; i++) {
            for (int j = 0; j < anchoArbol; j++) {
                wchar_t c = arbol[i][j];
                if (c != L' ') {
                    int y = posYArbol + i;
                    int x = j + posXArbol;
                    
                    if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
                        pantalla[y][x].simbolo = c;
                        bool Tronco = (i >= 22) && (j >= 15 && j <= 45);
                        pantalla[y][x].color = Tronco ? ConsoleColor::DarkYellow : ConsoleColor::Green;

                    }
                }
            }
        }


    }

    // Dibujar Montañas
    void DibujarMontañas() {
        const wchar_t* montanas[] = {
            L"                                                          ░░█████████                               ",
            L"                                                        ░░░██████▓▓████                       ▓█    ",
            L"                                                      ░░░░███████▓▓█████                    ▓▓▓██   ",
            L"                                                   ░░░░█░░████████▓▓████                  ▓▓▓▓████  ",
            L"                                                 ░░░█░░█░░█████████▓▓████▓ ██            ▓▓▓█▓████  ",
            L"                         ░░▓█                   ░░░░█░░████░░███████▓▓█▓▓█▓███          ▓▓█▓█▓████  ",
            L"    ░██                 ░░█▓▓█                  ░░░░██████░███████████▓▓█▓█████        ▓▓▓█▓███████ ",
            L"   ░████               ░█░██▓██               ░░█░███████░██████████████▓░██████      ▓▓█▓█████████ ",
            L"  ░██████    ░█       ░░█░██▓███              ░░█░█████████████████████▓░░██████     ▓█▓████████████",
            L" ░████████  ░███     ░█░█░██▓███              ░░█░████░░██████████████▓░░████████   ▓▓█▓████████████",
            L"░██████████▓█████  ░█░█░██░██▓██            ░░███████░██████████████▓▓░░██████████ ▓█▓██████████████",
            L"██████████▓███████▓░█░███░░██▓█▓██       ███░██░██░░██████████████▓▓███████████████▓█▓██████████████",
            L"█████████▓███████▓█░████░░████▓████     ██████░██░██████████████▓▓████████████████▓█████████████████",
            L"████████▓███████▓████████████▓█████    ██████░████████████████▓▓█████████████████▓██████████████████",
            L"████████████████████████████▓██████   ██████████████████████▓▓██████████████████▓███████████████████",
            L"███████████████████████████▓████████ █████████████████████▓▓███████████████████▓████████████████████",
            L"███████████████████████████████████████████████████████▓▓▓███████████████████▓▓█████████████████████",
            L"████████████████████████████████████████████████████▓▓▓████████████████████▓▓███████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████",
            L"████████████████████████████████████████████████████████████████████████████████████████████████████"
        };

        int altoMontaña = 23;
        int anchoMontaña = wcslen(montanas[0]);

        int posYMontaña = 3;

        for (int i = 0; i < altoMontaña; i++) {
            for (int j = 0; j < anchoMontaña; j++) {
                wchar_t c = montanas[i][j];
                if (c != L' ') {
                    if (i + posYMontaña >= 0 && i + posYMontaña < ALTO && j >= 0 && j < ANCHO) {
                        pantalla[posYMontaña + i][j].simbolo = c;
                        pantalla[posYMontaña + i][j].color = ConsoleColor::Gray;
                    }
                }
            }
        }
    }


    void DibujarMenu(int posx, int posy, int ancho, int alto) {
        const wchar_t* Menu[] = {
            L"                                          ",
            L"  ███╗   ███╗███████╗███╗   ██╗██╗   ██╗  ",
            L"  ████╗ ████║██╔════╝████╗  ██║██║   ██║  ",
            L"  ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║  ",
            L"  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║  ",
            L"  ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝  ",
            L"  ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝   "
        };

        const int int_AltoMenu = sizeof(Menu) / sizeof(Menu[0]);
        const size_t int_AnchoMenu = wcslen(Menu[0]);

        size_t x = posx + (ancho - int_AnchoMenu) / 2;
        size_t y = posy + (alto - int_AltoMenu) / 2;

        if (x + int_AnchoMenu + 1 > ANCHO) {
            x = ANCHO - int_AnchoMenu - 1;
        }
        if (x < 0) x = 0;

        for (int i = -1; i <= int_AltoMenu; i++) {
            for (int a = -1; a <= (int)int_AnchoMenu; a++) {
                size_t y2 = y + i;
                size_t x2 = x + a;

                if (y2 >= 0 && y2 < ALTO && x2 >= 0 && x2 < ANCHO) {
                    if (i == -1 || i == int_AltoMenu || a == -1 || a == (int)int_AnchoMenu) {
                        pantalla[y2][x2].simbolo = L'█';
                        pantalla[y2][x2].color = ConsoleColor::DarkGray;
                    }
                }
            }
        }

        // Dibujar el contenido del menú
        for (int i = 0; i < int_AltoMenu; i++) {
            for (int a = 0; a < (int)int_AnchoMenu; a++) {
                wchar_t ccc = Menu[i][a];
                size_t y2 = y + i;
                size_t x2 = x + a;

                if (y2 >= 0 && y2 < ALTO && x2 >= 0 && x2 < ANCHO) {
                    pantalla[y2][x2].simbolo = (ccc == L' ') ? L'█' : ccc;
                    pantalla[y2][x2].color = (ccc == L' ') ? ConsoleColor::Black : ConsoleColor::Blue;
                }
            }
        }
    }

    // Dibujar Pino
    void DibujarPino() {
        const wchar_t* pino[] = {
        L"    █    ",
        L"   ██▒   ",
        L"  ███▒▒  ",
        L" ████▒▒▒ ",
        L"█████▒▒▒▒",
        L"    █▓    ",
        L"    █▓   "
        };

        int altoPino = 7;
        int anchoPino = wcslen(pino[0]);

        for (int p = 0; p < 6; p++) {
            int posY = posicionesPinos[p].y;
            int posX = posicionesPinos[p].x;

            for (int i = 0; i < altoPino; i++) {
                for (int a = 0; a < anchoPino; a++) {
                    wchar_t c = pino[i][a];
                    if (c != L' ') {
                        if (posY + i >= 0 && posY + i < ALTO && posX + a >= 0 && posX + a < ANCHO) {
                            pantalla[posY + i][posX + a].simbolo = c;
                            if (i < altoPino - 2) {
                                pantalla[posY + i][posX + a].color = ConsoleColor::Green;
                            }
                            else {
                                pantalla[posY + i][posX + a].color = ConsoleColor::DarkYellow;
                            }
                        }
                    }
                }
            }
        }
    }

    void RedibujarFondo() {
        // Cielo
        for (int i = 0; i < ALTO; i++) {
            for (int j = 0; j < ANCHO; j++) {
                pantalla[i][j].simbolo = L'█';
                pantalla[i][j].color = ConsoleColor::Cyan;
            }
        }


        int posxmenu = 10;
        int posymenu = 0;
        int anchoverde = 70;
        int altoverde = 30;
        
        DibujarMontañas();
        DibujarSuelo();
        DibujarPino();
        DibujarArbolMadre();
        DibujarMenu(posxmenu, posymenu, anchoverde, altoverde);

    }

    void AnimarNubes() {
        while (true) {
            RedibujarFondo();   
            ActualizarNubes();
            DibujarNubes();
            mostrarPantalla();
            Sleep(50); 
        }
    }


    //Dibujar el Menu


    //dibujar informacion:
    void DibujarInformacion(int posx, int posy, int ancho, int alto) {
        const wchar_t* informacion[] = {
        L" ██╗███╗   ██╗███████╗ ██████╗ ██████╗ ███╗   ███╗ █████╗  ██████╗██╗ ██████╗ ███╗   ██╗",
        L" ██║████╗  ██║██╔════╝██╔═══██╗██╔══██╗████╗ ████║██╔══██╗██╔════╝██║██╔═══██╗████╗  ██║",
        L" ██║██╔██╗ ██║█████╗  ██║   ██║██████╔╝██╔████╔██║███████║██║     ██║██║   ██║██╔██╗ ██║",
        L" ██║██║╚██╗██║██╔══╝  ██║   ██║██╔══██╗██║╚██╔╝██║██╔══██║██║     ██║██║   ██║██║╚██╗██║",
        L" ██║██║ ╚████║██║     ╚██████╔╝██║  ██║██║ ╚═╝ ██║██║  ██║╚██████╗██║╚██████╔╝██║ ╚████║",
        L" ╚═╝╚═╝  ╚═══╝╚═╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝"

        };

        int int_Altoinfo = 6;
        size_t int_Anchoinfo = wcslen(informacion[0]);

        size_t x = posx + (ancho - int_Anchoinfo) / 2;
        size_t y = posy + (alto - int_Altoinfo) / 2;

        for (int i = 0; i < int_Altoinfo; i++) {
            for (int a = 0; a < int_Anchoinfo; a++) {
                wchar_t ccc = informacion[i][a];
                size_t y2 = y + i;
                size_t x2 = x + a;

                if (y2 >= 0 && y2 < ALTO && x2 >= 0 && x2 < ANCHO) {
                    pantalla[y2][x2].simbolo = (ccc == L' ') ? L'█' : ccc;
                    pantalla[y2][x2].color = (ccc == L' ') ? ConsoleColor::Gray : ConsoleColor::Blue;
                }
            }
        }
    }



    int main() {
        configurarConsola();
		InicializarPantalla(ALTO, ANCHO);
        for (int i = 0; i < ALTO; i++) {
            for (int j = 0; j < ANCHO; j++) {
                pantalla[i][j].simbolo = L'█';
                pantalla[i][j].color = ConsoleColor::Cyan;
            }
        }

        //int posxinfo = 10;
        //int posyinfo = 30;
        //int anchoverde = 70;
        //int altoverde = 30;
        
        
        // Llamada a funciones
        DibujarNubes();
        DibujarMontañas();
        DibujarArbolMadre();
        mostrarPantalla();
        
        Sleep(4);

        AnimarNubes();

        cin.get();
        return 0;
    }