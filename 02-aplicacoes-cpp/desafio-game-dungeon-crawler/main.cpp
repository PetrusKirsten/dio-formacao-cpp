#include <iostream>
#include <cctype>
#include "game.h"

int main() {
    srand(time(0));

    char mapa[ALTURA][LARGURA];
    char comando;
    Personagem heroi = {1, 1, 100, 50};

    inicializarMapa(mapa);

    espalharElementos(mapa, 'X', 3);
    espalharElementos(mapa, '*', 4);
        
    while(true) {
        desenhar(mapa, heroi);  // desenha o estado atual

        if (mapa[heroi.y][heroi.x] == '>') {
            std::cout << "\n PARABENS! Voce escapou da masmorra!\n";
            break;
        }

        std::cin >> comando;
        comando = std::tolower(comando);
        moverJogador(heroi, comando, mapa);

        heroi.energia--;
        if (heroi.energia <= 0) {
            std::cout << "\n Voce morreu de cansaco...\n";
            break;
        }
    }
    return 0;
}
