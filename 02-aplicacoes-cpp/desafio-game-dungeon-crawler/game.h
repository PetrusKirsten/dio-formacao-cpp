// game.h
#ifndef JOGO_H
#define JOGO_H

#include <vector>
#include <string>

// Definições de constantes (O tamanho do mundo)
const int LARGURA = 10;
const int ALTURA = 10;

// Struct para o Jogador
struct Personagem {
    int x, y;
    int vida;
    int energia;
    std::string status;
};

// Protótipos das funções
void inicializarMapa(char mapa[ALTURA][LARGURA]);
void desenhar(char mapa[ALTURA][LARGURA], Personagem p);
void moverJogador(Personagem &p, char comando, char mapa[ALTURA][LARGURA]);
void espalharElementos(char mapa[ALTURA][LARGURA], char simbolo, int quantidade);

#endif