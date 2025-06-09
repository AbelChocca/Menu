#include "HambreCeroBiblioteca.h"

namespace funciones {
    // Mostrar Pantalla
     void mostrarPantalla() {
    for (int i = 0; i < ALTO; i++) {
        for (int j = 0; j < ANCHO; j++) {
            Console::ForegroundColor = pantalla[i][j].color;
            Console::SetCursorPosition(j, i);
            Console::Write(pantalla[i][j].simbolo);
        }
    }
}
    // Mostrar frases
     void MostrarFrases(int i) {
         const wchar_t* frasesHambreCero[] = {
     L"\"Presiona F para ver el fondo de pantalla.\"",
     L"\"Hambre Cero no es un sueño, es una meta alcanzable.\"",
     L"\"Acabar con el hambre es el primer paso hacia un mundo justo.\"",
     L"\"Cada comida cuenta: únete al movimiento por Hambre Cero.\"",
     L"\"La seguridad alimentaria es un derecho, no un privilegio.\"",
     L"\"Un mundo sin hambre empieza con tu acción.\"",
     L"\"Alimentar al planeta es alimentar el futuro.\"",
     L"\"Nadie debería irse a dormir con el estómago vacío.\"",
     L"\"Erradicar el hambre es sembrar esperanza.\"",
     L"\"La lucha contra el hambre empieza con la solidaridad.\"",
     L"\"Producir más, desperdiciar menos: clave para el Hambre Cero.\""
         };
         int posYFrases = 10;
         const wchar_t* frase = frasesHambreCero[i];
         int longitudFrase = wcslen(frase);
         int posXFrases = ANCHO / 2 - (longitudFrase / 2);

         for (int i = 0; i < longitudFrase; i++) {
             pantalla[posYFrases][posXFrases + i].simbolo = L' ';
             pantalla[posYFrases][posXFrases + i].color = ConsoleColor::Gray;

         }
         for (int i = 0; i < longitudFrase; ++i) {
             if (posXFrases + i >= 0 && posXFrases + i < ANCHO) {
                 pantalla[posYFrases][posXFrases + i].simbolo = frase[i];
                 pantalla[posYFrases][posXFrases + i].color = ConsoleColor::Yellow;
                 Sleep(5);
             }
         }
     }
    // Condicion para dibujar arbol madre
     ConsoleColor ArbolMadre(int fila, int columna, wchar_t c) {
         bool Tronco = (fila >= 22) && (columna >= 15 && columna <= 45);
         return Tronco ? ConsoleColor::DarkYellow : ConsoleColor::Green;
     }
    // Condicion para los pinos del Fondo
     ConsoleColor Pinos(int fila, int columna, wchar_t c) {
         bool Tronco = (fila < 5);
         return Tronco ? ConsoleColor::DarkGreen : ConsoleColor::DarkYellow;
     }
    // Condicion para dibujar los bordes de los botones
     ConsoleColor Bordes(int fila, int columna, wchar_t c) {
         if (fila == 0 || fila == 4 || columna == 0 || columna == 21) return ConsoleColor::DarkGray;
         if (c == L'█') return ConsoleColor::Black;
         return ConsoleColor::Blue;
     }
    // Dibujar figura que acepte condiciones
     void DibujarFiguraAvanzada(FiguraAvanzada& figura) {
         for (int i = 0; i < figura.alto; i++) {
             for (int j = 0; j < figura.ancho; j++) {
                 wchar_t c = figura.dato[i][j];
                 if (c != L' ') {
                     int x = figura.posx + j;
                     int y = figura.posy + i;

                     if (y >= 0 && y < ALTO && x >= 0 && x < ANCHO) {
                         pantalla[y][x].simbolo = c;
                         ConsoleColor color = figura.funcionColor ? figura.funcionColor(i, j, c) : figura.color;

                         pantalla[y][x].color = color;
                     }
                 }
             }
         }
     }
    // Reproducir Audio del Juego
     void ReproducirAudio() {
         SoundPlayer^ player = gcnew SoundPlayer("audios\\FloatingTrees.wav");
         try {
             player->Load();
             player->PlayLooping();
         }
         catch (Exception^ e) {
             Console::WriteLine("Error al reproducir el audio: " + e->Message);
         }
     }
    // Elejir opciones del Menu
    void ElejirOpcion(int opcion, int seleccionDeOpcion, int* configurarEntrada, bool* salirAnimacion) {
        if (opcion == 13) {
            *salirAnimacion = true;
            switch (seleccionDeOpcion) {
            case 0:
                Console::Clear();
                if (*configurarEntrada < 1) {
                    (*configurarEntrada)++;
                    AnimacionEntrada::AnimacionDeEntrada();
                }
                break;
            case 1:
                informacion::MostrarInformacion();
                break;
            }
        }
    }

}