// game.cpp
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "game.h"

void inicializarMapa(char mapa[ALTURA][LARGURA]) {
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1)
                mapa[i][j] = '#'; // Paredes
            else
                mapa[i][j] = '.'; // Chão
        }
    }
    mapa[ALTURA-2][LARGURA-2] = '>'; // Saída da masmorra
}

void desenhar(char mapa[ALTURA][LARGURA], Personagem p) {
    system("clear || cls"); // Limpa a tela
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == p.y && j == p.x) std::cout << "@ "; // Jogador
            else std::cout << mapa[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // Exibição da Interface (UI)
    std::cout << "\n====================================" << std::endl;
    std::cout << " STATUS: " << p.status << std::endl;
    std::cout << " HP: " << p.vida << " | ENERGIA: " << p.energia << std::endl;
    std::cout << " POSICAO: (" << p.x << "," << p.y << ")" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Comando (WASD): ";
}

void moverJogador(Personagem &p, char comando, char mapa[ALTURA][LARGURA]) {
    int proxX = p.x, proxY = p.y;
    comando = std::tolower(comando); // A mágica da letra minúscula!

    if (comando == 'w') proxY--;
    if (comando == 's') proxY++;
    if (comando == 'a') proxX--;
    if (comando == 'd') proxX++;

    char destino = mapa[proxY][proxX];

    if (destino != '#') {
        p.x = proxX;
        p.y = proxY;
        p.status = "Caminhando..."; // Mensagem padrão

        if (destino == 'X') {
            p.vida -= 20;
            p.status = "AI! Voce lutou com um inimigo (-20 HP)";
            mapa[p.y][p.x] = '.';
        } else if (destino == '*') {
            p.energia += 15;
            p.status = "OBA! Comeu um chocolate (+15 Energia)";
            mapa[p.y][p.x] = '.';
        }
    } else {
        p.status = "Bateu na parede!";
    }
}

void espalharElementos(char mapa[ALTURA][LARGURA], char simbolo, int quantidade) {
    int cont = 0;
    while (cont < quantidade) {
        int rx = rand() % LARGURA;
        int ry = rand() % ALTURA;

        // Só coloca se o lugar estiver vazio ('.')
        if (mapa[ry][rx] == '.') {
            mapa[ry][rx] = simbolo;
            cont++;
        }
    }
}